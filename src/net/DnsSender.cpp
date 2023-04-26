#include "DnsSender.h"
#include "UdpSender.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/format.hpp>
#include <ctime>
#include <ios>
#include <iostream>
#include <netinet/in.h>
#include <random>

namespace net {
std::shared_ptr<std::vector<std::uint8_t>>
DnsSender::send(string domain, uint16_t localPort, string dnsIp,
                uint16_t dnsPort, bool queryRecur) {

    std::uint16_t transactionId = htons(genTranId());
    std::uint16_t flags =
        htons(queryRecur ? 0b0000000100000000 : 0b0000000000000000);
    std::uint16_t questions = htons(0x0001);
    std::uint16_t answerRRs = htons(0x0000);
    std::uint16_t authorityRRs = htons(0x0000);
    std::uint16_t additionalRRs = htons(0x0000);
    std::uint16_t queryType = htons(0x0001);
    std::uint16_t queryClass = htons(0x0001);
    auto queryNamePtr = genQryName(domain);

    std::size_t idx = 0, len = 16 + queryNamePtr->size();
    std::uint8_t bytePtr[len];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&transactionId)[0];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&transactionId)[1];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&flags)[0];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&flags)[1];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&questions)[0];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&questions)[1];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&answerRRs)[0];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&answerRRs)[1];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&authorityRRs)[0];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&authorityRRs)[1];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&additionalRRs)[0];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&additionalRRs)[1];
    for (auto &i : *queryNamePtr) {
        bytePtr[idx++] = i;
    }
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&queryType)[0];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&queryType)[1];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&queryClass)[0];
    bytePtr[idx++] = reinterpret_cast<std::uint8_t *>(&queryClass)[1];

    vector<std::uint8_t> bytes;
    for (auto i = 0; i < len; i++) {
        bytes.push_back(bytePtr[i]);
    }
    return UdpSender::send(bytes, localPort, dnsIp, dnsPort);
}

std::uint16_t DnsSender::genTranId() {
    std::default_random_engine engine(
        static_cast<std::uint16_t>(time(nullptr)));
    std::uniform_int_distribution<std::uint16_t> distribution(0, 65535);
    auto tranId = distribution(engine);
    boost::format fmt("dns request transaction id: 0x%x");
    std::cout << (fmt % tranId) << std::endl;
    return tranId;
}

std::shared_ptr<std::vector<std::uint8_t>>
DnsSender::genQryName(std::string domain) {
    std::vector<string> domainSplit;
    boost::split(domainSplit, domain, boost::is_any_of("."));

    auto ptr = std::make_shared<std::vector<std::uint8_t>>();
    for (auto &s : domainSplit) {
        ptr->push_back(static_cast<std::uint8_t>(s.size()));
        for (auto &c : s) {
            ptr->push_back(static_cast<std::uint8_t>(c));
        }
    }
    ptr->push_back(0);
    std::cout << "dns request query name length is " << ptr->size() << " bytes"
              << std::endl;
    return ptr;
}
} // namespace net