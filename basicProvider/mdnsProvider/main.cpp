#include <QCoreApplication>
#include <qmdnsengine/abstractserver.h>
#include <qmdnsengine/server.h>
#include <qmdnsengine/hostname.h>
#include <qmdnsengine/provider.h>
#include <qmdnsengine/service.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QMdnsEngine::Server server;
    QMdnsEngine::Hostname hostname(&server);
    QMdnsEngine::Provider provider(&server, &hostname);

    QMdnsEngine::Service service;
    service.setType("_http._tcp.local.");
    service.setName("Ya96sin");
    service.setPort(5454);
    provider.update(service);

    return a.exec();
}
