#ifndef APPLICATION_CONTROLLER_H
#define APPLICATION_CONTROLLER_H

#include "sshwrapper.h"
#include "commandexecutor.h"
#include "sshconnectionmodel.h"

#include <QObject>
#include <QDebug>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QProcess>
#include <QTimer>
#include <QTextCodec>
#include <QQuickItem>

class application_controller : public QObject
{
    Q_OBJECT

public:
    explicit application_controller(QQmlApplicationEngine *engine);
    ~application_controller();

    Q_INVOKABLE void func(int status)
    {
//        QObject* textInput = engine->rootObjects()[0]->findChild<QObject*>("textInput");
//        r.clear();
//        sshProcess->write("top -bn 1\n");
    }
    static QObject* FindItemByName(QList<QObject*> nodes, const QString& name);

public slots:
    void executeCommand();
    void mySlot()
    {
//        QObject* textInput = engine->rootObjects()[0]->findChild<QObject*>("textInput");
        r.append(sshProcess->readAllStandardOutput());
        qDebug() << r;
//        textInput->setProperty("text", r);
    }
    void updateCaption() {
        r.append(sshProcess->readAllStandardOutput());
        qDebug() << r;
    }
    void removeConnection(int index);
    void addConnection();
    void beforeQuit();
    void connectToHost(int index);

private:
    int currentConnectionIndex;
    QString r;
    QProcess *sshProcess;
    QTimer *timer;
    QQmlApplicationEngine *engine;
    SshConnectionModel sshConnectionModel;
};

#endif // APPLICATION_CONTROLLER_H
