#ifndef __DNSSENDER_H__
#define __DNSSENDER_H__

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

using std::string;
using std::uint16_t;
using std::vector;

namespace net {
class DnsSender {
  public:
    static std::shared_ptr<std::vector<std::uint8_t>>
    send(string domain, uint16_t localPort, string dnsIp, uint16_t dnsPort = 53,
         bool queryRecur = false);

  private:
    static std::uint16_t genTranId();
    static std::shared_ptr<std::vector<std::uint8_t>>
    genQryName(std::string domain);
};
} // namespace net
#endif // __DNSSENDER_H__