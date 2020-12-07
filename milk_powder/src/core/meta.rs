#[derive(Debug)]
#[derive(Clone)]
pub struct Meta {
    mode: u8,
    args: Vec<u8>,
}

impl Meta {

    pub fn new(mode: u8, args: Vec<u8>) -> Self {
        Self {
            mode, 
            args,
        }
    }

    pub fn get_mode(&self) -> u8 {
        self.mode
    }

    pub fn get_args(&self) -> &[u8] {
        &self.args.as_slice()
    }
}