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
    Q_PROPERTY(double sampleRate READ sampleRate WRITE setSampleRate NOTIFY sampleRateChanged)

public:
    explicit BackEnd(QObject *parent = nullptr);
    double aoaValue();
    double aosValue();
    QString bColor();
    Gauge aosGauge();
    Gauge aoaGauge();
    double sampleRate();

    void setAOAValue(const double& val);
    void setAOSValue(const double& val);
    void setbColor(const QString& color);
    void setAoSGauge(const Gauge& g);
    void setAoAGauge(const Gauge& g);
    void setSampleRate(const double& val);

signals:
    void aoaValueChanged();
    void aosValueChanged();
    void bColorValueChanged();
    void aosGaugeChanged();
    void aoaGaugeChanged();
    void sampleRateChanged();

public slots:
    void updateFromWorker(double val);

private:
    double m_aoaValue;
    double m_aosValue;

    ConfigLoader config;

    void dataFromFile();
    void dataFromPort();
};

#endif // BACKEND_H
