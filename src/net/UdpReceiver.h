#ifndef __UDPRECEIVER_H__
#define __UDPRECEIVER_H__

#include <memory>
#include <string>

namespace net {
class UdpReceiver {
  public:
    static std::shared_ptr<std::string> receive(const std::uint16_t);
};
} // namespace net
#endif // __UDPRECEIVER_H__