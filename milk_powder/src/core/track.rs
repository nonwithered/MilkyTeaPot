use super::event::Event;
use super::meta::Meta;
use super::sysex::SysexPackets;

#[derive(Debug)]
#[derive(Clone)]
pub struct Track {
    events: Vec<Event>,
}

impl Track {

    pub fn new() -> Self {
        Self {
            events: Vec::new(),
        }
    }

    pub fn get_size(&self) -> u32 {
        self.events.len() as u32
    }

    pub fn get_event(&self, index: u32) -> Option<&Event> {
        self.events.get(index as usize)
    }

    pub fn add_event(&mut self, delta: usize, mode: u8, args: (u8, u8)) {
        self.add(Event::new(delta, mode, args));
    }

    pub fn add_meta(&mut self, delta: usize, mode: u8, args: Vec<u8>) {
        self.add(Event::new_meta(delta, Meta::new(mode, args)));
    }

    pub fn add_sysex_packets(&mut self, sysex_packets: SysexPackets) {
        self.add(Event::new_sysex_packets(sysex_packets));
    }

    pub fn add(&mut self, event: Event) {
        self.events.push(event);
    }
}