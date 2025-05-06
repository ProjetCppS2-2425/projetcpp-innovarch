#include "arduinocontracteur.h"

ArduinoCont::ArduinoCont(QObject *parent) : QObject(parent) // Fix constructor
{
    data = "";
    arduino_port_name = "COM15";
    serial = new QSerialPort;
}

QString ArduinoCont::get_arduino_port_name() // Fix method name
{
    return arduino_port_name;
}

QSerialPort* ArduinoCont::get_serial() // Fix method name
{
    return serial;
}

int ArduinoCont::connect_arduino()
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

int ArduinoCont::close_arduino()
{
    if (serial->isOpen()) {
        serial->close();
        return 0;
    }
    return 1;
}

QByteArray ArduinoCont::read_from_arduino()
{
    if (serial->isReadable()) {
        data = serial->readAll();
        if (!data.isEmpty()) {
            emit cardScanned();
        }
        return data;
    }
    return "";
}

void ArduinoCont::write_to_arduino(const QByteArray &d) // Fix parameter type
{
    if (serial->isWritable()) {
        serial->write(d);
    } else {
        qDebug() << "❌ Impossible d'écrire sur le port série!";
    }
}
