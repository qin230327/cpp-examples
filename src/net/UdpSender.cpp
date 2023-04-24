#include "UdpSender.h"
#include <boost/asio.hpp>
#include <iostream>

namespace net {
bool UdpSender::send(const std::string &msg, const std::uint16_t localPort,
                     const std::string &remoteAddr,
                     const std::uint16_t remotePort) {
    boost::asio::io_service ioService;
    boost::system::error_code errorCode;
    try {
        boost::asio::ip::udp::endpoint localEndpoint(boost::asio::ip::udp::v4(),
                                                     localPort);
        boost::asio::ip::udp::endpoint remoteEndpoint(
            boost::asio::ip::address::from_string(msg, errorCode), remotePort);
        boost::asio::ip::udp::socket socket(ioService, localEndpoint);
        auto len = socket.send_to(boost::asio::buffer(msg), remoteEndpoint);
        std::cout << "send " << len << " bytes successfully" << std::endl;
    } catch (std::exception &e) {
        std::cerr << "send message to socket error, exception message: "
                  << e.what() << std::endl;
        std::cerr << boost::system::system_error(errorCode).what() << std::endl;
        return false;
    }
    return true;
}

bool UdpSender::send(const std::vector<std::uint8_t> &bytes,
                     const std::uint16_t localPort,
                     const std::string &remoteAddr,
                     const std::uint16_t remotePort) {
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
    } catch (std::exception &e) {
        std::cerr << "send message to socket error, exception message: "
                  << e.what() << std::endl;
        std::cerr << boost::system::system_error(errorCode).what() << std::endl;
        return false;
    }
    return true;
}
} // namespace net