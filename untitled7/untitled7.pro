QT += core gui widgets network

CONFIG += c++17 cmdline
DISTFILES += form.ui

SOURCES += main.cpp \
    control_panel.cpp \
    global_window.cpp \
    сonnection.cpp
RESOURCES += resources.qrc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    control_panel.h \
    global_window.h \
    сonnection.h

