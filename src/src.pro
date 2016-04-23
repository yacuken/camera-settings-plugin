TEMPLATE = lib
TARGET = onyxcamerasettings-qt5
CONFIG += qt hide_symbols 
CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0
QT += dbus qml quick
QT -= gui

SOURCES += \
    settingsui.cpp

HEADERS += \
    settingsui.h

target.path = $$[QT_INSTALL_LIBS]

INSTALLS += target
