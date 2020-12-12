#ifndef MILK_POWDER_H_
#define MILK_POWDER_H_

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

#include <stdint.h>

#define SYSEX ((uint8_t) 0xf0)
#define META ((uint8_t) 0xff)

struct Midi_t;
struct Track_t;
struct Event_t;
struct Meta_t;
struct SysexPackets_t;
struct Sysex_t;

const struct Midi_t *Midi_Parse(const uint8_t *bytes, uint32_t length);

uint16_t Midi_GetFormat(const struct Midi_t *midi);
uint16_t Midi_GetNtrks(const struct Midi_t *midi);
uint16_t Midi_GetDivision(const struct Midi_t *midi);
const struct Track_t *Midi_GetTrack(const struct Midi_t *midi, uint16_t index);

uint32_t Track_GetSize(const struct Track_t *track);
const struct Event_t *Track_GetEvent(const struct Track_t *track, uint32_t index);

uint32_t Event_GetDelta(const struct Event_t *event);
uint8_t Event_GetMode(const struct Event_t *event);
uint8_t Event_GetArgs(const struct Event_t *event, uint8_t *arg);
const struct Meta_t *Event_CastMeta(const struct Event_t *event);
const struct SysexPackets_t *Event_CastSysexPackets(const struct Event_t *event);

uint8_t Meta_GetMode(const struct Meta_t *meta);
uint32_t Meta_GetArgc(const struct Meta_t *meta);
void Meta_GetArgv(const struct Meta_t *meta, uint8_t *argv);

uint32_t SysexPackets_GetSize(const struct SysexPackets_t *sysex_packets);
const struct Sysex_t *SysexPackets_GetSysex(const struct SysexPackets_t *sysex_packets, uint32_t index);

uint32_t Sysex_GetDelta(const struct Sysex_t *sysex);
uint32_t Sysex_GetArgc(const struct Sysex_t *sysex);
void Sysex_GetArgv(const struct Sysex_t *sysex, uint8_t *argv);

void Midi_Destroy(const struct Midi_t *midi);
struct Midi_t *Midi_Clone(const struct Midi_t *midi);
void Track_Destory(const struct Track_t *track);
struct Track_t *Track_Clone(const struct Track_t *track);
void Event_Destory(const struct Event_t *event);
struct Event_t *Event_Clone(const struct Event_t *event);
void Meta_Destory(const struct Meta_t *meta);
struct Meta_t *Meta_Clone(const struct Meta_t *meta);
void SysexPackets_Destory(const struct SysexPackets_t *sysex_packets);
struct SysexPackets_t *SysexPackets_Clone(const struct SysexPackets_t *sysex_packets);
void Sysex_Destory(const struct Sysex_t *sysexs);
struct Sysex_t *Sysex_Clone(const struct Sysex_t *sysexs);

struct Midi_t *Midi_Create(uint16_t division);
void Midi_AddTrack(struct Midi_t *midi, struct Track_t *track);

struct Track_t *Track_Create();
void Track_AddEvent(struct Track_t *track, uint32_t delta, uint8_t mode, uint8_t arg0, uint8_t arg1);
void Track_AddMeta(struct Track_t *track, uint32_t delta, uint8_t mode, uint32_t argc, const uint8_t *argv);
void Track_AddSysexPackets(struct Track_t *track, struct SysexPackets_t *sysex_packets);

struct SysexPackets_t *SysexPackets_Create();
void SysexPackets_AddSysex(struct SysexPackets_t *sysex_packets, uint32_t delta, uint32_t argc, const uint8_t *argv);

typedef void (*DumpFunction)(void *receiver, const uint8_t *bytes, uint32_t length);
void Midi_Dump(const struct Midi_t *midi, DumpFunction callback, void *receiver);

#define NOTE_OFF(channel) ((uint8_t) (0x80 | (channel)))
#define NOTE_ON(channel) ((uint8_t) (0x90 | (channel)))
#define REGISTERED_PARAMETER_NUMBERS(channel) ((uint8_t) (0xa0 | (channel)))
#define CONTROL_CHANGE(channel) ((uint8_t) (0xb0 | (channel)))
#define PROGRAM_CHANGE(channel) ((uint8_t) (0xc0 | (channel)))
#define CHANNEL_PRESSURE(channel) ((uint8_t) (0xd0 | (channel)))
#define PITCH_BEND(channel) ((uint8_t) (0xe0 | (channel)))

