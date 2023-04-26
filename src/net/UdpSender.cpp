#include "UdpSender.h"
#include <boost/asio.hpp>
#include <cstring>
#include <iostream>

namespace net {
std::shared_ptr<std::vector<std::uint8_t>>
UdpSender::send(const std::string &msg, const std::uint16_t localPort,
                const std::string &remoteAddr, const std::uint16_t remotePort) {
    std::vector<std::uint8_t> bytes(msg.size());
    std::memcpy(bytes.data(), msg.data(), msg.size());
    return send(bytes, localPort, remoteAddr, remotePort);
}

std::shared_ptr<std::vector<std::uint8_t>>
UdpSender::send(const std::vector<std::uint8_t> &bytes,
                const std::uint16_t localPort, const std::string &remoteAddr,
                const std::uint16_t remotePort) {
    auto res = std::make_shared<std::vector<std::uint8_t>>();
    boost::asio::io_service ioService;
    boost::system::error_code errorCode;
    try {
        boost::asio::ip::udp::endpoint localEndpoint(boost::asio::ip::udp::v4(),
                                                     localPort);
        boost::asio::ip::udp::endpoint remoteEndpoint(
            boost::asio::ip::address::from_string(remoteAddr, errorCode),
            remotePort);
        boost::asio::ip::udp::socket socket(ioService, localEndpoint);
        auto len = socket.send_to(
            boost::asio::buffer(bytes.data(), bytes.size()), remoteEndpoint);
        std::cout << "send " << len << " bytes successfully" << std::endl;

        std::uint8_t twoKB[2048] = {'\0'};
        auto len2 =
            socket.receive_from(boost::asio::buffer(twoKB), remoteEndpoint);
        for (auto i = 0; i < len2; ++i) {
            res->push_back(twoKB[i]);
        }

    } catch (std::exception &e) {
        std::cerr << "send message to socket error, exception message: "
                  << e.what() << std::endl;
        std::cerr << boost::system::system_error(errorCode).what() << std::endl;
    }
    return res;
}
} // namespace net