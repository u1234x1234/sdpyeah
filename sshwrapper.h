#ifndef SSHWRAPPER_H
#define SSHWRAPPER_H

#include <QString>

class SshWrapper
{
public:
    SshWrapper(QString host, QString user, QString port, QString password);
    QString executeCommand(QString command);
private:
    QString host;
    QString user;
    QString port;
    QString password;
};

#endif // SSHWRAPPER_H
