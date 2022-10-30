#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QGuiApplication>
#include "core.h"
#include "SuggestionListModel.h"
#include "demomodel.h"

int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/sail-multitran.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //   - SailfishApp::pathToMainQml() to get a QUrl to the main QML file
    //
    // To display the view, call "show()" (will show fullscreen on device).

    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    Core core;
//    SuggestionListModel suggestionListModel(&core);

    QQmlContext *context = view.data()->rootContext();
    context->setContextProperty("core", &core);

    qmlRegisterType<SuggestionListModel>("harbour.multitran", 1, 0, "SuggestionListModel");


    view->setSource(SailfishApp::pathTo("qml/sail-multitran.qml"));
    view->show();


    return app->exec();
}
