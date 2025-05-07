#include "arduinocontrat.h"
#include <QDebug>

Arduinocontrat::Arduinocontrat() {
    serial = new QSerialPort;
    data = "";
}

QString Arduinocontrat::getarduino_port_name() {
    return arduino_port_name;
}

QSerialPort* Arduinocontrat::getserial() {
    return serial;
}

int Arduinocontrat::connect_arduino() {
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.vendorIdentifier()) {
            arduino_port_name = info.portName();
            arduino_is_available = true;
        }
    }

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);
        if (serial->open(QIODevice::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;
        }
    }
    return 1;
}

int Arduinocontrat::close_arduino() {
    if (serial->isOpen()) {
        serial->close();
        return 0;
    }
    return 1;
}

QByteArray Arduinocontrat::read_from_arduino() {
    if (serial->isReadable()) {
        data = serial->readLine();
        return data;
    }
    return "";
}

void Arduinocontrat::write_to_arduino(QByteArray d) {
    if (serial->isWritable()) {
        serial->write(d);
    }
}
