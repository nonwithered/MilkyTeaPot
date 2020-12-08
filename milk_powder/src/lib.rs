mod core;
mod serialize;

pub use self::core::*;
pub use self::serialize::*;

#[no_mangle]
pub extern "C" fn Midi_Parse(bytes_ptr: *const u8, length: u32) -> *const Midi {
    let bytes = unsafe { std::slice::from_raw_parts(bytes_ptr, length as usize) };
    if let Some(midi) = Midi::from_bytes(bytes) {
        return Box::into_raw(Box::new(midi));
    }
    std::ptr::null()
}

#[no_mangle]
pub extern "C" fn Midi_GetFormat(midi_ptr: *const Midi) -> u16 {
    if let Some(midi) = unsafe { midi_ptr.as_ref() } {
        return midi.get_format();
    }
    0u16
}

#[no_mangle]
pub extern "C" fn Midi_GetNtrks(midi_ptr: *const Midi) -> u16 {
    if let Some(midi) = unsafe { midi_ptr.as_ref() } {
        return midi.get_ntrks();
    }
    0u16
}

#[no_mangle]
pub extern "C" fn Midi_GetDivision(midi_ptr: *const Midi) -> u16 {
    if let Some(midi) = unsafe { midi_ptr.as_ref() } {
        return midi.get_division();
    }
    0u16
}

#[no_mangle]
pub extern "C" fn Midi_GetTrack(midi_ptr: *const Midi, index: u16) -> *const Track {
    if let Some(midi) = unsafe { midi_ptr.as_ref() } {
        if let Some(track) = midi.get_track(index) {
            return track as *const Track;
        }
    }
    std::ptr::null()
}

#[no_mangle]
pub extern "C" fn Track_GetSize(track_ptr: *const Track) -> u32 {
    if let Some(track) = unsafe { track_ptr.as_ref() } {
        return track.get_size();
    }
    0u32
}

#[no_mangle]
pub extern "C" fn Track_GetEvent(track_ptr: *const Track, index: u32) -> *const Event {
    if let Some(track) = unsafe { track_ptr.as_ref() } {
        if let Some(event) = track.get_event(index) {
            return event as *const Event;
        }
    }
    std::ptr::null()
}

#[no_mangle]
pub extern "C" fn Event_GetDelta(event_ptr: *const Event) -> u32 {
    if let Some(event) = unsafe { event_ptr.as_ref() } {
        return event.get_delta() as u32;
    }
    0u32
}

#[no_mangle]
pub extern "C" fn Event_GetMode(event_ptr: *const Event) -> u8 {
    if let Some(event) = unsafe { event_ptr.as_ref() } {
        return event.get_mode();
    }
    0u8
}

#[no_mangle]
pub extern "C" fn Event_GetArgs(event_ptr: *const Event, arg_ptr: *mut u8) -> u8 {
    if let Some(event) = unsafe { event_ptr.as_ref() } {
        if let Some(args) = event.get_args() {
            if !arg_ptr.is_null() {
                let arg = args.1;
                unsafe { *arg_ptr = arg; }
            }
            return args.0;
        }
    }
    if !arg_ptr.is_null() {
        let arg = 0u8;
        unsafe { *arg_ptr = arg; }
    }
    0u8
}

#[no_mangle]
pub extern "C" fn Event_CastMeta(event_ptr: *const Event) -> *const Meta {
    if let Some(event) = unsafe { event_ptr.as_ref() } {
        if let Some(meta) = event.cast_meta() {
            return meta as *const Meta;
        }
    }
    std::ptr::null()
}

#[no_mangle]
pub extern "C" fn Event_CastSysexPackets(event_ptr: *const Event) -> *const SysexPackets {
    if let Some(event) = unsafe { event_ptr.as_ref() } {
        if let Some(sysex_packets) = event.cast_sysex_packets() {
            return sysex_packets as *const SysexPackets;
        }
    }
    std::ptr::null()
}

#[no_mangle]
pub extern "C" fn Meta_GetMode(meta_ptr: *const Meta) -> u8 {
    if let Some(meta) = unsafe { meta_ptr.as_ref() } {
        return meta.get_mode();
    }
    0u8
}

#[no_mangle]
pub extern "C" fn Meta_GetArgc(meta_ptr: *const Meta) -> u32 {
    if let Some(meta) = unsafe { meta_ptr.as_ref() } {
        return meta.get_args().len() as u32;
    }
    0u32
}

#[no_mangle]
pub extern "C" fn Meta_GetArgv(meta_ptr: *const Meta, argv_ptr: *mut u8) {
    if let Some(meta) = unsafe { meta_ptr.as_ref() } {
        let args = meta.get_args();
        let argc = args.len();
        let argv = unsafe { std::slice::from_raw_parts_mut(argv_ptr, argc) };
        for i in 0..argc {
            argv[i] = args[i];
        }
    }
}

