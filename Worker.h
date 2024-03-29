#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <iostream>
#include <fstream>
#include <string>

class Worker: public QObject
{
    Q_OBJECT
public:
    Worker();
    Worker(unsigned int hz);
    ~Worker();

public slots:
    void process();

signals:
    void finished();
    void error();
    void updateValue(double val);
private:
    double data;
    std::ifstream myFile;
    double sampleRate;

};

#endif // WORKER_H
