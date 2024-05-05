QT       += core gui
QT +=multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bullet.cpp \
    END.cpp \
    Enemy.cpp \
    Gamecontrol.cpp \
    Gameobject.cpp \
    Gameobjectpool.cpp \
    Introduce.cpp \
    OUT.cpp \
    Player.cpp \
    awula.cpp \
    fuxian.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    Bullet.h \
    END.h \
    Enemy.h \
    Gamecontrol.h \
    Gameobject.h \
    Gameobjectpool.h \
    Introduce.h \
    OUT.h \
    Player.h \
    awula.h \
    fuxian.h \
    widget.h

FORMS += \
    END.ui \
    Introduce.ui \
    OUT.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
