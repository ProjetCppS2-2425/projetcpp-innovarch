#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QObject>

class Arduino : public QObject
{
    Q_OBJECT // Add this macro to enable signals and slots

public:
    Arduino();
    int connect_arduino(); // Connexion Arduino
    int close_arduino();   // Déconnexion Arduino
    void write_to_arduino(QByteArray data); // Envoyer des données
    QByteArray read_from_arduino();         // Lire des données
    QSerialPort* getserial();               // Accès au port série
    QString getarduino_port_name();         // Nom du port

signals:
    void cardScanned(); // Signal emitted when a card is scanned

private:
    QSerialPort *serial;
    QString arduino_port_name;
    QByteArray data;
};

#endif // ARDUINO_H
