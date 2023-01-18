#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QObject>
#include <QTimer>
#include <MQTTClient.h>
#include <QDebug>
#include <string>

class Publisher : public QObject
{
    Q_OBJECT
public:
    explicit Publisher(const char* peerAddress, const char* client_id);
    void setTopic(const char*);
    void setPayload(const char*);
    void setQos(uint8_t);
    void setRetain(uint8_t);
signals:

private:
    MQTTClient client;
    MQTTClient_message message;
    MQTTClient_connectOptions conn_opt;
    MQTTClient_deliveryToken token;

    QTimer *timer;

    char topic[50];
    char clientId[50];
    char address[80];
};

#endif // PUBLISHER_H