#ifdef __cplusplus
}
#endif // ifdef __cplusplus

#ifdef __cplusplus

#include <functional>

#include <cassert>

namespace milk_powder {

class Sysex {

private:
  const Sysex_t *sysex_;

private:
  Sysex(const Sysex_t *sysex)
  : sysex_(sysex) {
    assert(sysex_ != nullptr);
  }

  Sysex(const Sysex &) = delete;

  Sysex &operator=(const Sysex &);

  Sysex &operator=(Sysex &&);

public:
  Sysex(Sysex &&sysex)
  : Sysex(sysex.sysex_) {
    sysex.sysex_ = nullptr;
  }

  ~Sysex() = default;

  uint32_t GetDelta() const {
    return Sysex_GetDelta(sysex_);
  }

  uint8_t GetMode() const {
    return Sysex_GetArgc(sysex_);
  }

  void GetArgv(uint8_t *argv) const {
    Sysex_GetArgv(sysex_, argv);
  }

  friend class SysexPackets;
};

class SysexPackets {

private:
  SysexPackets_t *sysex_packets_;

  const bool mut_;

private:
  SysexPackets(SysexPackets_t *sysex_packets, bool mut = false)
  : sysex_packets_(sysex_packets)
  , mut_(mut) {
    assert(sysex_packets_ != nullptr);
  }

  SysexPackets &operator=(const SysexPackets &);
  
  SysexPackets &operator=(SysexPackets &&);

public:
  SysexPackets()
  : SysexPackets(SysexPackets_Create(), true) {
  }

  SysexPackets(const SysexPackets &sysex_packets)
  : SysexPackets(SysexPackets_Clone(sysex_packets.sysex_packets_), true) {
  }

  SysexPackets(SysexPackets &&sysex_packets)
  : SysexPackets(sysex_packets.sysex_packets_, sysex_packets.mut_) {
    sysex_packets.sysex_packets_ = nullptr;
  }

  ~SysexPackets() {
    if (mut_ && sysex_packets_ != nullptr) {
      SysexPackets_Destory(sysex_packets_);
    }
  }

  uint32_t GetSize() const {
    return SysexPackets_GetSize(sysex_packets_);
  }

  Sysex GetSysex(uint32_t index) const {
    return Sysex(SysexPackets_GetSysex(sysex_packets_, index));
  }

  void AddSysex(uint32_t delta, uint32_t argc, const uint8_t *argv) {
    assert(mut_);
    SysexPackets_AddSysex(sysex_packets_, delta, argc, argv);
  }

  friend class Event;
  friend class Track;
};

class Meta {

private:
  const Meta_t *meta_;

private:
  Meta(const Meta_t *meta)
  : meta_(meta) {
    assert(meta_ != nullptr);
  }

  Meta(const Meta &) = delete;

  Meta &operator=(const Meta &);
  
  Meta &operator=(Meta &&);

public:
  Meta(Meta &&meta)
  : Meta(meta.meta_) {
    meta.meta_ = nullptr;
  }

  ~Meta() = default;

  uint8_t GetMode() const {
    return Meta_GetMode(meta_);
  }

  uint32_t GetArgc() const {
    return Meta_GetArgc(meta_);
  }

  void GetArgv(uint8_t *argv) const {
    Meta_GetArgv(meta_, argv);
  }

  friend class Event;
};

class Event {

private:
  const Event_t *event_;

private:
  Event(const Event_t *event)
  : event_(event) {
    assert(event_ != nullptr);
  }

  Event(const Event &) = delete;

  Event &operator=(const Event &);
  
  Event &operator=(Event &&);

public:
  Event(Event &&event)
  : Event(event.event_) {
    event.event_ = nullptr;
  }

  ~Event() = default;

  uint32_t GetDelta() const {
    return Event_GetDelta(event_);
  }

