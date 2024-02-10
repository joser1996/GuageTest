#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H
#include <QString>
#include <QDebug>
#include <iostream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <QFile>
#include <tuple>

struct Gauge
{
    QString name;
    int minAngle;
    int maxAngle;
    int minValue;
    int maxValue;
    int redZone;
};

struct Config
{
    unsigned int comPort;
    bool usingCOMPort;
    QString fileDataSource;
    unsigned int sampleRateHz;
    QString backgroundColor;
    QVector<Gauge> gauges;
};

class ConfigLoader
{
public:
    ConfigLoader();
    Config configObj;

private:
    static const QString configName;
    bool loadConfigFile();
    bool createDefaultFile();
};

#endif // CONFIGLOADER_H



