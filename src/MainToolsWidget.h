#pragma once

#include <QWidget>

#include "DrawingTool.h"

class ColorSettingsWidget;
class SizeSettingsWidget;
class QComboBox;
class QPushButton;

class MainToolsWidget: public QWidget
{
    Q_OBJECT

public:
    MainToolsWidget();

signals:
    void toolChanged(std::shared_ptr<DrawingTool> spTool);

    void undo();
    void redo();

    void save();
    void open();

private slots:
    void onChangeDrawingTool();

    void onSave();
    void onOpen();

private:
    void initGui();
    void createConnections();

    ColorSettingsWidget* m_pColorSettings;
    SizeSettingsWidget* m_pSizeSettings;
    QComboBox* m_pToolsComboBox;

    QPushButton* m_pUndo;
    QPushButton* m_pRedo;

    QPushButton* m_pSave;
    QPushButton* m_pOpen;
};

