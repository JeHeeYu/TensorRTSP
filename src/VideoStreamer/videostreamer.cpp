#include "videostreamer.h"

#include <QImage>

VideoStreamer::VideoStreamer(QThread *parent) : QThread(parent)
{

}

void VideoStreamer::openVideos(QList<QString> videoList)
{
    for(int i =  0; i < videoList.length(); i++) {
        videoUrls.append(videoList[i]);

        cv::VideoCapture video(videoUrls[i].toStdString());

        if (!video.isOpened()) {
            continue;
        }

        videos.append(video);
        frame.append(cv::Mat());
    }

    std::vector<BatchResult> batchResults;

    while(true) {
        for(int i =  0; i < videos.length(); i++) {
            if(!videos[i].read(frame[i])) {
            }

            std::vector<BatchResult> batchResult;
            std::vector<cv::Mat> batchImage = { frame[i] };
            DETECTIONMANAGER()->detect(batchImage, batchResult);

            for (const auto& result : batchResult[0]) {
                DETECTIONMANAGER()->drawLabel(frame[i], result);
            }

            std::string windowName = "Video Window " + std::to_string(i+1);

            // here image
            QImage currentImage = QImage((uchar*) frame[i].data, frame[i].cols, frame[i].rows, frame[i].step, QImage::Format_RGB888);
            StreamingModel::Instance()->updateImage(currentImage);

            cv::imshow(windowName, frame[i]);
        }

        if (cv::waitKey(1) >=  0) break;
    }

    for(auto &video : videos) {
        video.release();
    }

    cv::destroyAllWindows();
}
