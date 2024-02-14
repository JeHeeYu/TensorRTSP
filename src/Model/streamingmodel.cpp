#include "streamingmodel.h"


StreamingModel::StreamingModel(QObject *parent) : QObject(parent)
{

}


void StreamingModel::updateImage(const QImage &image)
{
    emit newImage(image);
}
