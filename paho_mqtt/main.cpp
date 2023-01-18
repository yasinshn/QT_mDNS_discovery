#include <QCoreApplication>
#include <QHostAddress>
#include <iostream>
#include <string>
#include "publisher.h"

#include <qmdnsengine/abstractserver.h>
#include <qmdnsengine/server.h>
#include <qmdnsengine/service.h>
#include <qmdnsengine/browser.h>
#include <qmdnsengine/cache.h>
#include <qmdnsengine/resolver.h>
#include <qmdnsengine/message.h>

//mqtt variables
const char adr[] = "tcp://localhost:1883";
const char client_id[] = "Client4";
const char topic[] = "network_devices";

Publisher *pub;

//mdns variables
QMdnsEngine::Server *server;
QMdnsEngine::Cache cache;
std::string payloadString;
std::string devAddress;
QVector<QMdnsEngine::Service> devices;
QMdnsEngine::Browser *browser;

int findService(const QByteArray &name)
{
    for (auto i = devices.constBegin(); i != devices.constEnd(); ++i) {
        if ((*i).name() == name) {
            return i - devices.begin();
        }
    }

    return -1;
}


void addService(const QMdnsEngine::Service& service)
{
    devices.append(service);
    payloadString = "";
    qDebug()<<"New Device Added: "<<service.name();

    for(int i = 0; i < devices.length(); ++i)
    {
        payloadString.append("Hostname: " + devices.at(i).hostname().toStdString()
                             + "    Name: " + devices.at(i).name().toStdString()
                             + "    Protocol: " + devices.at(i).type().toStdString()
                             + "    Port: " + std::to_string(devices.at(i).port())
                             + "                    *********device seperator***********     ");
    }
    QString strTmp = QString::fromStdString(payloadString);
    qDebug()<<"Devices : "<<strTmp;
}


void removeService(const QMdnsEngine::Service &service)
{
    int i = findService(service.name());
    if(i != -1)
    {
        devices.removeAt(i);
        qDebug()<<"Removed Device: "<<devices.at(i).name();
    }
    payloadString = "";

    for(auto dev = devices.begin(); dev != devices.end(); ++dev)
    {
        payloadString.append("      Hostname: " + devices.at(i).hostname().toStdString()
                             + "    Name: " + devices.at(i).name().toStdString()
                             + "    Protocol: " + devices.at(i).type().toStdString()
                             + "    Port: " + std::to_string(devices.at(i).port()) );
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    pub = new Publisher(adr,  client_id);
    pub->setTopic(topic);
    //pub->setPayload("deneme");
    server = new QMdnsEngine::Server(nullptr);
    browser = new QMdnsEngine::Browser(server,  "_http._tcp.local.", &cache);

    QObject::connect(browser, &QMdnsEngine::Browser::serviceAdded, qApp, addService);
    QObject::connect(browser, &QMdnsEngine::Browser::serviceRemoved, removeService);

    QObject::connect(server, &QMdnsEngine::Server::messageReceived,qApp,
                     [&](const QMdnsEngine::Message &message)
    {
        devAddress = "";
        devAddress.append(message.address().toString().toUtf8().constData());
        qDebug()<<"Device address: "<<message.address();
        payloadString.append("   Device Address: " + devAddress);

        char* str = const_cast<char*>(payloadString.c_str());
        pub->setPayload(str);

        /*
        QString strTmp = QString::fromStdString(payloadString);
        qDebug()<<"\nPayload String: "<<strTmp;
        */
    });

    return a.exec();
}
