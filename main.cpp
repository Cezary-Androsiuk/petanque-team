#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Backend *backend = new Backend(&app);
    // engine.rootContext()->setContextProperty("Backend", backend);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    // QObject::connect(
    //     &engine,
    //     &QQmlApplicationEngine::objectCreated,
    //     Initializer::getInstance(),
    //     &Initializer::initialize);
    engine.loadFromModule("PetanqueTeam", "Main");

    return app.exec();
}
