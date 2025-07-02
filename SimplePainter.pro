QT       += opengl widgets

CONFIG += c++17

LIBS += -lGL

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
    $$PWD/src/WorkspaceWidget.cpp \
    $$PWD/src/LineDrawingInstruction.cpp \
    $$PWD/src/make_gl_program.cpp \
    $$PWD/src/LineDrawingTool.cpp \
    $$PWD/src/WorkspacePainter.cpp \
    $$PWD/src/BasePopupWidget.cpp \
    $$PWD/src/BaseValueSlider.cpp

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
    $$PWD/src/WorkspaceWidget.h \
    $$PWD/src/LineDrawingInstruction.h \
    $$PWD/src/make_gl_program.h \
    $$PWD/src/LineDrawingTool.h \
    $$PWD/src/WorkspacePainter.h \
    $$PWD/src/BasePopupWidget.h \
    $$PWD/src/BaseValueSlider.h
