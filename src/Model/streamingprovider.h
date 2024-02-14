#ifndef STREAMINGPROVIDER_H
#define STREAMINGPROVIDER_H

#include <QQuickImageProvider>
#include <QObject>

#include "../Common/Singleton.h"
#include "streamingmodel.h"

class StreamingProvider : public QQuickImageProvider, public QObject, public Singleton<StreamingProvider>
{
    Q_OBJECT

public:
    explicit StreamingProvider(QObject *parent = nullptr);

    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;

signals:
    void imageChanged();

public slots:
    void updateImage(const QImage &image);

private:
    QImage receiveImage;
};

#endif // STREAMINGPROVIDER_H
