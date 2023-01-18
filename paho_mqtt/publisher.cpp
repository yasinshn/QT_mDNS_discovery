#include "publisher.h"

Publisher::Publisher(const char* peerAddress, const char* client_id)
{

    message = MQTTClient_message_initializer;
    message.retained = 1;
    message.qos = 1;
    message.msgid = 0;

    snprintf(address, strlen(peerAddress) + 1, "%s", peerAddress);
    snprintf(clientId, strlen(client_id) + 1, "%s", client_id);

    qDebug()<<address;
    qDebug()<<clientId;

    int ret = MQTTClient_create(&client, address, clientId, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    if(ret != MQTTCLIENT_SUCCESS)
    {
        qDebug()<<"Failed to create client";
    }

    conn_opt = MQTTClient_connectOptions_initializer;
    conn_opt.cleansession = 1;
    conn_opt.keepAliveInterval = 60;

    ret = MQTTClient_connect(client, &conn_opt);
    if(ret != MQTTCLIENT_SUCCESS)
    {
        qDebug()<<"Failed to connect server";
    }

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout, this, [this]()
    {
            MQTTClient_publishMessage(client, topic, &message, &token);
            message.msgid++;
            int rt = MQTTClient_waitForCompletion(client, token, 10000);
            if(rt != MQTTCLIENT_SUCCESS)
            {
                qDebug()<<"Failed to send message";
            }
    });

    timer->start(1000);

}

void Publisher::setPayload(const char *p)
{
    message.payload = (char*)p;
    message.payloadlen = strlen(p);
}

void Publisher::setTopic(const char *topic_)
{
    snprintf(this->topic, strlen(topic_) + 1, "%s", topic_);
    qDebug()<<"Topic changed to: "<<this->topic;
}

void Publisher::setQos(uint8_t qos)
{
    message.qos = qos;
}

void Publisher::setRetain(uint8_t r)
{
    message.retained = r;
}
