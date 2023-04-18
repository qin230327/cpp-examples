#include "UdpReceiver.h"
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <exception>
#include <iostream>
#include <memory>
namespace net {
std::shared_ptr<std::string> UdpReceiver::receive(const std::uint16_t port) {
    auto res = std::make_shared<std::string>();
    boost::asio::io_service ioService;
    try {
        boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::udp::v4(),
                                                port);
        boost::asio::ip::udp::socket socket(ioService, endpoint);
        char oneKB[1024] = {'\0'};
        auto len = socket.receive_from(boost::asio::buffer(oneKB), endpoint);
        for (auto i = 0; i < len; ++i) {
            res->push_back(oneKB[i]);
        }
    } catch (std::exception &e) {
        std::cerr << "receive message to socket error, exception message: "
                  << e.what() << std::endl;
    }
    return res;
}
} // namespace net