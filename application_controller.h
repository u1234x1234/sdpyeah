#ifndef APPLICATION_CONTROLLER_H
#define APPLICATION_CONTROLLER_H

#include "sshwrapper.h"
#include "commandexecutor.h"

#include <QObject>
#include <QDebug>

class application_controller : public QObject
{
    Q_OBJECT

public:
    explicit application_controller();

    Q_INVOKABLE void func(int status)
    {
//        qDebug() << sshWrapper->executeCommand("ls");
        QStringList result = commandExecutor->getDirectoryContents("");
        qDebug() << result;
    }

public slots:
    void mySlot(int status)
    {
    }

private:
    SshWrapper *sshWrapper;
    CommandExecutor *commandExecutor;
};

#endif // APPLICATION_CONTROLLER_H
