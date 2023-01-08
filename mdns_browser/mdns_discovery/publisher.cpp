#include "publisher.h"
static const QString topic = "network_devices";

Publisher::Publisher(const QHostAddress& address, const quint16 port, QObject* parent)
    :QMQTT::Client(address, port, parent), msgIndex(0)
{
    connect(this, &Publisher::connected, this, &Publisher::onConnected);
    connect(&timer, &QTimer::timeout, this, &Publisher::sendMessage);
    connect(this, &Publisher::disconnected, this, &Publisher::onDisconnected);
}

void Publisher::onConnected()
{
    this->subscribe(topic);
    timer.start(1000);
}

void Publisher::sendMessage()
{
    QByteArray qb = payload.toUtf8();
    QMQTT::Message msg(msgIndex, topic, qb);
    this->publish(msg);
    qDebug()<<msgIndex<<"\n"<<topic<<"\n"<<payload;
    msgIndex++;
}

void Publisher::onDisconnected()
{
    //QTimer::singleShot(0, qApp, &QCoreApplication::quit);
    qDebug()<<"Disconnected";
}

void Publisher::setPayloadData(QString &pData){
    this->payload = pData;
}

