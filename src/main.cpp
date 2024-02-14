#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "VideoStreamer/videostreamer.h"
#include "Model/streamingmodel.h"
#include "Model/streamingprovider.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qputenv("ffmpeg", "windows");

    QQmlApplicationEngine engine;

    StreamingModel streamingModel;

    qmlRegisterType<StreamingModel>("StreamingModel", 1, 0, "StreamingModel");

    engine.rootContext()->setContextProperty("StreamingModel", &streamingModel);
    engine.rootContext()->setContextProperty("StreamingProvider", StreamingProvider::Instance());
    engine.addImageProvider(QLatin1String("providers"), StreamingProvider::Instance());

    const QUrl url(QStringLiteral("qrc:/src/qml/main.qml"));
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

    VideoStreamer manager;

    QList<QString> urls;

    urls.append("rtsp://210.99.70.120:1935/live/cctv001.stream");
    urls.append("rtsp://210.99.70.120:1935/live/cctv003.stream");
    urls.append("rtsp://210.99.70.120:1935/live/cctv004.stream");

    manager.openVideos(urls);

    return app.exec();
}
