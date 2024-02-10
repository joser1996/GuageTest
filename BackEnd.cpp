#include "BackEnd.h"
#include "Worker.h"
#include <QThread>

//TODO: Add config file for
//        * COM PORT
//        * Min/Max for gauges
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

double BackEnd::aoaValue() {
    return m_aoaValue;
}

void BackEnd::setAOAValue(const double& val) {
    m_aoaValue = val;
    qDebug("SLot called");
    emit aoaValueChanged();
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
