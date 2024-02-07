#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "class_timer.hpp"
#include "class_detector.h"

#include "class_yolo_detector.hpp"

#include "cuda_runtime_api.h"

#include "NvInferRuntimeCommon.h".h"

#define YOLO_CFG "D:\\Workstations\\TensorRTSP\\TensorRTSP\\yolo\\yolov4.cfg"
#define YOLO_WEIGHTS "D:\\Workstations\\TensorRTSP\\TensorRTSP\\yolo\\yolov4.weights"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    Config config_v4;
    std::unique_ptr<Detector> detector{ new Detector() };

    config_v4.net_type = YOLOV4;
    config_v4.file_model_cfg = YOLO_CFG;
    config_v4.file_model_weights = YOLO_WEIGHTS;
    config_v4.calibration_image_list_file_txt = "../configs/calibration_images.txt";
    config_v4.inference_precison = FP32;
    config_v4.detect_thresh = 0.5;
    detector->init(config_v4);

    return app.exec();
}
