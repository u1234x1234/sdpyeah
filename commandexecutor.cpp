#include "commandexecutor.h"

CommandExecutor::CommandExecutor(SshWrapper *sshWrapper)
    :sshWrapper(sshWrapper)
{

}

QStringList CommandExecutor::getDirectoryContents(QString directory)
{
    QString rawResult = sshWrapper->executeCommand("ls " + directory);

    QStringList contents;
    contents = rawResult.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);

    return contents;
}
