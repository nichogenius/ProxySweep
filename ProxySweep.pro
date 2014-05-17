TEMPLATE = app
CONFIG += qt thread debug
QT+= widgets

SOURCES += \
    board.cpp \
    interface.cpp \
    main.cpp \
    gamestart.cpp \
    main.cpp \
    video.cpp

HEADERS += \
    board.h \
    interface.h \
    gamestart.h

LIBS += -lSDL2

OTHER_FILES += \
    ProxySweep.pro.user

FORMS += \
    gamestart.ui
