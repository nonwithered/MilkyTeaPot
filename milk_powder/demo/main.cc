#include <milk_powder.h>

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

  std::cout << "dump" << std::endl;
  midi.Dump(callback);
  std::cout << "parse" << std::endl;
  Midi m = Midi::Parse(gBuf, gLen);
  std::cout << "dump" << std::endl;
  m.Dump(callback);

  std::cout << gRes << std::endl;

  return 0;
}