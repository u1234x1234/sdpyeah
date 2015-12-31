#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include "sshwrapper.h"

#include <QStringList>

class CommandExecutor
{
public:
    CommandExecutor(SshWrapper *sshWrapper);
    QStringList getDirectoryContents(QString directory);
    QStringList getTop();
private:
    SshWrapper *sshWrapper;
};

#endif // COMMANDEXECUTOR_H
