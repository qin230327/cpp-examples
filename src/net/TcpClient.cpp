//
// Created by qin on 2023/4/7.
//

#include "TcpClient.h"
#include <boost/asio.hpp>
#include <iostream>

namespace net {
std::shared_ptr<std::vector<unsigned char>>
TcpClient::sendAndReceive(const std::string &ip, const unsigned short &port,
                          const std::vector<unsigned char> &bytes) {
    auto ptr = std::make_shared<std::vector<unsigned char>>();

    /*
     * create a socket obj
     */
    boost::asio::io_service ioService;
    boost::asio::ip::tcp::socket socket(ioService);
    boost::system::error_code errorCode;

    try {
        socket.connect(boost::asio::ip::tcp::endpoint(
            boost::asio::ip::address::from_string(ip), port));
        auto len1 = socket.write_some(boost::asio::buffer(bytes), errorCode);
        std::cout << "write " << len1 << " bytes." << std::endl;

        unsigned char twoKB[2048];
        auto len2 = socket.read_some(boost::asio::buffer(twoKB), errorCode);
        for (auto i = 0; i < len2; i++) {
            ptr->push_back(twoKB[i]);
        }
    } catch (std::exception &e) {
        std::cerr << "write message to socket error or read message from "
                     "socket error, exception message: "
                  << e.what() << std::endl;
        std::cerr << boost::system::system_error(errorCode).what() << std::endl;
    }

    return ptr;
}
} // namespace net
