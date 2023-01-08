#include "subscriber.h"

static const QString topic = "network_devices";

Subscriber::Subscriber(const QHostAddress &addr, quint16 port, QObject* p)
    :QMQTT::Client(addr, port, p)
{
    connect(this, &Subscriber::connected, this, &Subscriber::onConnected);
    connect(this, &Subscriber::subscribed, this, &Subscriber::onConnected);
    connect(this, &Subscriber::received, this, &Subscriber::onReceived);
}

Subscriber::~Subscriber(){

}

void Subscriber::onConnected()
{
    //qDebug()<<"Connected";
    subscribe(topic, 0);
}

void Subscriber::onSubscribed()
{
    qDebug()<<"Subscribed To: "<<topic;
}

void Subscriber::onReceived(const QMQTT::Message& msg)
{
    qDebug()<<"Received: "<<QString::fromUtf8(msg.payload());
}
