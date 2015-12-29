#include "sshwrapper.h"

#include <string>
#include <memory>

#include <QStandardPaths>
#include <QDebug>

SshWrapper::SshWrapper(QString host, QString user, QString port, QString password)
    :host(host), user(user), port(port), password(password)
{

}

QString SshWrapper::executeCommand(QString command)
{
    auto exec = [](const char* cmd) -> std::string
    {
        std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
        if (!pipe) return "ERROR";
        char buffer[128];
        std::string result = "";
        while (!feof(pipe.get())) {
            if (fgets(buffer, 128, pipe.get()) != NULL)
                result += buffer;
        }
        return result;
    };

    QString dbclient_location = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/dbclient";

    QString bashCommand = QString("DROPBEAR_PASSWORD=%1 %2 %3@%4 -y \'%5\'").arg(password, dbclient_location, user, host, command);

    qDebug() << "command: " << bashCommand;

    std::string s = exec(bashCommand.toStdString().c_str());

    return QString::fromStdString(s);
}
