#include "application_controller.h"

#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDateTime>

application_controller::application_controller(QQmlApplicationEngine *engine)
    :engine(engine)
{
    // config reading
    QFile configFile(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/config");
    configFile.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!configFile.isOpen()){
        qDebug() << "- Error, unable to open" << configFile.fileName() << "for input";
    }

    QDataStream inStream(&configFile);
    inStream >> sshConnectionModel;
    configFile.close();


    QQmlContext *ctxt = engine->rootContext();
    ctxt->setContextProperty("appModel", &sshConnectionModel);

    // copy dbclient to application data location
    QString write_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(write_path);
    if (!dir.exists())
        dir.mkpath(".");

    QString prebuilt_path;
#ifdef Q_OS_ANDROID
    prebuilt_path = ":/prebuilt/arm-linux-androideabi/";
#else
    prebuilt_path = ":/prebuilt/x86_64-linux/";
#endif

    QFile::copy(prebuilt_path + "dbclient", write_path + "/dbclient");
    QFile dbclient_file(write_path + "/dbclient");
    dbclient_file.setPermissions(QFile::ExeOwner);
}

application_controller::~application_controller()
{
    sshProcess.terminate();
}

void application_controller::beforeQuit()
{
    // saving config to file
    QFile configFile(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/config");
    configFile.open(QIODevice::WriteOnly | QIODevice::Text);

    if(!configFile.isOpen()){
        qDebug() << "- Error, unable to open" << configFile.fileName() << "for output";
    }

    QDataStream outStream(&configFile);
    outStream << sshConnectionModel;

    configFile.close();
}

void application_controller::connectToHost(int index)
{
    SshConnection connection = sshConnectionModel.getConnections().at(index);
    qDebug() << connection.name() << connection.host() << connection.password();

    QString dbclient_location = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/dbclient";
    sshProcess.terminate();

    connect(&sshProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(mySlot()));
    setenv("DROPBEAR_PASSWORD", connection.password().toStdString().c_str(), 1);
//    sshProcess.start(dbclient_location, QStringList() << connection.host() << "-y");
    sshProcess.waitForStarted();
    sshProcess.waitForReadyRead(2000);
    if (sshProcess.state() != 2){
        qDebug() << "could not connect to host" << connection.host();
    }
    QMetaObject::invokeMethod(engine->rootObjects()[0], "swapPages");

//    timer = new QTimer();
//    connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
//    timer->start(300);
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
    return NULL;
}

void application_controller::removeConnection(int index)
{
    sshConnectionModel.removeRows(index);
}

void application_controller::addConnection()
{
    sshConnectionModel.addSshConnection(SshConnection());
}
