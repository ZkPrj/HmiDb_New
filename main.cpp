#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "DataModelCore.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    DataModelCore* core = new DataModelCore;
    core->updateDbInfo();
    engine.rootContext()->setContextProperty("core", core);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
