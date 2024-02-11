#include "SerialReader.h"

SerialReader::SerialReader(QObject *parent)
    :QObject(parent), comPortName(""), sampleRate(5)
{}

void SerialReader::process() {
    qDebug() << "Starting serial process";
    if (comPortName ==  "") {
        qDebug() << "COM Port wasn't set";
        emit finished();
    }

    startReceiver();
}

void SerialReader::createSerialPort() {
    this->serial = new QSerialPort;
}

void SerialReader::startReceiver() {
    if (serial == nullptr) {
        serial = new QSerialPort;
    }

    serial->setPortName(this->comPortName);

    if (!serial->setBaudRate(QSerialPort::Baud115200)) {
        qDebug() << "BaudRate: " << serial->errorString();
    }
    if (!serial->setDataBits(QSerialPort::Data7)) {
        qDebug() << "DataBits: " << serial->errorString();
    }
    if (!serial->setParity(QSerialPort::NoParity)) {
        qDebug() << "Parity: " << serial->errorString();
    }
    if (!serial->setFlowControl(QSerialPort::HardwareControl)) {
        qDebug() << "FlowControl: " << serial->errorString();
    }
    if (!serial->setStopBits(QSerialPort::OneStop)) {
        qDebug() << "StopBits: " << serial->errorString();
    }
    if (!serial->open(QIODevice::ReadOnly)) {
        qDebug() <<"Opening Port: " + this->comPortName << serial->errorString();
    }
    qDebug() << "Bytes availalbe: " << serial->bytesAvailable();

    while (serial->isOpen()) {
        if (!serial->waitForReadyRead(-1)) {
            qDebug() << "Error Reading: " << serial->errorString();
        }
        else {
            qDebug() << "New Data: " << serial->bytesAvailable();
            QByteArray data = serial->readAll();
            qDebug() << data;
            //parse data and get aos and aoa
        }
    }
}