#[no_mangle]
pub extern "C" fn SysexPackets_GetSize(sysex_packets_ptr: *const SysexPackets) -> u32 {
    if let Some(sysex_packets) = unsafe { sysex_packets_ptr.as_ref() } {
        return sysex_packets.get_size() as u32;
    }
    0u32
}

#[no_mangle]
pub extern "C" fn SysexPackets_GetSysex(sysex_packets_ptr: *const SysexPackets, index: u32) -> *const Sysex {
    if let Some(sysex_packets) = unsafe { sysex_packets_ptr.as_ref() } {
        if let Some(sysex) = sysex_packets.get_sysex(index as usize) {
            return sysex as *const Sysex;
        }
    }
    std::ptr::null()
}

#[no_mangle]
pub extern "C" fn Sysex_GetDelta(sysex_ptr: *const Sysex) -> u32 {
    if let Some(sysex) = unsafe { sysex_ptr.as_ref() } {
        return sysex.get_delta() as u32;
    }
    0u32
}

#[no_mangle]
pub extern "C" fn Sysex_GetArgc(sysex_ptr: *const Sysex) -> u32 {
    if let Some(sysex) = unsafe { sysex_ptr.as_ref() } {
        return sysex.get_args().len() as u32;
    }
    0u32
}

#[no_mangle]
pub extern "C" fn Sysex_GetArgv(sysex_ptr: *const Sysex, argv_ptr: *mut u8) {
    if let Some(sysex) = unsafe { sysex_ptr.as_ref() } {
        let args = sysex.get_args();
        let argc = args.len();
        let argv = unsafe { std::slice::from_raw_parts_mut(argv_ptr, argc) };
        for i in 0..argc {
            argv[i] = args[i];
        }
    }
}

#[no_mangle]
pub extern "C" fn Midi_Destroy(midi_ptr: *const Midi) {
    if let Some(midi) = unsafe { midi_ptr.as_ref() } {
        unsafe { std::ptr::drop_in_place(midi_ptr as *mut Midi); }
        let layout = std::alloc::Layout::for_value(midi);
        unsafe { std::alloc::dealloc(midi_ptr as *mut u8, layout); }
    }
}

#[no_mangle]
pub extern "C" fn Midi_Clone(midi_ptr: *const Midi) -> *mut Midi {
    if let Some(midi) = unsafe { midi_ptr.as_ref() } {
        return Box::into_raw(Box::new(midi.clone()));
    }
    std::ptr::null_mut()
}

#[no_mangle]
pub extern "C" fn Track_Destory(track_ptr: *const Track) {
    if let Some(track) = unsafe { track_ptr.as_ref() } {
        unsafe { std::ptr::drop_in_place(track_ptr as *mut Track); }
        let layout = std::alloc::Layout::for_value(track);
        unsafe { std::alloc::dealloc(track_ptr as *mut u8, layout); }
    }
}

#[no_mangle]
pub extern "C" fn Track_Clone(track_ptr: *const Track) -> *mut Track {
    if let Some(track) = unsafe { track_ptr.as_ref() } {
        return Box::into_raw(Box::new(track.clone()));
    }
    std::ptr::null_mut()
}

#[no_mangle]
pub extern "C" fn Event_Destory(event_ptr: *const Event) {
    if let Some(event) = unsafe { event_ptr.as_ref() } {
        unsafe { std::ptr::drop_in_place(event_ptr as *mut Event); }
        let layout = std::alloc::Layout::for_value(event);
        unsafe { std::alloc::dealloc(event_ptr as *mut u8, layout); }
    }
}

#[no_mangle]
pub extern "C" fn Event_Clone(event_ptr: *const Event) -> *mut Event {
    if let Some(event) = unsafe { event_ptr.as_ref() } {
        return Box::into_raw(Box::new(event.clone()));
    }
    std::ptr::null_mut()
}

#[no_mangle]
pub extern "C" fn Meta_Destory(meta_ptr: *const Meta) {
    if let Some(meta) = unsafe { meta_ptr.as_ref() } {
        unsafe { std::ptr::drop_in_place(meta_ptr as *mut Meta); }
        let layout = std::alloc::Layout::for_value(meta);
        unsafe { std::alloc::dealloc(meta_ptr as *mut u8, layout); }
    }
}

#[no_mangle]
pub extern "C" fn Meta_Clone(meta_ptr: *const Meta) -> *mut Meta {
    if let Some(meta) = unsafe { meta_ptr.as_ref() } {
        return Box::into_raw(Box::new(meta.clone()));
    }
    std::ptr::null_mut()
}

