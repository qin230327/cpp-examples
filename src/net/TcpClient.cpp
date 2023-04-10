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
        auto flag = false;

        /*
         * create a socket obj
         */
        boost::asio::io_service ioService;
        boost::asio::ip::tcp::socket socket(ioService);
        boost::system::error_code errorCode;

        for (auto i = 0; i < 1; i++) {
            /*
             * connect to a remote tcp endpoint
             */
            try {
                auto ipAddress = boost::asio::ip::address::from_string(ip);
                boost::asio::ip::tcp::endpoint endpoint(ipAddress, port);
                socket.connect(endpoint);
            } catch (std::exception &e) {
                std::cerr << "connect to " << ip << ":" << port << " error, exception message: " << e.what() << std::endl;
                break;
            }

            /*
             * send
             */
            auto bytesBuf = boost::asio::buffer(bytes);
            try {
                auto len = socket.write_some(bytesBuf, errorCode);
                std::cout << "write " << len << " bytes." << std::endl;
            } catch (std::exception &e) {
                std::cerr << "write message to socket error, exception message: " << e.what() << std::endl;
                std::cerr << boost::system::system_error(errorCode).what() << std::endl;
                break;
            }

            /*
             * block and receive
             */
            try {
                unsigned char oneKB[1024];
                while (true) {
                    auto len = socket.read_some(boost::asio::buffer(oneKB), errorCode);
                    if (len > 0) {
                        for (auto i = 0; i < len; i++) {
                            ptr->push_back(oneKB[i]);
                        }
                    } else {
                        break;
                    }
                }
            } catch (std::exception &e) {
                std::cerr << "read message from socket error, exception message: " << e.what() << std::endl;
                std::cerr << boost::system::system_error(errorCode).what() << std::endl;
                break;
            }

            /*
             * close socket
             */
            try {
                socket.close();
            } catch (std::exception &e) {
                std::cerr << "close socket error, exception message: " << e.what() << std::endl;
                std::cerr << boost::system::system_error(errorCode).what() << std::endl;
                break;
            }

            flag = true;
        }

        return flag ? ptr : nullptr;
    }
}// namespace net
