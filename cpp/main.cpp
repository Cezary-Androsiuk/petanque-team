#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QPointer>

#include "cpp/SingletonManager.h"
#include "cpp/DoubleStartProtection.h"
#include "cpp/Login.h"
#include "cpp/Backend.h"
#include "cpp/support/LogQML.h"

int main(int argc, char *argv[])
{
    std::unique_ptr<SingletonManager> sm =
        std::make_unique<SingletonManager>();

    std::unique_ptr<QGuiApplication> app =
        std::make_unique<QGuiApplication>(argc, argv);
    std::unique_ptr<QQmlApplicationEngine> engine =
        std::make_unique<QQmlApplicationEngine>();

    QPointer<Backend> backend(new Backend(app.get()));
    QPointer<Login> login(new Login(app.get()));
    QPointer<LogQML> logQML(new LogQML(app.get()));

    engine->rootContext()->setContextProperty("DoubleStartProtection", DoubleStartProtection::getInstance());
    engine->rootContext()->setContextProperty("Backend", backend);
    engine->rootContext()->setContextProperty("Login", login);
    engine->rootContext()->setContextProperty("log", logQML);

    QObject::connect(
        engine.get(),
        &QQmlApplicationEngine::objectCreationFailed,
        app.get(),
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    QObject::connect(
        engine.get(),
        &QQmlApplicationEngine::objectCreated,
        DoubleStartProtection::getInstance(),
        &DoubleStartProtection::verify);
    engine->loadFromModule("PetanqueTeam", "Main");

    int exitValue = app->exec(); /// Loop

    /// reset QGuiApplication and QQmlApplicationEngine
    engine.reset();
    app.reset();

    /// SingletonManager - delete all singletons
    sm.reset();

    return exitValue;
}
