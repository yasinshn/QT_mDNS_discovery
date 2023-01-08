#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QObject>
#include <qmqtt.h>
#include <QTimer>
#include <QCoreApplication>
#include <QDebug>

class Publisher: public QMQTT::Client
{
    Q_OBJECT
public:
    explicit Publisher(const QHostAddress& address, const quint16 port, QObject* parent);
    virtual ~Publisher(){}
    quint16 msgIndex;
    QTimer timer;
    QString payload;
    void setPayloadData(QString&);
public slots:
    void onConnected();
    void sendMessage();
    void onDisconnected();

};

#endif // PUBLISHER_H
