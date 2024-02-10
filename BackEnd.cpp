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
    qDebug("SLot called");
    emit aoaValueChanged();
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

void BackEnd::updateFromWorker(double val) {
    this->setAOAValue(val);
}

void BackEnd::dataFromFile() {
    QThread* thread = new QThread;
    Worker* worker = new Worker;

    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(updateValue(double)), this, SLOT(updateFromWorker(double)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(worker, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

    qDebug("Thread started");
}

void BackEnd::dataFromPort() {

}
