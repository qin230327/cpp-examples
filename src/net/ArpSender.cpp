#include "ArpSender.h"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <net/if.h>
#include <netpacket/packet.h>
#include <sys/socket.h>
#include <unistd.h>

namespace net {
bool ArpSender::broadcast(const std::array<uint8_t, ETH_ALEN> &srcMac,
                          const std::array<uint8_t, ETH_ALEN> &dstMac,
                          const std::array<uint8_t, 4> &srcIp,
                          const std::array<uint8_t, 4> &dstIp) {

    ArpPacket packet;
    memcpy(packet.etherDstHost, dstMac.data(), ETH_ALEN);
    memcpy(packet.etherSrcHost, srcMac.data(), ETH_ALEN);
    packet.etherType = htons(ETH_P_ARP);
    packet.hardType = htons(0x01);
    packet.protocolType = htons(ETH_P_IP);
    packet.hardLen = ETH_ALEN;
    packet.protocolLen = 4;
    packet.op = htons(0x01);
    memcpy(packet.srcHard, packet.etherSrcHost, ETH_ALEN);
    memcpy(packet.srcIp, srcIp.data(), 4);
    memcpy(packet.dstHard, packet.etherDstHost, ETH_ALEN);
    memcpy(packet.dstIp, dstIp.data(), 4);

    auto fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (fd < 0) {
        std::cerr << "socket error" << std::endl;
        return false;
    }

    struct sockaddr_ll sll;
    memset(&sll, 0, sizeof(sll));
    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = IFF_BROADCAST;

    auto res =
        sendto(fd, &packet, sizeof(packet), 0, (sockaddr *)&sll, sizeof(sll));
    if (res <= 0) {
        std::cerr << "send error" << std::endl;
        return false;
    }
    close(fd);
    return true;
}
} // namespace net