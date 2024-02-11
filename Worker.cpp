#include "Worker.h"
#include <QThread>
#include <QDebug>

Worker::Worker()
{
    data = 0;
    myFile.open("test.txt", std::ifstream::in);
    sampleRate = 5; //20 ms Animation should be faster than this
}

Worker::Worker(unsigned int hz)
{
    data = 0;
    myFile.open("test.txt", std::ifstream::in);
    if (hz < 5) {
        hz = 5;
    }

    if (hz > 10) {
        hz = 10;
    }
    sampleRate = hz; //20 ms Animation should be faster than this
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
                QThread::msleep((1/sampleRate) * 1000);
            }
        } else {
            qDebug() << "Couldn't open file";
        }

        myFile.clear();
        myFile.seekg(0);
    }

    emit finished();
}
