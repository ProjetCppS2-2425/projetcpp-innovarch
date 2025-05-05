#include "mailer.h"
#include <QSslSocket>
#include <QDebug>

mailer::mailer() {}

int mailer::sendEmail(const QString& recipientEmail, const QString& subject, const QString& body) {
    QString smtpServer = "smtp.gmail.com";
    int smtpPort = 465;
    QString username = "youssef.bensaid@esprit.tn"; // ← ton adresse Gmail
    QString password = "yeiy hmpk aoil glox";          // ← mot de passe d'application Gmail
    QString from = "youssef.bensaid@esprit.tn";     // ← identique à username

    QSslSocket socket;
    socket.connectToHostEncrypted(smtpServer, smtpPort);

    if (!socket.waitForConnected()) {
        qDebug() << "Connexion échouée:" << socket.errorString();
        return -1;
    }

    if (!socket.waitForReadyRead()) return -1;
    socket.readAll();

    socket.write("HELO localhost\r\n");
    if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) return -1;
    socket.readAll();

    socket.write("AUTH LOGIN\r\n");
    if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) return -1;
    socket.readAll();

    socket.write(QByteArray().append(username.toUtf8()).toBase64() + "\r\n");
    if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) return -1;
    socket.readAll();

    socket.write(QByteArray().append(password.toUtf8()).toBase64() + "\r\n");
    if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) return -1;
    socket.readAll();

    socket.write("MAIL FROM:<" + from.toUtf8() + ">\r\n");
    if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) return -1;
    socket.readAll();

    socket.write("RCPT TO:<" + recipientEmail.toUtf8() + ">\r\n");
    if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) return -1;
    socket.readAll();

    socket.write("DATA\r\n");
    if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) return -1;
    socket.readAll();

    socket.write("From: \"Innovarch\" <" + from.toUtf8() + ">\r\n");
    socket.write("To: <" + recipientEmail.toUtf8() + ">\r\n");
    socket.write("Subject: " + subject.toUtf8() + "\r\n");
    socket.write("MIME-Version: 1.0\r\n");
    socket.write("Content-Type: text/plain; charset=\"UTF-8\"\r\n");
    socket.write("\r\n");

    socket.write(body.toUtf8() + "\r\n.\r\n");
    if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) return -1;
    socket.readAll();

    socket.write("QUIT\r\n");
    socket.waitForBytesWritten();
    socket.close();

    return 0;
}
