#ifndef APPLICATION_CONTROLLER_H
#define APPLICATION_CONTROLLER_H

#include "sshwrapper.h"
#include "commandexecutor.h"

#include <QObject>
#include <QDebug>
#include <QQmlContext>
#include <QQmlApplicationEngine>

class application_controller : public QObject
{
    Q_OBJECT

public:
    explicit application_controller(QQmlApplicationEngine *engine);

    Q_INVOKABLE void func(int status)
    {
        QStringList result = commandExecutor->getDirectoryContents("");
//        qDebug() << result;

        QObject* textInput = engine->rootObjects()[0]->findChild<QObject*>("textInput");

        qDebug() << textInput;
        if (textInput) {
            QString r;
            for (auto it : result)
                r += it + "\n";
            textInput->setProperty("text", r);
        }
    }

public slots:
    void mySlot(int status)
    {
    }

private:
    SshWrapper *sshWrapper;
    CommandExecutor *commandExecutor;
    QQmlApplicationEngine *engine;
};

#endif // APPLICATION_CONTROLLER_H
