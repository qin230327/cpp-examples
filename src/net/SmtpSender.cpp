#include "SmtpSender.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <memory>
#include <string>

namespace net {
shared_ptr<string> SmtpSender::wrapAngleBrackets(const string &str) {
    auto res = std::make_shared<string>();
    res->append("<");
    res->append(str);
    res->append(">");
    return res;
}

shared_ptr<string> SmtpSender::sendToSmtpSrv(const string &smtpHost,
                                             const unsigned short smtpPort,
                                             const string &smtpUser,
                                             const string &smtpPasswd,
                                             const Email &email) {
    auto curl = curl_easy_init();
    auto res = CURLE_OK;
    if (!curl) {
        return nullptr;
    }
    curl_slist *headers;

    /*
     * smtp config
     */
    const string url = smtpHost + ":" + std::to_string(smtpPort);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERNAME, smtpUser.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, smtpPasswd.c_str());

    /*
     * sender config
     */
    auto from = wrapAngleBrackets(*(email.getFrom()));
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from->c_str());

    /*
     * recipients config
     */
    curl_slist *recipients = nullptr;
    auto to = email.getTo();
    for (auto &rcptStr : *to) {
        auto rcpt = wrapAngleBrackets(rcptStr);
        recipients = curl_slist_append(recipients, rcpt->c_str());
    }
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    /*
     * header config
     */
    auto header = email.getSubj();
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header->c_str());

    /*
     * body config
     */
    curl_mime *mime = curl_mime_init(curl);
    curl_mime *alt = curl_mime_init(curl);
    curl_mimepart *part = curl_mime_addpart(alt);
    curl_mime_data(part, email.getBody()->c_str(), CURL_ZERO_TERMINATED);
    curl_mime_type(part, "text/plain");
    part = curl_mime_addpart(mime);
    curl_mime_subparts(part, alt);
    curl_mime_type(part, "multipart/alternative");
    curl_slist *slist = curl_slist_append(NULL, "Content-Disposition: inline");
    curl_mime_headers(part, slist, 1);

    /*
     * send
     */

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    auto code = curl_easy_perform(curl);
    if (code != CURLE_OK) {
        std::cerr << "failed to send email" << std::endl;
        std::cerr << curl_easy_strerror(code) << std::endl;
    }

    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
    curl_mime_free(mime);

    return nullptr;
}

SmtpSender::Email::Email(const string &from, const vector<string> &to,
                         const string &subj, const string &body) {
    this->_from = from;
    this->_to = to;
    this->_subj = subj;
    this->_body = body;
}

shared_ptr<string> SmtpSender::Email::getFrom() const {
    return std::make_shared<string>(this->_from);
}

shared_ptr<vector<string>> SmtpSender::Email::getTo() const {
    return std::make_shared<vector<string>>(this->_to);
}

shared_ptr<string> SmtpSender::Email::getSubj() const {
    return std::make_shared<string>(this->_subj);
}

shared_ptr<string> SmtpSender::Email::getBody() const {
    return std::make_shared<string>(this->_body);
}

} // namespace net