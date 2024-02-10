#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <qqml.h>
#include "ConfigLoader.h"

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double aoaValue READ aoaValue WRITE setAOAValue NOTIFY aoaValueChanged)
    Q_PROPERTY(QString bColor READ bColor WRITE setbColor NOTIFY bColorValueChanged)
    Q_PROPERTY(Gauge aosGauge READ aosGauge WRITE setAoSGauge NOTIFY aosGaugeChanged)

public:
    explicit BackEnd(QObject *parent = nullptr);
    double aoaValue();
    QString bColor();
    Gauge aosGauge();

    void setAOAValue(const double& val);
    void setbColor(const QString& color);
    void setAoSGauge(const Gauge& g);

signals:
    void aoaValueChanged();
    void bColorValueChanged();
    void aosGaugeChanged();

public slots:
    void updateFromWorker(double val);

private:
    double m_aoaValue;
    ConfigLoader config;

    void dataFromFile();
    void dataFromPort();
};

#endif // BACKEND_H