  uint8_t GetMode() const {
    return Event_GetMode(event_);
  }

  uint8_t GetArgs(uint8_t *arg) const {
    return Event_GetArgs(event_, arg);
  }

  operator Meta() && {
    Meta meta(Event_CastMeta(event_));
    event_ = nullptr;
    return meta;
  }

  operator SysexPackets() && {
    SysexPackets sysex_packets(const_cast<SysexPackets_t *>(Event_CastSysexPackets(event_)));
    event_ = nullptr;
    return sysex_packets;
  }

  friend class Track;
};

class Track {

private:
  Track_t *track_;

  const bool mut_;

private:
  Track(Track_t *track, bool mut = false)
  : track_(track)
  , mut_(mut) {
    assert(track_ != nullptr);
  }

  Track &operator=(const Track &);
  
  Track &operator=(Track &&);

public:
  Track()
  : Track(Track_Create(), true) {
  }

  Track(const Track &track)
  : Track(Track_Clone(track.track_), true) {
  }

  Track(Track &&track)
  : Track(track.track_, track.mut_) {
    track.track_ = nullptr;
  }

  ~Track() {
    if (mut_ && track_ != nullptr) {
      Track_Destory(track_);
    }
  }

  uint32_t GetSize() const {
    return Track_GetSize(track_);
  }

  Event GetEvent(uint32_t index) const {
    return Event(Track_GetEvent(track_, index));
  }

  void AddEvent(uint32_t delta, uint8_t mode, uint8_t arg0, uint8_t arg1) {
    assert(mut_);
    Track_AddEvent(track_, delta, mode, arg0, arg1);
  }

  void AddMeta(uint32_t delta, uint8_t mode, uint8_t argc, const uint8_t *argv) {
    assert(mut_);
    Track_AddMeta(track_, delta, mode, argc, argv);
  }

  void AddSysexPackets(SysexPackets &&sysex_packets) {
    assert(mut_);
    assert(sysex_packets.mut_ && sysex_packets.sysex_packets_ != nullptr);
    Track_AddSysexPackets(track_, sysex_packets.sysex_packets_);
    sysex_packets.sysex_packets_ = nullptr;
  }

  friend class Midi;
};

class Midi {

public:
  static Midi Parse(const uint8_t *bytes, uint32_t length) {
    return Midi(const_cast<Midi_t *>(Midi_Parse(bytes, length)));
  }

private:
  using DumpReceiver = std::function<void(const uint8_t *, uint32_t)>;
  static void DumpCallback(DumpReceiver &receiver, const uint8_t *bytes, uint32_t length) {
    receiver(bytes, length);
  }

public:
  void Dump(DumpReceiver receiver) const {
    Midi_Dump(midi_, reinterpret_cast<DumpFunction>(&DumpCallback), &receiver);
  }

private:
  Midi_t *midi_;

private:
  Midi(Midi_t *midi)
  : midi_(midi) {
    assert(midi_ != nullptr);
  }

  Midi &operator=(const Midi &);
  
  Midi &operator=(Midi &&);
  
public:
  Midi(uint16_t division)
  : Midi(Midi_Create(division)) {
  }

  Midi(const Midi &midi)
  : Midi(Midi_Clone(midi.midi_)) {
  }

  Midi(Midi &&midi)
  : Midi(midi.midi_) {
    midi.midi_ = nullptr;
  }

  ~Midi() {
    Midi_Destroy(midi_);
  }

  uint16_t GetFormat() const {
    return Midi_GetFormat(midi_);
  }

  uint16_t GetNtrks() const {
    return Midi_GetNtrks(midi_);
  }

  uint16_t GetDivision() const {
    return Midi_GetDivision(midi_);
  }

  Track GetTrack(uint16_t index) const {
    return Track(const_cast<Track_t *>(Midi_GetTrack(midi_, index)));
  }

  void AddTrack(Track &&track) {
    assert(track.mut_ && track.track_ != nullptr);
    Midi_AddTrack(midi_, track.track_);
    track.track_ = nullptr;
  }
};

} // namespace milk_powder

#endif // ifdef __cplusplus

#endif // ifndef MILK_POWDER_H_