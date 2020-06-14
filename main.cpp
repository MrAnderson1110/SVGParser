#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "svgreader.h"
#include "svgrecoder.h"

const QString inPath = "/home/mranderson/Work/Графы/Агрегаты/graph.svg";
const QString globalSettingPath = "/home/mranderson/Work/Графы/Агрегаты/JSONglobal";
const QString nodesFilePath = "/home/mranderson/Work/Графы/Агрегаты/JSONnodes";
const QString edgesFilePath = "/home/mranderson/Work/Графы/Агрегаты/JSONedges";
const QString arrowsFilePath = "/home/mranderson/Work/Графы/Агрегаты/JSONarrows";
const QString textFilePath = "/home/mranderson/Work/Графы/Агрегаты/JSONtext";

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

    svgReader->setPath(inPath);
    svgRecoder->setGlobalSettingsPath(globalSettingPath);
    svgRecoder->setTextPath(textFilePath);
    svgRecoder->setNodesPath(nodesFilePath);
    svgRecoder->setEdgesPath(edgesFilePath);
    svgRecoder->setArrowsPath(arrowsFilePath);
    svgRecoder->parse();
    svgRecoder->record();
    return app.exec();
}
