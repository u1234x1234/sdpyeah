TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
	application_controller.cpp

INCLUDEPATH += ../dropbear/
LIBS += -L../dropbear/ -llibdropbear -llibtommath -llibtomcrypt

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += application_controller.h
