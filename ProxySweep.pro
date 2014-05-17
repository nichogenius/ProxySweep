TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    board.cpp \
    interface.cpp \
    video.cpp \
    main.cpp \
    gamestart.cpp

HEADERS += \
    board.h \
    interface.h \
    gamestart.h

LIBS += -lSDL2

OTHER_FILES += \
    ProxySweep.pro.user

FORMS += \
    gamestart.ui
