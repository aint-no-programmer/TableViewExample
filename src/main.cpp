#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QSettings>
#include <QThread>
#include <QObject>
#include <QIcon>

#include "QMLAdapter.h"
#include "TableModel.h"
#include "Adapters.h"


int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //    QGuiApplication app(argc, argv);
    //swap with QApplication, because QtCharts require it
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("data/logo.png"));
    QQmlApplicationEngine engine;
    //! [registertype]
    qmlRegisterType<TableModel>("TableModel", 1, 0, "TableModel");
    //
    QSettings settings("gui.config", QSettings::NativeFormat);
    //
    QMLAdapter qmlAdapter(&settings);
    engine.rootContext()->setContextProperty("qmlAdapter", &qmlAdapter);
    //
    DataModel dataModel;     
    //
    TableModel tableModel;
    tableModel.setDataModel(&dataModel);
    engine.rootContext()->setContextProperty("tableModel", &tableModel);

    FakeAdapter adapter(&dataModel, &qmlAdapter);
    engine.rootContext()->setContextProperty("adapter", &adapter);

    QThread thread;
    adapter.moveToThread(&thread);
    thread.start();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, 
				&QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
				        if (!obj && url == objUrl) QCoreApplication::exit(-1);
				    }, 
				Qt::QueuedConnection);
    engine.load(url);

    auto ret = app.exec();

    thread.quit();
    thread.wait();

    return ret;
}
