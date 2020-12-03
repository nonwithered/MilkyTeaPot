use super::event::VarLen;

#[derive(Debug)]
pub struct SysexPackets {
    packets: Vec<Sysex>,
}

#[derive(Debug)]
pub struct Sysex {
    delta: VarLen,
    args: Vec<u8>,
}

impl SysexPackets {

    pub fn new(packets: Vec<Sysex>) -> Self {
        Self {
            packets,
        }
    }

    pub fn get_packets(&self) -> &[Sysex] {
        &self.packets[1..]
    }

    pub fn get_first(&self) -> Option<&Sysex> {
        self.packets.first()
    }

    pub fn get_size(&self) -> usize {
        self.packets.len()
    }

    pub fn get_sysex(&self, index: usize) -> Option<&Sysex> {
        self.packets.get(index)
    }

    pub fn add_sysex(&mut self, delta: usize, args: Vec<u8>) {
        self.packets.push(Sysex::new(delta, args));
    }
}

impl Sysex {

    pub fn new(delta: usize, args: Vec<u8>) -> Self {
        Self {
            delta: VarLen::from(delta),
            args,
        }
    }

    pub fn get_delta(&self) -> usize {
        self.delta.0
    }

    pub fn get_args(&self) -> &[u8] {
        &self.args.as_slice()
    }
}