#include "commandexecutor.h"
#include <QDebug>

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

QStringList CommandExecutor::getTop()
{
    QString rawResult = sshWrapper->executeCommand("top -b -n 1 | head -n 15" );

    QStringList contents;
    contents = rawResult.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    qDebug() << contents;

    return contents;
}
