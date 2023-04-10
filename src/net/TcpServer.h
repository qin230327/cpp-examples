

#ifndef CPP_EXAMPLES_TCPSERVER_H
#define CPP_EXAMPLES_TCPSERVER_H

#include <memory>
#include <string>

namespace net {
    class TcpServer {
    public:
        static std::shared_ptr<std::string> start(const unsigned short port, const std::string &rspToCli);
    };


}// namespace net

#endif//CPP_EXAMPLES_TCPSERVER_H