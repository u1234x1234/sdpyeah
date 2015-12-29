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

    qDebug() << write_path;
    QFile::copy(":/dbclient", write_path + "/dbclient");
}
