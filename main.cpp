#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "application_controller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    application_controller ac(&engine);

    engine.rootContext()->setContextProperty("ac", &ac);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    return app.exec();
}
