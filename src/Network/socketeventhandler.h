#ifndef SOCKETEVENTHANDLER_H
#define SOCKETEVENTHANDLER_H

#include <QObject>

class SocketEventHandler : public QObject
{
    explicit SocketEventHandler(QObject *parent = nullptr);
    ~SocketEventHandler();
};

#endif // SOCKETEVENTHANDLER_H
