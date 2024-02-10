#include "ConfigLoader.h"

const QString ConfigLoader::configName = "Config.xml";

ConfigLoader::ConfigLoader()
{
    if (!loadConfigFile()) {
        qDebug() << "Failed to load config file";
        exit(-1);
    }
}

bool ConfigLoader::loadConfigFile() {

    QFile file(configName);
    if (!file.exists() && !createDefaultFile()) {
        qDebug() << "Failed to create a default file.";
        return false;
    }

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Failed to open file: " << configName;
        return false;
    }

    QXmlStreamReader xml(&file);
    if (xml.readNextStartElement()) {
        if (xml.name() == "Config") {
            while (xml.readNextStartElement()) {
                if (xml.name() == "COM") {
                    QStringRef strRef = xml.attributes().value("usingSource");
                    const QString f = "false";
                    if (strRef.toString() == f)
                        this->configObj.usingCOMPort = false;
                    else
                        this->configObj.usingCOMPort = true;
                    QString portStr = xml.readElementText();
                    this->configObj.comPort = portStr.toUInt();
                }else if (xml.name() == "fileName") {
                    this->configObj.fileDataSource = xml.readElementText();
                } else if (xml.name() == "sampleRateHz") {
                    QString hzStr = xml.readElementText();
                    this->configObj.sampleRateHz = hzStr.toUInt();
                } else if (xml.name() == "backGroundColor") {
                    this->configObj.backgroundColor = xml.readElementText();
                } else if (xml.name() == "gauge") {
                    QStringRef strRef = xml.attributes().value("name");
                    Gauge current;
                    current.m_name = strRef.toString();
                    while (xml.readNextStartElement()) {
                        int val = xml.readElementText().toInt();
                        if (xml.name() == "minAngle") {
                            current.m_minAngle = val;
                        } else if (xml.name() == "maxAngle") {
                            current.m_maxAngle = val;
                        } else if (xml.name() == "minValue") {
                            current.m_minValue = val;
                        } else if (xml.name() == "maxValue") {
                            current.m_maxValue = val;
                        } else if (xml.name() == "redZone") {
                            current.m_redZone = val;
                        }
                    }
                    this->configObj.gauges.append(current);
                }
            }
        }
    }

    return true;
}



bool ConfigLoader::createDefaultFile() {
    qDebug() << "Creating default config";
    QFile file(configName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Failed to open file for writing";
        return false;
    }

    QDomDocument xml("config");

    QDomElement root = xml.createElement("Config");
    xml.appendChild(root);

    // COM
    QDomElement tagCOM = xml.createElement("COM");
    root.appendChild(tagCOM);
    tagCOM.setAttribute("usingSource", "false");
    QDomText comText = xml.createTextNode("7");
    tagCOM.appendChild(comText);

    // fileName
    QDomElement fileName = xml.createElement("fileName");
    root.appendChild(fileName);
    QDomText fileNameText = xml.createTextNode("test.txt");
    fileName.appendChild(fileNameText);

    // sampleRateHz
    QDomElement sampleRateHz = xml.createElement("sampleRateHz");
    root.appendChild(sampleRateHz);
    QDomText sampleRateHzText = xml.createTextNode("5");
    sampleRateHz.appendChild(sampleRateHzText);

    // backGroundColor
    QDomElement backGroundColor = xml.createElement("backGroundColor");
    root.appendChild(backGroundColor);
    QDomText backGroundColorText = xml.createTextNode("#000000");
    backGroundColor.appendChild(backGroundColorText);

    // first gauge
    QDomElement gauge = xml.createElement("gauge");
    root.appendChild(gauge);
    gauge.setAttribute("name", "AoA");

    QDomElement minAngle = xml.createElement("minAngle");
    gauge.appendChild(minAngle);
    QDomText minAngleText = xml.createTextNode("-90");
    minAngle.appendChild(minAngleText);

    QDomElement maxAngle = xml.createElement("maxAngle");
    gauge.appendChild(maxAngle);
    QDomText maxAngleText = xml.createTextNode("90");
    maxAngle.appendChild(maxAngleText);

    QDomElement minValue = xml.createElement("minValue");
    gauge.appendChild(minValue);
    QDomText minValueText = xml.createTextNode("-90");
    minValue.appendChild(minValueText);

    QDomElement maxValue = xml.createElement("maxValue");
    gauge.appendChild(maxValue);
    QDomText maxValueText = xml.createTextNode("90");
    maxValue.appendChild(maxValueText);


    // second gauge
    gauge = xml.createElement("gauge");
    root.appendChild(gauge);
    gauge.setAttribute("name", "AoS");

    minAngle = xml.createElement("minAngle");
    gauge.appendChild(minAngle);
    minAngleText = xml.createTextNode("-90");
    minAngle.appendChild(minAngleText);

    maxAngle = xml.createElement("maxAngle");
    gauge.appendChild(maxAngle);
    maxAngleText = xml.createTextNode("90");
    maxAngle.appendChild(maxAngleText);

    minValue = xml.createElement("minValue");
    gauge.appendChild(minValue);
    minValueText = xml.createTextNode("0");
    minValue.appendChild(minValueText);

    maxValue = xml.createElement("maxValue");
    gauge.appendChild(maxValue);
    maxValueText = xml.createTextNode("180");
    maxValue.appendChild(maxValueText);

    QDomElement redZone = xml.createElement("redZone");
    gauge.appendChild(redZone);
    QDomText redZoneText = xml.createTextNode("70");
    redZone.appendChild(redZoneText);

    //save to file
    QTextStream output(&file);
    output << xml.toString();

    file.close();

    return true;
}

























