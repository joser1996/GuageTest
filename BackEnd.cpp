#include "BackEnd.h"
#include "Worker.h"
#include <QThread>

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
    m_aoaValue = 0;
    QThread* thread = new QThread;
    Worker* worker = new Worker;

    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(updateValue(double)), this, SLOT(updateFromWorker(double)));
    thread->start();
    qDebug("Thread started");
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
