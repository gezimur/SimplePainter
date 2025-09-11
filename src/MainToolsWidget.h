#pragma once

#include <QWidget>

#include "DrawingTools/DrawingTool.h"

class ColorSettingsWidget;
class SizeSettingsWidget;
class QComboBox;
class QPushButton;

class MainToolsWidget: public QWidget
{
    Q_OBJECT

public:
    MainToolsWidget();

    const std::shared_ptr<DrawingTool>& getTool() const;

signals:
    void toolChanged(std::shared_ptr<DrawingTool> spTool);

    void undo();
    void redo();

    void save();
    void open();

public slots:
    void onDisable();
    void onEnable();

private slots:
    void onSwitchTool(int iTool);
    void onChangeColor(const QColor& crColor);
    void onChangeSize(int iSize);

    void onSave();
    void onOpen();

private:
    void initGui();
    void createConnections();

    std::shared_ptr<DrawingTool> m_spTool;

    ColorSettingsWidget* m_pColorSettings;
    SizeSettingsWidget* m_pSizeSettings;
    QComboBox* m_pToolsComboBox;

    QPushButton* m_pUndo;
    QPushButton* m_pRedo;

    QPushButton* m_pSave;
    QPushButton* m_pOpen;
};

