#ifndef SERIALREADER_H
#define SERIALREADER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QMutex>
#include <QtSerialPort>

class SerialReader : public QObject
{
    Q_OBJECT
public:
    explicit SerialReader(QObject *parent = nullptr);

    void setPort(const QString& port) {this->comPortName = port;}
    void setHz(const unsigned int& hz) {
        if (hz < 5) {
            this->sampleRate = 5;
        }else if (hz > 10) {
            this->sampleRate = 10;
        } else {
            this->sampleRate = hz;
        }
    }
    //read data from that port
    void startReceiver();

    //store that data

    //parse into the correct format

    //Thread API as well
    void process();

signals:
    void timeout(const QString& s);
    void finished();
    void error();
    void updateAoS(double val);
    void updateAoA(double val);
    void updateAoS_AoA(double aos, double aoa);

public slots:
    void createSerialPort();

private:
    QString comPortName;
    QString response;
    int waitTimeout = 0;
    double sampleRate;
    QSerialPort* serial = nullptr;
};

#endif // SERIALREADER_H
