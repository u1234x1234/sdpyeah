#ifndef APPLICATION_CONTROLLER_H
#define APPLICATION_CONTROLLER_H

#include "sshwrapper.h"
#include "commandexecutor.h"

#include <QObject>
#include <QDebug>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QProcess>
#include <QTimer>
#include <QTextCodec>

class application_controller : public QObject
{
    Q_OBJECT

public:
    explicit application_controller(QQmlApplicationEngine *engine);
    ~application_controller();

    Q_INVOKABLE void func(int status)
    {
        QObject* textInput = engine->rootObjects()[0]->findChild<QObject*>("textInput");

        r.clear();
        sshProcess->write("top -bn 1\n");
    }

public slots:
    void mySlot()
    {
        QObject* textInput = engine->rootObjects()[0]->findChild<QObject*>("textInput");
        r.append(sshProcess->readAllStandardOutput());
        qDebug() << r;
        textInput->setProperty("text", r);
    }
    void updateCaption() {
    }

private:
    QString r;
    QProcess p1, p2;
    QProcess *sshProcess;
    QTimer *timer;
    SshWrapper *sshWrapper;
    CommandExecutor *commandExecutor;
    QQmlApplicationEngine *engine;
};

#endif // APPLICATION_CONTROLLER_H
