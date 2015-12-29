#ifndef APPLICATION_CONTROLLER_H
#define APPLICATION_CONTROLLER_H

#include <QObject>
#include <QDebug>
#include <iostream>
#include <QQmlApplicationEngine>
#include <chrono>
#include <thread>
#include <QList>
#include <QQmlEngine>
#include <QObject>
#include  <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QScreen>
#include <QPixmap>
#include <QProcess>
#include <QStandardPaths>

using namespace std;


class application_controller : public QObject
{
    Q_OBJECT

public:
    explicit application_controller();

    Q_INVOKABLE void func(int status)
    {
        auto exec1 = [](const char* cmd)  -> string
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

        string s = exec1("DROPBEAR_PASSWORD=q2w3e4r /data/data/org.qtproject.example.sdpyeah/files/dbclient linux12341234@192.168.1.83 -y \'ls\'");
        qDebug() << QString::fromStdString(s);
//        qDebug() << QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);



    }

public slots:
    void mySlot(int status)
    {
    }

private:

};

#endif // APPLICATION_CONTROLLER_H
