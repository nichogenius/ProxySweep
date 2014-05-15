TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    board.cpp \
    interface.cpp \
    main.cpp

HEADERS += \
    board.h \
    interface.h

LIBS += -lSDL2

OTHER_FILES += \
    ProxySweep.pro.user
