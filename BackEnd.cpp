#include "BackEnd.h"
#include "Worker.h"
#include <QThread>

//TODO: Connect back end to QML front end
/*
 * Differentiate b/w both gauges
 * assuming always two and names in config are only for knowing
 * which gauge you're changing. Not addin/removing number
 *
 * Pass two structures gauge1 and gauge 2 and use those to config values
 */
//TODO: Set up class for parsing bytes of data


BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
    config = ConfigLoader();
    m_aoaValue = 0;
    if (config.configObj.usingCOMPort) {
        dataFromPort();
    } else {
        dataFromFile();
    }
}
// AoA Value
double BackEnd::aoaValue() {
    return m_aoaValue;
}

void BackEnd::setAOAValue(const double& val) {
    m_aoaValue = val;
    emit aoaValueChanged();
}

//AoS Value
double BackEnd::aosValue() {
    return m_aosValue;
}

void BackEnd::setAOSValue(const double &val) {
    m_aosValue = val;
    emit aosValueChanged();
}

//Background Color
QString BackEnd::bColor() {
    return this->config.configObj.backgroundColor;
}

void BackEnd::setbColor(const QString &color) {
    config.configObj.backgroundColor = color;
    emit bColorValueChanged();
}

//AoS Gauge Config
Gauge BackEnd::aosGauge() {
    Gauge g = this->config.configObj.gauges[1];
    return g;
}

void BackEnd::setAoSGauge(const Gauge &g) {
    config.configObj.gauges[1] = g;
    emit aosGaugeChanged();
}

//AoA Gauge Config
Gauge BackEnd::aoaGauge() {
    return this->config.configObj.gauges[0];
}

void ::BackEnd::setAoAGauge(const Gauge& g) {
    config.configObj.gauges[0] = g;
    emit aoaGaugeChanged();
}

//AoA Str
QString BackEnd::aoaStr() {
    return m_aoaStr;
}

void BackEnd::setAoAStr(const QString &val) {
    m_aoaStr = val;
    emit aoaStrChanged();
}

//AoS Val
QString BackEnd::aosStr() {
    return m_aosStr;
}

void BackEnd::setAoSStr(const QString &val) {
    m_aosStr = val;
    emit aosStrChanged();
}

/*****************Thread Updates*******************/
void BackEnd::updateFromWorker(double val) { //FOR AOA Value
    this->setAOAValue(val);

    QString valStr = QString::number(val) + " units/sec";

    this->setAoAStr(valStr);
    this->setAoSStr(valStr);
}

void
BackEnd::dataFromFile() {
    QThread* thread = new QThread;
    Worker* worker = new Worker(this->config.configObj.sampleRateHz);

    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(updateValue(double)), this, SLOT(updateFromWorker(double)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(worker, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

    qDebug("Thread started");
}

void BackEnd::dataFromPort() {
    QThread* thread = new QThread;
    SerialReader* reader = new SerialReader;
    reader->setPort(this->config.configObj.comPort);

    reader->moveToThread(thread);

    connect(thread, &QThread::started, reader, &SerialReader::process);
    connect(reader, &SerialReader::updateAoA, this, &BackEnd::updateAoASerial);
    connect(reader, &SerialReader::updateAoS, this, &BackEnd::updateAoSSerial);
    connect(reader, &SerialReader::updateAoS_AoA, this, &BackEnd::updateAoS_AoASeraial);
    connect(reader, &SerialReader::finished, reader, &SerialReader::deleteLater);
    connect(reader, &SerialReader::finished, thread, &QThread::deleteLater);
    connect(this, &BackEnd::createSerialReader, reader, &SerialReader::createSerialPort);

    thread->start();
    qDebug() << "Serail Thread started";

}

void BackEnd::updateAoASerial(double val) {
    this->setAOAValue(val);
    QString valStr = QString::number(val) + " units/sec";
    this->setAoAStr(valStr);
}

void BackEnd::updateAoSSerial(double val) {
    this->setAOSValue(val);
    QString valStr = QString::number(val) + " units/sec";
    this->setAoSStr(valStr);
}

void BackEnd::updateAoS_AoASeraial(double aos, double aoa) {
    this->setAOAValue(aoa);
    this->setAOSValue(aos);
    QString aosStr = QString::number(aos) + " units/sec";
    QString aoaStr = QString::number(aoa) + " units/sec";

    this->setAoAStr(aosStr);
    this->setAoSStr(aoaStr);
}
