#include "arduino.h"

Arduino::Arduino()
{
    data = "";
    arduino_port_name = "COM15"; // ✅ Fixer ici le port (exemple : "COM4")
    serial = new QSerialPort;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort* Arduino::getserial()
{
    return serial;
}

int Arduino::connect_arduino()
{
    serial->setPortName(arduino_port_name);

    if (serial->open(QSerialPort::ReadWrite)) {
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        qDebug() << "✅ Arduino connecté sur " << arduino_port_name;
        return 0;
    } else {
        qDebug() << "❌ Impossible d'ouvrir le port " << arduino_port_name;
        return 1;
    }
}

int Arduino::close_arduino()
{
    if (serial->isOpen()) {
        serial->close();
        return 0;
    }
    return 1;
}

QByteArray Arduino::read_from_arduino()
{
    if (serial->isReadable()) {
        data = serial->readAll();
        if (!data.isEmpty()) {
            emit cardScanned(); // Emit signal when a card is scanned
        }
        return data;
    }
    return "";
}

void Arduino::write_to_arduino(QByteArray d)
{
    if (serial->isWritable()) {
        serial->write(d);
    } else {
        qDebug() << "❌ Impossible d'écrire sur le port série!";
    }
}