#[no_mangle]
pub extern "C" fn SysexPackets_Destory(sysex_packets_ptr: *const SysexPackets) {
    if let Some(sysex_packets) = unsafe { sysex_packets_ptr.as_ref() } {
        unsafe { std::ptr::drop_in_place(sysex_packets_ptr as *mut SysexPackets); }
        let layout = std::alloc::Layout::for_value(sysex_packets);
        unsafe { std::alloc::dealloc(sysex_packets_ptr as *mut u8, layout); }
    }
}

#[no_mangle]
pub extern "C" fn SysexPackets_Clone(sysex_packets_ptr: *const SysexPackets) -> *mut SysexPackets {
    if let Some(sysex_packets) = unsafe { sysex_packets_ptr.as_ref() } {
        return Box::into_raw(Box::new(sysex_packets.clone()));
    }
    std::ptr::null_mut()
}

#[no_mangle]
pub extern "C" fn Sysex_Destory(sysex_ptr: *const Sysex) {
    if let Some(sysex) = unsafe { sysex_ptr.as_ref() } {
        unsafe { std::ptr::drop_in_place(sysex_ptr as *mut Sysex); }
        let layout = std::alloc::Layout::for_value(sysex);
        unsafe { std::alloc::dealloc(sysex_ptr as *mut u8, layout); }
    }
}

#[no_mangle]
pub extern "C" fn Sysex_Clone(sysex_ptr: *const Sysex) -> *mut Sysex {
    if let Some(sysex) = unsafe { sysex_ptr.as_ref() } {
        return Box::into_raw(Box::new(sysex.clone()));
    }
    std::ptr::null_mut()
}

#[no_mangle]
pub extern "C" fn Midi_Create(division: u16) -> *mut Midi {
    Box::into_raw(Box::new(Midi::new(0x0001u16, 0x0000u16, division, Vec::new())))
}

#[no_mangle]
pub extern "C" fn Midi_AddTrack(midi_ptr: *mut Midi, track_ptr: *mut Track) {
    if let Some(midi) = unsafe { midi_ptr.as_mut() } {
        let track = unsafe { Box::from_raw(track_ptr) };
        midi.add_track(*track);
    }
}

#[no_mangle]
pub extern "C" fn Track_Create() -> *mut Track {
    Box::into_raw(Box::new(Track::new()))
}

#[no_mangle]
pub extern "C" fn Track_AddEvent(track_ptr: *mut Track, delta: u32, mode: u8, arg0: u8, arg1: u8) {
    if let Some(track) = unsafe { track_ptr.as_mut() } {
        track.add_event(delta as usize, mode, (arg0, arg1));
    }
}

#[no_mangle]
pub extern "C" fn Track_AddMeta(track_ptr: *mut Track, delta: u32, mode: u8, argc: u32, argv_ptr: *const u8) {
    if let Some(track) = unsafe { track_ptr.as_mut() } {
        let argv = unsafe { std::slice::from_raw_parts(argv_ptr, argc as usize) };
        let mut args = Vec::new();
        args.extend_from_slice(argv);
        track.add_meta(delta as usize, mode, args);
    }
}

#[no_mangle]
pub extern "C" fn Track_AddSysexPackets(track_ptr: *mut Track, sysex_packets_ptr: *mut SysexPackets) {
    if let Some(track) = unsafe { track_ptr.as_mut() } {
        let sysex_packets = unsafe { Box::from_raw(sysex_packets_ptr) };
        track.add_sysex_packets(*sysex_packets);
    }
}

#[no_mangle]
pub extern "C" fn SysexPackets_Create() -> *mut SysexPackets {
    Box::into_raw(Box::new(SysexPackets::new(Vec::new())))
}

#[no_mangle]
pub extern "C" fn SysexPackets_AddSysex(sysex_packets_ptr: *mut SysexPackets, delta: u32, argc: u32, argv_ptr: *const u8) {
    if let Some(sysex_packets) = unsafe { sysex_packets_ptr.as_mut() } {
        let argv = unsafe { std::slice::from_raw_parts(argv_ptr, argc as usize) };
        let mut args = Vec::new();
        args.extend_from_slice(argv);
        sysex_packets.add_sysex(delta as usize, args);
    }
}

#[no_mangle]
pub extern "C" fn Midi_Dump(midi_ptr: *const Midi, callback: unsafe extern "C" fn(receiver_ptr: *mut u8, bytes_ptr: *const u8, length: u32), receiver_ptr: *mut u8) {
    if let Some(midi) = unsafe { midi_ptr.as_ref() } {
        let bytes = midi.into_bytes();
        let bytes_ptr = bytes.as_ptr();
        let length = bytes.len() as u32;
        unsafe { callback(receiver_ptr, bytes_ptr, length); }
    } else {
        let bytes_ptr = std::ptr::null();
        let length = 0u32;
        unsafe { callback(receiver_ptr, bytes_ptr, length); }
    }
}