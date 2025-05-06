#ifndef ARDUINOMANAGER_H
#define ARDUINOMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class ArduinoManager : public QObject {
    Q_OBJECT

public:
    explicit ArduinoManager(QObject *parent = nullptr);
    ~ArduinoManager();
    bool connectToArduino();
    bool isSerialOpen() const;  // Check if serial port is open
    void sendDataToArduino(const QString &data);

signals:
    void productRemoved();  // Signal to notify Qt about product removal

private slots:
    void readSerialData();

private:
    QSerialPort *serial;
};


#endif // ARDUINOMANAGER_H
