#ifndef __SMTPSENDER_H__
#define __SMTPSENDER_H__

#include <memory>
#include <string>
#include <vector>

using std::shared_ptr;
using std::string;
using std::vector;

namespace net {
class SmtpSender {
  public:
    class Email;

    static shared_ptr<string> sendToSmtpSrv(const string &smtpHost,
                                            const unsigned short smtpPort,
                                            const string &smtpUser,
                                            const string &smtpPasswd,
                                            const Email &);

    class Email {
      public:
        Email(const string &from, const vector<string> &to, const string &subj,
              const string &body);

        shared_ptr<string> getFrom() const;
        shared_ptr<vector<string>> getTo() const;
        shared_ptr<string> getSubj() const;
        shared_ptr<string> getBody() const;

      private:
        string _from;
        vector<string> _to;
        string _subj;
        string _body;
    };

  private:
    static shared_ptr<string> wrapAngleBrackets(const string &);
};
} // namespace net

#endif // __SMTPSENDER_H__