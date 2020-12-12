#include <milk_powder.h>

#include <cassert>
#include <iostream>
#include <utility>
#include <cstring>

int main(int argc, char *argv[]) {

  milk_powder::Midi midi(120);
  milk_powder::Track track;
  track.AddEvent(120, 0x90, 0x3c, 0x7f);
  milk_powder::SysexPackets sysex_packets;
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
    milk_powder::Track p = midi.GetTrack(0);
    milk_powder::Track q = p;
    milk_powder::Track track = q;
    {
      milk_powder::Event p = track.GetEvent(1);
      assert(p.GetMode() == SYSEX);
      milk_powder::SysexPackets q = std::move(p);
      milk_powder::SysexPackets sysex_packets = q;
      track.AddSysexPackets(std::move(sysex_packets));
    }
    {
      milk_powder::Event e = track.GetEvent(0);
      uint32_t delta = e.GetDelta();
      uint8_t mode = e.GetMode();
      assert(mode != SYSEX && mode != META);
      uint8_t arg0, arg1;
      arg0 = e.GetArgs(&arg1);
      track.AddEvent(delta, mode, arg0, arg1);
    }
    midi.AddTrack(std::move(track));
  }

  constexpr size_t kCapacity = 1024;
  uint8_t buf[kCapacity];
  uint32_t len = 0;
  bool res = false;

  std::cout << "dump" << std::endl;
  midi.Dump([&] (const uint8_t *bytes, uint32_t length) {
      len = length;
      memcpy(buf, bytes, static_cast<size_t>(length));
  });
  std::cout << "parse" << std::endl;
  milk_powder::Midi tmp = milk_powder::Midi::Parse(buf, len);
  milk_powder::Midi m = tmp;
  std::cout << "dump" << std::endl;
  m.Dump([&] (const uint8_t *bytes, uint32_t length) {
      res = len == length && memcmp(buf, bytes, static_cast<size_t>(length)) == 0;
  });
  for (auto i = 0; i != len; ++i) {
    std::cout << i << ": " << int(buf[i]) << std::endl;
  }

  std::cout << res << std::endl;

  return 0;
}