#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>
#include <QHostAddress>
#include <qmqtt.h>
#include <QDebug>

class Subscriber : public QMQTT::Client
{
    Q_OBJECT
public:
   explicit Subscriber(const QHostAddress& address, quint16 port, QObject* parent);
   virtual ~Subscriber();
public slots:
    void onConnected();
    void onSubscribed();
    void onReceived(const QMQTT::Message&);

};

#endif // SUBSCRIBER_H
