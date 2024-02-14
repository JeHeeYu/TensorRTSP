#include "streamingprovider.h"

StreamingProvider::StreamingProvider(QObject *parent) : QObject(parent), QQuickImageProvider(QQuickImageProvider::Image)
{
    receiveImage = QImage(100, 100,QImage::Format_RGB888);

    QObject::connect(StreamingModel::Instance(), &StreamingModel::newImage, this, &StreamingProvider::updateImage);
}

QImage StreamingProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    return receiveImage;
}
void StreamingProvider::updateImage(const QImage &image)
{
    receiveImage = image;

    emit imageChanged();
}
