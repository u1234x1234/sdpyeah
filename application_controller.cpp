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

    QFile::remove(write_path + "/dbclient");
    QFile::copy(prebuilt_path + "dbclient", write_path + "/dbclient");
    QFile dbclient_file(write_path + "/dbclient");
    dbclient_file.setPermissions(QFile::ExeUser);

    sshProcess = new QProcess();
}

application_controller::~application_controller()
{
    sshProcess->terminate();
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
    qDebug() << dbclient_location;

    setenv("DROPBEAR_PASSWORD", connection.password().toStdString().c_str(), 1);
    QProcess tmpSshProccess;
    QString com = "sh -c \"" + dbclient_location + " " + connection.host() + " -y " + "\'ls\'" + "\"";
    qDebug() << com;
    tmpSshProccess.start(com);

    qDebug() << "started" << tmpSshProccess.waitForStarted(500);
    qDebug() << "ready read" << tmpSshProccess.waitForReadyRead(100);
    bool finished = tmpSshProccess.waitForFinished(3000);
    qDebug() << "finished" << finished;

    QString result = tmpSshProccess.readAllStandardOutput();

    qDebug() << "output:" << result;
    qDebug() << "state:" << tmpSshProccess.state();
    if (!finished || result.size() == 0){
        qDebug() << "could not connect to host" << connection.host();
        QObject *hostsPage = FindItemByName(engine->rootObjects(), "hostsPage");
        QMetaObject::invokeMethod(hostsPage, "connectionError");
        return;
    }
    QMetaObject::invokeMethod(engine->rootObjects()[0], "swapPages");
    currentConnectionIndex = index;

    QObject* textInput = engine->rootObjects()[0]->findChild<QObject*>("textInput");
    QFont f = textInput->property("font").value<QFont>();
    f.setFixedPitch(true);
    f.setStyleHint(QFont::TypeWriter);
    f.setFamily("Monospace");
    textInput->setProperty("font",f);


    QFile configFile(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + connection.host());
    configFile.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!configFile.isOpen()){
        qDebug() << "- Error, unable to open" << configFile.fileName() << "for output";
    }

    QObject *printFile = FindItemByName(engine->rootObjects(), "printInput");
    QString fileToPrint;
    QDataStream inStream(&configFile);
    inStream >> fileToPrint;
    printFile->setProperty("text", fileToPrint);
}

void application_controller::backToHostsPage()
{
    QMetaObject::invokeMethod(engine->rootObjects()[0], "swapPages");

    //save filename in printFile field to storage
    SshConnection connection = sshConnectionModel.getConnections().at(currentConnectionIndex);

    QFile configFile(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + connection.host());
    configFile.open(QIODevice::WriteOnly | QIODevice::Text);


    if(!configFile.isOpen()){
        qDebug() << "- Error, unable to open" << configFile.fileName() << "for output";
    }

    QObject *printFile = FindItemByName(engine->rootObjects(), "printInput");
    QString fileToPrint = printFile->property("text").value<QString>();

    qDebug() << configFile.fileName() << fileToPrint;
    QDataStream outStream(&configFile);
    outStream << fileToPrint;

    configFile.close();
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

void application_controller::executeCommand(QString command)
{
    SshConnection connection = sshConnectionModel.getConnections().at(currentConnectionIndex);

    QString dbclient_location = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/dbclient";
    sshProcess->close();
    sshProcess->terminate();
    qDebug() << dbclient_location;

    connect(sshProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(updateText()));
    setenv("DROPBEAR_PASSWORD", connection.password().toStdString().c_str(), 1);
    r.clear();
    QString com = "sh -c \"" + dbclient_location + " " + connection.host() + " -y " + "\'" + command + "\'" + "\"";
    qDebug() << com;
    sshProcess->start(com);

    //    timer = new QTimer();
    //    connect(timer, SIGNAL(timeout()), this, SLOT(updateText()));
    //    timer->start(300);
}

void application_controller::updateText()
{
    QObject* textInput = engine->rootObjects()[0]->findChild<QObject*>("textInput");
    r.append(sshProcess->readAllStandardOutput());
    qDebug() << r;
    textInput->setProperty("text", r);
}

void application_controller::removeConnection(int index)
{
    sshConnectionModel.removeRows(index);
}

void application_controller::addConnection()
{
    sshConnectionModel.addSshConnection(SshConnection());
}
