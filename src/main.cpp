#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "VideoStreamer/videostreamer.h"

#include "sio_client.h"

int main(int argc, char *argv[])
{
// #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
//     QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
// #endif
//     QGuiApplication app(argc, argv);

//     QQmlApplicationEngine engine;
//     const QUrl url(QStringLiteral("qrc:/src/qml/main.qml"));
//     QObject::connect(
//         &engine,
//         &QQmlApplicationEngine::objectCreated,
//         &app,
//         [url](QObject *obj, const QUrl &objUrl) {
//             if (!obj && url == objUrl)
//                 QCoreApplication::exit(-1);
//         },
//         Qt::QueuedConnection);
//     engine.load(url);

//     return app.exec();

    VideoStreamer manager;

    QList<QString> urls;

    urls.append("rtsp://210.99.70.120:1935/live/cctv001.stream");
    urls.append("rtsp://210.99.70.120:1935/live/cctv003.stream");
    urls.append("rtsp://210.99.70.120:1935/live/cctv004.stream");

    manager.openVideos(urls);
}
