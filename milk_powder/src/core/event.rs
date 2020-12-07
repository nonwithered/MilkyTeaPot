use super::meta::Meta;
use super::sysex::SysexPackets;

#[derive(Debug)]
#[derive(Clone)]
pub struct Event {
    delta: VarLen,
    msg: Msg,
}

#[derive(Debug)]
#[derive(Clone)]
pub struct VarLen(pub usize);

#[derive(Debug)]
#[derive(Clone)]
enum Msg {
    Event {
        mode: u8,
        args: (u8, u8),
    },
    Meta(Meta),
    SysexPackets(SysexPackets),
}

impl Event {

    pub fn new(delta: usize, mode: u8, args: (u8, u8)) -> Self {
        Self {
            delta: VarLen::from(delta),
            msg: Msg::Event { mode, args },
        }
    }

    pub fn new_meta(delta: usize, meta: Meta) -> Self {
        Self {
            delta: VarLen::from(delta),
            msg: Msg::Meta(meta),
        }
    }

    pub fn new_sysex_packets(sysex_packets: SysexPackets) -> Self {
        Self {
            delta: if let Some(sysex) = sysex_packets.get_first() {
                VarLen::from(sysex.get_delta())
            } else {
                VarLen::default()
            },
            msg: Msg::SysexPackets(sysex_packets),
        }
    }

    pub fn get_delta(&self) -> usize {
        self.delta.0
    }

    pub fn get_mode(&self) -> u8 {
        match &self.msg {
            Msg::Event { mode, .. } => *mode,
            Msg::Meta(_) => 0xffu8,
            Msg::SysexPackets(_) => 0xf0u8,
        }
    }

    pub fn get_args(&self) -> Option<(u8, u8)> {
        if let Msg::Event { args, .. } = &self.msg {
            Some(*args)
        } else {
            None
        }
    }

    pub fn cast_meta(&self) -> Option<&Meta> {
        if let Msg::Meta(meta) = &self.msg {
            Some(meta)
        } else {
            None
        }
    }

    pub fn cast_sysex_packets(&self) -> Option<&SysexPackets> {
        if let Msg::SysexPackets(sysex_packets) = &self.msg {
            Some(sysex_packets)
        } else {
            None
        }
    }
}

impl Default for VarLen {

    fn default() -> Self {
        Self(0usize)
    }
}

impl From<usize> for VarLen {

    fn from(var_len: usize) -> Self {
        Self(var_len)
    }
}
