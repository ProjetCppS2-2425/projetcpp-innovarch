#include "arduinocl.h"

ArduinoCL::ArduinoCL()
{
    data = "";
    arduino_port_name = "COM4";
    serial = new QSerialPort;
}

QString ArduinoCL::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort* ArduinoCL::getserial()
{
    return serial;
}

int ArduinoCL::connect_arduino()
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

int ArduinoCL::close_arduino()
{
    if (serial->isOpen()) {
        serial->close();
        return 0;
    }
    return 1;
}

QByteArray ArduinoCL::read_from_arduino()
{
    if (serial->isReadable()) {
        data = serial->readAll();
        return data;
    }
    return "";
}

void ArduinoCL::write_to_arduino(QByteArray d)
{
    if (serial->isWritable()) {
        serial->write(d);
    } else {
        qDebug() << "❌ Impossible d'écrire sur le port série!";
    }
}
