use super::super::*;

impl Midi {

    pub fn into_bytes(&self) -> Vec<u8> {
        let mut v = Vec::new();
        v.append(&mut VarLen::u16_into_bytes(self.get_format()));
        v.append(&mut VarLen::u16_into_bytes(self.get_ntrks()));
        v.append(&mut VarLen::u16_into_bytes(self.get_division()));
        let mut bytes = Vec::new();
        bytes.append(&mut String::from("MThd").into_bytes());
        bytes.append(&mut VarLen::u32_into_bytes(v.len() as u32));
        bytes.append(&mut v);
        for i in 0..self.get_ntrks() {
            bytes.append(&mut self.get_track(i).unwrap().into_bytes());
        }
        bytes
    }
}

impl Track {

    fn into_bytes(&self) -> Vec<u8> {
        let mut v = Vec::new();
        for i in 0..self.get_size() {
            v.append(&mut self.get_event(i).unwrap().into_bytes());
        }
        let mut bytes = Vec::new();
        bytes.append(&mut String::from("MTrk").into_bytes());
        bytes.append(&mut VarLen::u32_into_bytes(v.len() as u32));
        bytes.append(&mut v);
        bytes
    }
}

impl Event {

    fn into_bytes(&self) -> Vec<u8> {
        let mut bytes = Vec::new();
        bytes.append(&mut VarLen::usize_into_bytes(self.get_delta()));
        match self.get_mode() {
            0xffu8 => bytes.append(&mut self.cast_meta().unwrap().into_bytes()),
            0xf0u8 => bytes.append(&mut self.cast_sysex_packets().unwrap().into_bytes()),
            mode => {
                bytes.push(mode);
                let args = self.get_args().unwrap();
                bytes.push(args.0);
                if mode & 0xf0u8 != 0xc0u8 && mode & 0xf0u8 != 0xd0u8 {
                    bytes.push(args.1);
                }
            }
        }
        bytes
    }
}

impl Meta {

    fn into_bytes(&self) -> Vec<u8> {
        let mut bytes = Vec::new();
        bytes.push(0xffu8);
        bytes.push(self.get_mode());
        bytes.append(&mut VarLen::args_into_bytes(self.get_args()));
        bytes
    }
}

impl SysexPackets {

    fn into_bytes(&self) -> Vec<u8> {
        let mut bytes = Vec::new();
        bytes.push(0xf0u8);
        if let Some(sysex) = self.get_first() {
            bytes.append(&mut VarLen::args_into_bytes(sysex.get_args()));
        } else {
            return Vec::default();
        }
        self.get_packets().iter().for_each(|sysex| bytes.append(&mut sysex.into_bytes()));
        bytes
    }
}

impl Sysex {

    fn into_bytes(&self) -> Vec<u8> {
        let mut bytes = Vec::new();
        bytes.append(&mut VarLen::usize_into_bytes(self.get_delta()));
        bytes.push(0xf7u8);
        bytes.append(&mut VarLen::args_into_bytes(self.get_args()));
        bytes
    }
}

impl VarLen {

    fn args_into_bytes(args: &[u8]) -> Vec<u8> {
        let mut bytes = Vec::new();
        bytes.append(&mut Self::usize_into_bytes(args.len()));
        bytes.extend_from_slice(args);
        bytes
    }

    fn usize_into_bytes(mut len: usize) -> Vec<u8> {
        let mut bytes = Vec::new();
        bytes.push((len & 0x7fusize) as u8);
        len >>= 0o07usize;
        if len != 0 {
            loop  {
                bytes.push((len & 0x7fusize) as u8 | 0x80u8);
                len >>= 0o07usize;
                if len == 0usize {
                    break;
                }
            }
            bytes.reverse();
        }
        bytes
    }

    fn u32_into_bytes(mut len: u32) -> Vec<u8> {
        let mut bytes = vec!(0u8, 0u8, 0u8, 0u8);
        for i in 0..4 {
            bytes[3 - i] = (len & 0xffu32) as u8;
            len >>= 0o10u32;
        }
        bytes
    }

    fn u16_into_bytes(len: u16) -> Vec<u8> {
        vec!((len >> 0o10u16) as u8, (len & 0xffu16) as u8)
    }
}