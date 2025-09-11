QT       += opengl widgets

CONFIG += c++17

LIBS += -lGL

INCLUDEPATH += src

SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/MainWidget.cpp \
    $$PWD/src/ColorSettingsWidget.cpp \
    $$PWD/src/DrawingTools/DrawingInstruction.cpp \
    $$PWD/src/DrawingTools/DrawingTool.cpp \
    $$PWD/src/DrawingTools/LineDrawingInstruction.cpp \
    $$PWD/src/DrawingTools/LineDrawingTool.cpp \
    $$PWD/src/DrawingTools/PenDrawingInstruction.cpp \
    $$PWD/src/DrawingTools/PenDrawingTool.cpp \
    $$PWD/src/DrawingTools/ImageDrawingInstruction.cpp \
    $$PWD/src/DrawingTools/FillDrawingInstruction.cpp \
    $$PWD/src/DrawingTools/FillDrawingTool.cpp \
    $$PWD/src/DrawingTools/drawing_tools.cpp \
    $$PWD/src/DrawingTools/make_gl_program.cpp \
    $$PWD/src/DrawingTools/simple_painter_aux.cpp \
    $$PWD/src/MainToolsWidget.cpp \
    $$PWD/src/PaintEventFilter.cpp \
    $$PWD/src/SizeSettingsWidget.cpp \
    $$PWD/src/WorkspaceLayer.cpp \
    $$PWD/src/WorkspaceLayerProcessor.cpp \
    $$PWD/src/WorkspaceWidget.cpp \
    $$PWD/src/BasePopupWidget.cpp \
    $$PWD/src/BaseValueSlider.cpp \
    $$PWD/src/LayerListItemWidget.cpp \
    $$PWD/src/LayersListWidget.cpp \
    $$PWD/src/WorkspaceScene.cpp

HEADERS += \
    $$PWD/src/MainWidget.h \
    $$PWD/src/ColorSettingsWidget.h \
    $$PWD/src/DrawingTools/DrawingInstruction.h \
    $$PWD/src/DrawingTools/DrawingTool.h \
    $$PWD/src/DrawingTools/LineDrawingInstruction.h \
    $$PWD/src/DrawingTools/LineDrawingTool.h \
    $$PWD/src/DrawingTools/PenDrawingInstruction.h \
    $$PWD/src/DrawingTools/PenDrawingTool.h \
    $$PWD/src/DrawingTools/ImageDrawingInstruction.h \
    $$PWD/src/DrawingTools/FillDrawingInstruction.h \
    $$PWD/src/DrawingTools/FillDrawingTool.h \
    $$PWD/src/DrawingTools/drawing_tools.h \
    $$PWD/src/DrawingTools/make_gl_program.h \
    $$PWD/src/DrawingTools/simple_painter_aux.h \
    $$PWD/src/MainToolsWidget.h \
    $$PWD/src/PaintEventFilter.h \
    $$PWD/src/SizeSettingsWidget.h \
    $$PWD/src/WorkspaceLayer.h \
    $$PWD/src/WorkspaceLayerProcessor.h \
    $$PWD/src/WorkspaceWidget.h \
    $$PWD/src/BasePopupWidget.h \
    $$PWD/src/BaseValueSlider.h \
    $$PWD/src/LayerListItemWidget.h \
    $$PWD/src/LayersListWidget.h \
    $$PWD/src/WorkspaceScene.h
