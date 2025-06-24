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
    $$PWD/src/ColorSettingsWidget.cpp \
    $$PWD/src/DrawingInstruction.cpp \
    $$PWD/src/DrawingTool.cpp \
    $$PWD/src/MainToolsWidget.cpp \
    $$PWD/src/PaintEventFilter.cpp \
    $$PWD/src/SizeSettingsWidget.cpp \
    $$PWD/src/WorkspaceLayer.cpp \
    $$PWD/src/WorkspaceLayerProcessor.cpp \
    $$PWD/src/WorkspaceWidget.cpp

HEADERS += \
    $$PWD/src/MainWidget.h \
    $$PWD/src/ColorSettingsWidget.h \
    $$PWD/src/DrawingInstruction.h \
    $$PWD/src/DrawingTool.h \
    $$PWD/src/MainToolsWidget.h \
    $$PWD/src/PaintEventFilter.h \
    $$PWD/src/SizeSettingsWidget.h \
    $$PWD/src/WorkspaceLayer.h \
    $$PWD/src/WorkspaceLayerProcessor.h \
    $$PWD/src/WorkspaceWidget.h
