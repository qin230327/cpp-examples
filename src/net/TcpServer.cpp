#include "TcpServer.h"
#include <boost/asio.hpp>
#include <iostream>

namespace net {
std::shared_ptr<std::string> TcpServer::start(const unsigned short port,
                                              const std::string &rspToCli) {
    auto res = std::make_shared<std::string>();

    /*
     * create a socket obj
     */
    boost::asio::io_service ioService;
    boost::asio::ip::tcp::socket socket(ioService);
    boost::system::error_code errorCode;

    /*
     * bind to a port, listen on it, and start to accept connections
     */
    try {
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(),
                                                port);
        boost::asio::ip::tcp::acceptor acceptor(ioService, endpoint);
        acceptor.accept(socket, errorCode);
    } catch (std::exception &e) {
        std::cerr << "accept error, exception message: " << e.what()
                  << std::endl;
        std::cerr << boost::system::system_error(errorCode).what() << std::endl;
    }

    /*
     * read
     */
    try {
        boost::asio::streambuf streamBuf;
        boost::asio::read_until(socket, streamBuf, '\n', errorCode);
        res->append(boost::asio::buffer_cast<const char *>(streamBuf.data()));
    } catch (std::exception &e) {
        std::cerr << "read message from socket error, exception message: "
                  << e.what() << std::endl;
        std::cerr << boost::system::system_error(errorCode).what() << std::endl;
    }

    /*
     * write
     */
    try {
        boost::asio::write(socket, boost::asio::buffer(rspToCli), errorCode);
    } catch (std::exception &e) {
        std::cerr << "write message from socket error, exception message: "
                  << e.what() << std::endl;
        std::cerr << boost::system::system_error(errorCode).what() << std::endl;
    }

    return res;
}
} // namespace net