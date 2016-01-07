#include "application_controller.h"

#include <QFile>
#include <QDir>
#include <QStandardPaths>

application_controller::application_controller(QQmlApplicationEngine *engine)
    :engine(engine)
{
//    QString write_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
//    QDir dir(write_path);
//    if (!dir.exists())
//        dir.mkpath(".");

//    qDebug() << "constructor write path " << write_path;

//    QString prebuilt_path;
//#ifdef Q_OS_ANDROID
//    prebuilt_path = ":/prebuilt/arm-linux-androideabi/";
//#else
//    prebuilt_path = ":/prebuilt/x86_64-linux/";
//#endif

//    qDebug() << "prebuilt read path " << prebuilt_path;
//    QFile::copy(prebuilt_path + "dbclient", write_path + "/dbclient");

//    QFile dbclient_file(write_path + "/dbclient");
//    dbclient_file.setPermissions(QFile::ExeOwner);


//    QString dbclient_location = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/dbclient";
//    sshProcess = new QProcess();

//    connect(sshProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(mySlot()));
//    setenv("DROPBEAR_PASSWORD", "q2w3e4r", 1);
//    sshProcess->start(dbclient_location, QStringList() << "dima@192.168.1.192" << "-y");
//    sshProcess->waitForStarted();

//    timer = new QTimer();
//    connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
//    timer->start(300);
}

application_controller::~application_controller()
{
    sshProcess->terminate();
}

void application_controller::beforeQuit()
{
    qDebug() << "quit";
}
