#ifndef ARDUINOCL_H
#define ARDUINOCL_H

#include <QtSerialPort/QSerialPort>
#include <QDebug>

class ArduinoCL
{
public:
    ArduinoCL();
    int connect_arduino();
    int close_arduino();
    void write_to_arduino(QByteArray data);
    QByteArray read_from_arduino();
    QSerialPort* getserial();
    QString getarduino_port_name();

private:
    QSerialPort *serial;
    QString arduino_port_name;
    QByteArray data;
};

#endif // ARDUINOCL_H
