#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QObject>

class Arduino : public QObject
{
    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr); // Fix constructor declaration
    int connect_arduino();
    int close_arduino();
    void write_to_arduino(const QByteArray &data); // Fix parameter type
    QByteArray read_from_arduino();
    QSerialPort* get_serial(); // Rename to match definition
    QString get_arduino_port_name(); // Rename to match definition

signals:
    void cardScanned();

private:
    QSerialPort *serial;
    QString arduino_port_name;
    QByteArray data;
};

#endif // ARDUINO_H
