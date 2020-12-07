use super::track::Track;

#[derive(Debug)]
#[derive(Clone)]
pub struct Midi {
    format: u16,
    ntrks: u16,
    division: u16,
    tracks: Vec<Track>,
}

impl Midi {

    pub fn new(format: u16, ntrks: u16, division: u16, tracks: Vec<Track>) -> Self {
        Self {
            format,
            ntrks,
            division,
            tracks,
        }
    }

    pub fn get_format(&self) -> u16 {
        self.format
    }

    pub fn get_ntrks(&self) -> u16 {
        self.ntrks
    }

    pub fn get_division(&self) -> u16 {
        self.division
    }

    pub fn get_track(&self, index: u16) -> Option<&Track> {
        self.tracks.get(index as usize)
    }

    pub fn add_track(&mut self, track: Track) {
        self.ntrks += 1u16;
        self.tracks.push(track);
    }
}