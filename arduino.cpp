#include "arduino.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QDateTime>
#include <QThread>

Arduino::Arduino(QObject *parent) : QObject(parent) {
    serial = new QSerialPort(this);
    connect(serial, &QSerialPort::readyRead, this, &Arduino::readData);
}

void Arduino::connectToArduino() {
    serial->setPortName("COM3");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    // Try 3 times with delays
    for (int attempt = 1; attempt <= 3; attempt++) {
        qDebug() << "Connection attempt" << attempt << "to COM3...";

        if (serial->open(QIODevice::ReadWrite)) {
            qDebug() << "Connected to COM3 successfully!";
            QThread::msleep(100); // Wait for port stabilization
            return;
        }

        qDebug() << "Failed attempt" << attempt << ":" << serial->errorString();
        QThread::msleep(1000); // Wait 1 second before retrying
    }

    qDebug() << "Critical error: Could not connect to COM3 after 3 attempts!";
    qDebug() << "Last error:" << serial->errorString();
}

void Arduino::readData() {
    // read everything, but only line-by-line
    while (serial->canReadLine()) {
        QByteArray raw = serial->readLine();
        QString line = QString::fromUtf8(raw).trimmed();
        qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
                 << "<< From Arduino:" << line;

        if (line.contains("HELLO")) {
            qDebug() << "   — Arduino boot confirmed";
        }
        else if (line.contains("READY")) {
            qDebug() << "   — Handshake READY seen";
            emit arduinoReady();
        }
        else if (line.startsWith("GOT:")) {
            qDebug() << "   — Arduino ACK:" << line;
        }
        else if (line == "DECREMENT") {
            qDebug() << "   — Removal event!";
            emit decrementRequested();
        }
    }
}

void Arduino::sendData(const QString &resourceName, int quantity) {
    if (!serial->isOpen()) return;
    QString cmd = QString("SET:%1:%2\n").arg(resourceName).arg(quantity);
    qDebug() << "→ Sending to Arduino:" << cmd.trimmed();
    serial->write(cmd.toUtf8());
}
