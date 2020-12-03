use super::super::*;

impl Midi {

    pub fn from_bytes(mut bytes: &[u8]) -> Option<Midi> {
        if &bytes[0..4] != String::from("MThd").into_bytes().as_slice() {
            return None;
        } else {
            bytes = &bytes[4..];
        }
        let len = VarLen::u32_from_bytes(&mut bytes)?;
        if len != 0x06u32 {
            return None;
        }
        let format = VarLen::u16_from_bytes(&mut bytes)?;
        let ntrks = VarLen::u16_from_bytes(&mut bytes)?;
        let division = VarLen::u16_from_bytes(&mut bytes)?;
        let mut tracks = Vec::new();
        for _ in 0..ntrks {
            if &bytes[0..4] != String::from("MTrk").into_bytes().as_slice() {
                return None;
            } else {
                bytes = &bytes[4..];
            }
            let len = VarLen::u32_from_bytes(&mut bytes)? as usize;
            tracks.push(Track::from_bytes(&bytes[0..len])?);
            bytes = &bytes[len..];
        }
        Some(Midi::new(format, ntrks, division, tracks))
    }
}

impl Track {

    fn from_bytes(mut bytes: &[u8]) -> Option<Track> {
        let mut track = Track::new();
        let mut preceding = 0x00u8;
        while bytes.len() > 0 {
            let (event, mode) = Event::from_bytes(&mut bytes, preceding)?;
            preceding = mode;
            track.add(event);
        }
        Some(track)
    }
}

impl Event {

    fn from_bytes(bytes: &mut &[u8], preceding: u8) -> Option<(Event, u8)> {
        let delta = VarLen::usize_from_bytes(bytes)?;
        let mut mode = *bytes.get(0)?;
        match mode {
            0xf0u8 => {
                *bytes = &bytes[1..];
                let mut packets = Vec::new();
                let args = VarLen::args_from_bytes(bytes)?;
                let mut b = args.len() > 0 && *args.last().unwrap() != 0xf7u8;
                packets.push(Sysex::new(delta, args));
                while b {
                    let delta = VarLen::usize_from_bytes(bytes)?;
                    if *bytes.get(0)? != 0xf7u8 {
                        return None
                    } else {
                        *bytes = &bytes[1..];
                    }
                    let args = VarLen::args_from_bytes(bytes)?;
                    b = args.len() == 0 || *args.last().unwrap() != 0xf7u8;
                    packets.push(Sysex::new(delta, args));
                }
                let sysex_packets = SysexPackets::new(packets);
                Some((Event::new_sysex_packets(sysex_packets), 0xf0u8))
            },
            0xffu8 => {
                *bytes = &bytes[1..];
                let mode = *bytes.get(0)?;
                *bytes = &bytes[1..];
                let args = VarLen::args_from_bytes(bytes)?;
                let meta = Meta::new(mode, args);
                Some((Event::new_meta(delta, meta), 0xffu8))
            },
            _ => {
                if mode & 0x80u8 == 0x00u8 {
                    mode = preceding;
                } else {
                    *bytes = &bytes[1..];
                }
                if mode & 0xf0u8 == 0xc0u8 || mode & 0xf0u8 == 0xd0u8 {
                    let args = (*bytes.get(0)?, 0x00u8);
                    *bytes = &bytes[1..];
                    Some((Event::new(delta, mode, args), mode))
                } else {
                    let args = (*bytes.get(0)?, *bytes.get(1)?);
                    *bytes = &bytes[2..];
                    Some((Event::new(delta, mode, args), mode))
                }
            },
        }
    }
}

impl VarLen {

    fn args_from_bytes(bytes: &mut &[u8]) -> Option<Vec<u8>> {
        let mut args = Vec::new();
        let len = VarLen::usize_from_bytes(bytes)?;
        for i in 0..len {
            args.push(bytes[i]);
        }
        *bytes = &bytes[len..];
        Some(args)
    }

    fn usize_from_bytes(bytes: &mut &[u8]) -> Option<usize> {
        let mut len = 0usize;
        let mut i = 0usize;
        loop {
            len <<= 0o07usize;
            let b = *bytes.get(i)? as usize;
            len |= b & 0x7fusize;
            i += 1usize;
            if b & 0x80usize == 0usize {
                break;
            }
        }
        *bytes = &bytes[i..];
        Some(len)
    }

    fn u32_from_bytes(bytes: &mut &[u8]) -> Option<u32> {
        let mut len = 0u32;
        for i in 0..4 {
            len <<= 0o10u32;
            len |= *bytes.get(i)? as u32;
        }
        *bytes = &bytes[4..];
        Some(len)
    }

    fn u16_from_bytes(bytes: &mut &[u8]) -> Option<u16> {
        let mut len = *bytes.get(0)? as u16;
        len <<= 0o10u16;
        len |= *bytes.get(1)? as u16;
        *bytes = &bytes[2..];
        Some(len)
    }
}