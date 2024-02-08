#ifndef DETECTIONMANAGER_H
#define DETECTIONMANAGER_H

#include <QFile>

#include "class_detector.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define YOLO_CFG "..\\TensorRTSP\\yolo\\yolov4.cfg"
#define YOLO_WEIGHTS "..\\TensorRTSP\\yolo\\yolov4.weights"

class DetectionManager
{
public:
    DetectionManager() : detector(std::make_unique<Detector>())
    {
        if(!checkYoloConfig() && !checkYoloWeights()) {
            return;
        }

        config_v4.net_type = YOLOV4;
        config_v4.file_model_cfg = YOLO_CFG;
        config_v4.file_model_weights = YOLO_WEIGHTS;
        config_v4.inference_precison = FP32;
        config_v4.detect_thresh = 0.5;
        detector->init(config_v4);
    }

    inline void detect(const std::vector<cv::Mat> &matImage, std::vector<BatchResult> &batchResult)
    {
        detector->detect(matImage, batchResult);
    }

    inline void drawLabel(cv::Mat &frame, const Result &result)
    {
        cv::rectangle(frame, result.rect, cv::Scalar(255,  0,  0),  2);

        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << "id:" << result.id << "  score:" << result.prob;

        cv::putText(frame, stream.str(), cv::Point(result.rect.x, result.rect.y -  5),  0,  0.5, cv::Scalar(0,  0,  255),  2);
    }

private:


    bool checkYoloConfig() const
    {
        return QFile::exists(YOLO_CFG);
    }

    bool checkYoloWeights() const
    {
        return QFile::exists(YOLO_WEIGHTS);
    }

    Config config_v4;
    std::unique_ptr<Detector> detector;
    Result rectangle;
};

#endif // DETECTIONMANAGER_H
