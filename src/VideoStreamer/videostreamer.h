#ifndef VIDEOSTREAMER_H
#define VIDEOSTREAMER_H



#include <QObject>
#include <QThread>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "detectionmanager.h"

class VideoStreamer : public QThread
{
    Q_OBJECT
public:

   explicit VideoStreamer(QThread *parent = nullptr);
    void run() override;
    void openVideos(QList<QString> videoList);

private:
    QList<cv::Mat> frame;
    QList<cv::VideoCapture> videos;
    QList<QString> videoUrls;
};

#endif // VIDEOSTREAMER_H
