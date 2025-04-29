#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>

class Arduino : public QObject {
    Q_OBJECT
public:
    explicit Arduino(QObject *parent = nullptr);
    void connectToArduino();
    void sendData(const QString &resourceName, int quantity);
    bool isConnected() const {
        return serial->isOpen() && serial->isWritable();
    }

signals:
    void decrementRequested();
    void arduinoReady();

private slots:
    void readData();

private:
    QSerialPort *serial;
};

#endif // ARDUINO_H
