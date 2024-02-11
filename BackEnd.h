#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <qqml.h>
#include "ConfigLoader.h"

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double aoaValue READ aoaValue WRITE setAOAValue NOTIFY aoaValueChanged)
    Q_PROPERTY(double aosValue READ aosValue WRITE setAOSValue NOTIFY aosValueChanged)
    Q_PROPERTY(QString bColor READ bColor WRITE setbColor NOTIFY bColorValueChanged)
    Q_PROPERTY(Gauge aosGauge READ aosGauge WRITE setAoSGauge NOTIFY aosGaugeChanged)
    Q_PROPERTY(Gauge aoaGauge READ aoaGauge WRITE setAoAGauge NOTIFY aoaGaugeChanged)
    Q_PROPERTY(QString aoaStr READ aoaStr WRITE setAoAStr NOTIFY aoaStrChanged)
    Q_PROPERTY(QString aosStr READ aosStr WRITE setAoSStr NOTIFY aosStrChanged)

public:
    explicit BackEnd(QObject *parent = nullptr);
    double aoaValue();
    double aosValue();
    QString bColor();
    Gauge aosGauge();
    Gauge aoaGauge();
    QString aoaStr();
    QString aosStr();

    void setAOAValue(const double& val);
    void setAOSValue(const double& val);
    void setbColor(const QString& color);
    void setAoSGauge(const Gauge& g);
    void setAoAGauge(const Gauge& g);
    void setAoAStr(const QString& val);
    void setAoSStr(const QString& val);


signals:
    void aoaValueChanged();
    void aosValueChanged();
    void bColorValueChanged();
    void aosGaugeChanged();
    void aoaGaugeChanged();
    void aoaStrChanged();
    void aosStrChanged();

public slots:
    void updateFromWorker(double val);

private:
    double m_aoaValue;
    double m_aosValue;
    QString m_aoaStr;
    QString m_aosStr;

    ConfigLoader config;

    void dataFromFile();
    void dataFromPort();
};

#endif // BACKEND_H
