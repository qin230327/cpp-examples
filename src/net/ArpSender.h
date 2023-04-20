#ifndef __ARPSENDER_H__
#define __ARPSENDER_H__

#include <array>
#include <cstdint>
#include <net/ethernet.h>

using std::uint16_t;
using std::uint8_t;

namespace net {
class ArpSender {
  private:
    class ArpPacket {
      public:
        // ethernet destination MAC
        uint8_t etherDstHost[ETH_ALEN];
        // ethernet source MAC
        uint8_t etherSrcHost[ETH_ALEN];
        // ethernet frame type(ARP frame: 0x0806)
        uint16_t etherType;
        // hardware type(ethernet: 0x1)
        uint16_t hardType;
        // protocol of upper layer(IP: 0x0800)
        uint16_t protocolType;
        // length of hardware address(MAC address)
        uint8_t hardLen;
        // length of upper protocol's address(IP address)
        uint8_t protocolLen;
        // operation code(arp req: 0x1; arp rsp: 0x2)
        uint16_t op;
        // source MAC
        uint8_t srcHard[ETH_ALEN];
        // source IP
        uint8_t srcIp[4];
        // destination MAC
        uint8_t dstHard[ETH_ALEN];
        // destination IP
        uint8_t dstIp[4];
    } __attribute__((__packed__));

  public:
    static bool broadcast(const std::array<uint8_t, ETH_ALEN> &srcMac,
                          const std::array<uint8_t, ETH_ALEN> &dstMac,
                          const std::array<uint8_t, 4> &srcIp,
                          const std::array<uint8_t, 4> &dstIp);
};
} // namespace net
#endif // __ARPSENDER_H__