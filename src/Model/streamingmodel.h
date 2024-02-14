#ifndef STREAMINGMODEL_H
#define STREAMINGMODEL_H

#include <QObject>
#include <QImage>

#include "../Common/Singleton.h"

class StreamingModel : public QObject, public Singleton<StreamingModel>
{
    Q_OBJECT

public:
    explicit StreamingModel(QObject *parent = nullptr);

    void updateImage(const QImage &image);

signals:
    void newImage(const QImage &image);

};

#endif // STREAMINGMODEL_H
