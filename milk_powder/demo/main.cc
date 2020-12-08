#include <milk_powder.h>

#include <cassert>
#include <iostream>
#include <utility>
#include <cstring>

namespace {

  constexpr size_t kCapaticy = 1024;

  bool gRes = false;
  
  uint8_t *gBuf = nullptr;

  uint32_t gLen = 0;

  void callback(const uint8_t *bytes, uint32_t length) {
    if (gBuf == nullptr) {
      gBuf = new uint8_t[kCapaticy];
      gLen = length;
      memcpy(gBuf, bytes, static_cast<size_t>(length));
    } else {
      gRes = gLen == length && memcmp(gBuf, bytes, static_cast<size_t>(length)) == 0;
      delete[] gBuf;
      gBuf = nullptr;
      gLen = 0;
    }
  }
} // namespace

int main(int argc, char *argv[]) {

  Midi midi(120);
  Track track;
  track.AddEvent(120, 0x90, 0x3c, 0x7f);
  SysexPackets sysex_packets;
  {
    uint8_t args[] = { 0x43, 0x12, 0x00 };
    sysex_packets.AddSysex(0, 3, args);
  }
  {
    uint8_t args[] = { 0x43, 0x12, 0x00, 0x43, 0x12, 0x00 };
    sysex_packets.AddSysex(200, 6, args);
  }
  {
    uint8_t args[] = { 0x43, 0x12, 0x00, 0xf7 };
    sysex_packets.AddSysex(100, 4, args);
  }
  track.AddSysexPackets(std::move(sysex_packets));
  midi.AddTrack(std::move(track));

  {
    Track p = midi.GetTrack(0);
    Track q = p;
    Track track = q;
    {
      Event p = track.GetEvent(1);
      assert(p.GetMode() == SYSEX);
      SysexPackets q = std::move(p);
      SysexPackets sysex_packets = q;
      track.AddSysexPackets(std::move(sysex_packets));
    }
    {
      Event e = track.GetEvent(0);
      uint32_t delta = e.GetDelta();
      uint8_t mode = e.GetMode();
      assert(mode != SYSEX && mode != META);
      uint8_t arg0, arg1;
      arg0 = e.GetArgs(&arg1);
      track.AddEvent(delta, mode, arg0, arg1);
    }
    midi.AddTrack(std::move(track));
  }

  std::cout << "dump" << std::endl;
  midi.Dump(callback);
  std::cout << "parse" << std::endl;
  Midi tmp = Midi::Parse(gBuf, gLen);
  Midi m = tmp;
  std::cout << "dump" << std::endl;
  m.Dump(callback);

  std::cout << gRes << std::endl;

  return 0;
}