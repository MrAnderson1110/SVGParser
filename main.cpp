#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "svgreader.h"

const QString inPath = "/home/mranderson/Work/Графы/Агрегаты/graph.svg";

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);



    SVGReader::instance()->setPath(inPath);
    SVGReader::instance()->readAll();

    return app.exec();
}
