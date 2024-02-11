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
    Q_GADGET

    Q_PROPERTY(QString name MEMBER m_name);
    Q_PROPERTY(int minAngle MEMBER m_minAngle);
    Q_PROPERTY(int maxAngle MEMBER m_maxAngle);
    Q_PROPERTY(int minValue MEMBER m_minValue);
    Q_PROPERTY(int maxValue MEMBER m_maxValue);
    Q_PROPERTY(int redZone MEMBER m_redZone);

public:
    QString m_name;
    int m_minAngle;
    int m_maxAngle;
    int m_minValue;
    int m_maxValue;
    int m_redZone;
};

struct Config
{
    QString comPort;
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



