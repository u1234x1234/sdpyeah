#include "application_controller.h"

#include <QFile>
#include <QDir>
#include <QStandardPaths>

application_controller::application_controller()
{
    QString write_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(write_path);
    if (!dir.exists())
        dir.mkpath(".");

    qDebug() << "constructor write path " << write_path;

    QString prebuilt_path;
#ifdef Q_OS_ANDROID
    prebuilt_path = ":/prebuilt/arm-linux-androideabi/";
#else
    prebuilt_path = ":/prebuilt/x86_64-linux/";
#endif

    qDebug() << "prebuilt read path " << prebuilt_path;

    QFile::copy(prebuilt_path + "dbclient", write_path + "/dbclient");

    QFile dbclient_file(write_path + "/dbclient");
    dbclient_file.setPermissions(QFile::ExeOwner);

    sshWrapper = new SshWrapper("192.168.1.83", "linux12341234", "22", "q2w3e4r");
}
