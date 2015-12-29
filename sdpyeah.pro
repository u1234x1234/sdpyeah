TEMPLATE = app
TARGET = sdpyeah

QT += qml quick
CONFIG += c++11 static

SOURCES += main.cpp \
	application_controller.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += application_controller.h


include(deployment.pri)
