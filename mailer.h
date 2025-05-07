#ifndef MAILER_H
#define MAILER_H

#include <QString>

class mailer {
public:
    mailer();
    int sendEmail(const QString& recipientEmail, const QString& subject, const QString& body);
};

#endif // MAILER_H
