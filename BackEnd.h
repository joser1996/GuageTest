#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <qqml.h>


class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double aoaValue READ aoaValue WRITE setAOAValue NOTIFY aoaValueChanged)

public:
    explicit BackEnd(QObject *parent = nullptr);
    double aoaValue();
    void setAOAValue(const double& val);

signals:
    void aoaValueChanged();

public slots:
    void updateFromWorker(double val);

private:
    double m_aoaValue;
};

#endif // BACKEND_H
