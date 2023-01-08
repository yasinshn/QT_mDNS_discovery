#include <QCoreApplication>
#include <publisher.h>
#include <subscriber.h>
#include <QVector>

#include <qmdnsengine/abstractserver.h>
#include <qmdnsengine/server.h>
#include <qmdnsengine/service.h>
#include <qmdnsengine/browser.h>
#include <qmdnsengine/cache.h>
#include <qmdnsengine/resolver.h>
#include <qmdnsengine/message.h>

QMdnsEngine::Server *server;
QMdnsEngine::Cache cache;
QString payloadString;
QString devAddress;
QVector<QMdnsEngine::Service> devices;
QMdnsEngine::Resolver *resolver;
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


void addService(const QMdnsEngine::Service &service)
{
    devices.append(service);
    payloadString = "";
    qDebug()<<"New Device Added: "<<service.name();
    for(int i = 0; i < devices.length(); ++i)
    {
        payloadString.append(" Hostname: " + QString::fromUtf8(devices.at(i).hostname())
            + "   Name: " + QString::fromUtf8(devices.at(i).name())
            + "   Protocol: " + QString::fromUtf8(devices.at(i).type())
            + "   Port: " + QString::number(devices.at(i).port()) );
    }
    qDebug()<<"Devices : "<<payloadString;

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
        payloadString.append(" Hostname: " + QString::fromUtf8((*dev).hostname())
                     + "   Name: " + QString::fromUtf8((*dev).name())
                     + "   Protocol: " + QString::fromUtf8((*dev).type())
                     + "   Port: " + QString::number((*dev).port()));
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    server = new QMdnsEngine::Server(nullptr);
    browser = new QMdnsEngine::Browser(server,  "_http._tcp.local.", &cache);

    Publisher *pub = new Publisher(QHostAddress::LocalHost, 1883, nullptr);

    QObject::connect(browser, &QMdnsEngine::Browser::serviceAdded, qApp, addService);
    QObject::connect(browser, &QMdnsEngine::Browser::serviceRemoved, removeService);

    QObject::connect(server, &QMdnsEngine::Server::messageReceived,qApp,
                     [&](const QMdnsEngine::Message &message)
    {
        devAddress = "";
        devAddress.append(message.address().toString());
        payloadString.append("   Device Address: " + devAddress);
        pub->payload = payloadString;
        qDebug()<<"\nPayload String: "<<payloadString;
        //pub->payload = "Device Address: " + message.address().toString();
    });

    pub->setAutoReconnect(true);
    pub->setClientId("Client");
    pub->setWillRetain(true);
    pub->connectToHost();

    return a.exec();
}
