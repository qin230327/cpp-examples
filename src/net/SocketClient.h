//
// Created by qin on 2023/4/7.
//

#ifndef CPP_EXAMPLES_SOCKETCLIENT_H
#define CPP_EXAMPLES_SOCKETCLIENT_H

#include <memory>
#include <string>
#include <vector>

namespace net {
    class SocketClient {
    public:
        static std::shared_ptr<std::vector<unsigned char>>
        sendAndReceive(const std::string &ip, const unsigned short &port, const std::vector<unsigned char> &bytes);
    };
}// namespace net


#endif//CPP_EXAMPLES_SOCKETCLIENT_H
