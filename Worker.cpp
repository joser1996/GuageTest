#include "Worker.h"
#include <QThread>
#include <QDebug>

Worker::Worker()
{
    data = 0;
    myFile.open("test.txt", std::ifstream::in);
}

Worker::~Worker() {

}

void Worker::process() {
    qDebug("Starting process");

    while (true) {
        if (myFile.is_open()) {
            while (myFile) {
                std::string line;
                std::getline(myFile, line);
                if (line == "")
                    continue;
                double tmp = std::stod(line);
                emit updateValue(tmp);
                QThread::msleep(60);
            }
        } else {
            qDebug() << "Couldn't open file";
        }

        myFile.clear();
        myFile.seekg(0);
    }

    emit finished();
}
