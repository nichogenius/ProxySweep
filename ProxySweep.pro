TEMPLATE = app
CONFIG += qt
QT += widgets

SOURCES += \
    board.cpp \
    interface.cpp \
    video.cpp \
    main.cpp \
    gamestart.cpp

HEADERS += \
    board.h \
    interface.h \
    gamestart.h \
    video.h

LIBS += -lSDL2

OTHER_FILES += \
    ProxySweep.pro.user

FORMS += \
    gamestart.ui
