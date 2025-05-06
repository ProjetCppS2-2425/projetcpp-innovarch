#include "arduinoManager.h"
#include <QDebug>
#include <QThread>

ArduinoManager::ArduinoManager(QObject *parent)
    : QObject(parent), serial(new QSerialPort(this))
{
    connect(serial, &QSerialPort::readyRead, this, &ArduinoManager::readSerialData);
}

bool ArduinoManager::connectToArduino() {
    QSerialPort *serial = new QSerialPort(this);
    serial->setPortName("COM3");  // Update with the actual port name where Arduino is connected
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Serial Port Opened!";
    } else {
        qDebug() << "Failed to open serial port!";
    }

}

void ArduinoManager::readSerialData()
{
    QByteArray data = serial->readAll();
    qDebug() << "?? Data received from Arduino:" << data;

    // Check if the data contains "Product removed!" indicating a product was removed
    if (data.contains("REMOVED")) {
        emit productRemoved();  // Emit the signal when the product is removed
    }
}
bool ArduinoManager::isSerialOpen() const {
    return serial->isOpen();
}

void ArduinoManager::sendDataToArduino(const QString &data) {
    if (serial->isOpen()) {
        serial->write(data.toUtf8());  // Send data as QByteArray
    } else {
        qDebug() << "❌ Serial port is not open!";
    }



ArduinoManager::~ArduinoManager() {
    if (serial->isOpen()) {
        serial->close();
    }
}
