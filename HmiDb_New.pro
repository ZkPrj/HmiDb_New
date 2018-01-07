QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    DataModelCore.cpp \
    HmiDbModel.cpp \
    DbTableModel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    DataModelCore.h \
    HmiDbModel.h \
    DbTableModel.h

RC_ICONS = fly.ico
