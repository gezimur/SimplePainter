QT       += opengl widgets

CONFIG += c++17

LIBS += -lGL -lGLEW -lglut -lglfw

CONFIG +=   link_pkgconfig
DEFINES+=__STDC_CONSTANT_MACROS
PKGCONFIG+= \
            opencv-4.6

SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/MainWidget.cpp \
    src/DrawingInstruction.cpp \
    src/DrawingTool.cpp \
    src/MainToolsWidget.cpp \
    src/PaintEventFilter.cpp \
    src/WorkspaceLayer.cpp \
    src/WorkspaceLayerProcessor.cpp \
    src/WorkspaceWidget.cpp

HEADERS += \
    $$PWD/src/MainWidget.h \
    src/DrawingInstruction.h \
    src/DrawingTool.h \
    src/MainToolsWidget.h \
    src/PaintEventFilter.h \
    src/WorkspaceLayer.h \
    src/WorkspaceLayerProcessor.h \
    src/WorkspaceWidget.h
