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

//        qDebug() << system("ls1");
        string s = exec1("/sdcard/dbclient > /sdcard/res");
        qDebug() << QString::fromStdString(s);
//        qDebug() << test_func();
//        QProcess proc;
//        proc.setStandardOutputFile("/sdcard/res");
//        proc.start("ls");
//        proc.waitForFinished();
//        qDebug() << proc.readAll();
//        qDebug() << status;
    }

public slots:
    void mySlot(int status)
    {
    }

private:

};

#endif // APPLICATION_CONTROLLER_H
