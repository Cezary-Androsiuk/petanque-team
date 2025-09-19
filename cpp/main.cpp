#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QPointer>
#include <QIcon>

#include "SingletonManager.h"
#include "DoubleStartProtection.h"
#include "storages/Personalization.h"
#include "Backend.h"
#include "support/LogQML.h"

int main(int argc, char *argv[])
{
    std::unique_ptr<SingletonManager> sm =
        std::make_unique<SingletonManager>();
    TRF;

    std::unique_ptr<QGuiApplication> app =
        std::make_unique<QGuiApplication>(argc, argv);
    std::unique_ptr<QQmlApplicationEngine> engine =
        std::make_unique<QQmlApplicationEngine>();

    app->setApplicationDisplayName(QString("Petanque Team ") + version);

    QPointer<Backend> backend(new Backend(app.get()));
    QPointer<LogQML> logQML(new LogQML(app.get()));

    engine->rootContext()->setContextProperty("DoubleStartProtection", DoubleStartProtection::getInstance());
    engine->rootContext()->setContextProperty("Personalization", Personalization::getInstance());
    engine->rootContext()->setContextProperty("Backend", backend);
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
    /// this will remove all related pointers
    engine.reset();
    app.reset();

    I("engine and app deleted");

    /// SingletonManager - delete all singletons
    sm.reset();

    return exitValue;
}
