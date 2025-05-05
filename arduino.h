#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QSerialPortInfo>

class Arduino {
public:
    Arduino();
    int connect_arduino();
    int close_arduino();
    QByteArray read_from_arduino();
    void write_to_arduino(QByteArray d);
    QSerialPort* getserial();
    QString getarduino_port_name();

private:
    QSerialPort* serial;
    QString arduino_port_name;
    QByteArray data;
    bool arduino_is_available;
};

#endif // ARDUINO_H
