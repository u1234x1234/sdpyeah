#include "application_controller.h"

#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDateTime>

application_controller::application_controller(QQmlApplicationEngine *engine)
    :engine(engine)
{
    sshConnectionModel.addSshConnection(SshConnection("conn1", "dima@192.168.1.192"));
    sshConnectionModel.addSshConnection(SshConnection("conn2", "dima2@192.168.1.192"));

    QQmlContext *ctxt = engine->rootContext();
    ctxt->setContextProperty("appModel", &sshConnectionModel);
    ctxt->setContextProperty("currentDateTime", QDateTime::currentDateTime());

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
    //    QFile configFile;
//        auto q = FindItemByName(engine->rootObjects(), "zxc");
    //    qDebug() << q;
}

QObject* application_controller::FindItemByName(QList<QObject*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++){
        // search for node
        if (nodes.at(i) && nodes.at(i)->objectName() == name){
            return dynamic_cast<QObject*>(nodes.at(i));
        }
        // search in children
        else if (nodes.at(i) && nodes.at(i)->children().size() > 0){
            QObject* item = FindItemByName(nodes.at(i)->children(), name);
            if (item)
                return item;
        }
    }
    // not found
    return NULL;
}
