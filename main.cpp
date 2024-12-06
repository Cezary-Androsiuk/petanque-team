#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>

#include "cpp/DoubleStartProtection.h"
#include "cpp/Login.h"
#include "cpp/Backend.h"
#include "cpp/support/LogQML.h"
// #include "cpp/storages/Memory.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Backend *backend = new Backend(&app);
    Login *login = new Login(&app);

    LogQML *logQML = new LogQML(&app);

    engine.rootContext()->setContextProperty("DoubleStartProtection", DoubleStartProtection::getInstance());
    engine.rootContext()->setContextProperty("Backend", backend);
    engine.rootContext()->setContextProperty("Login", login);

    engine.rootContext()->setContextProperty("log", logQML);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        DoubleStartProtection::getInstance(),
        &DoubleStartProtection::verify);
    engine.loadFromModule("PetanqueTeam", "Main");

    return app.exec();
}
