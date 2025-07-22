#pragma once

#include <QWidget>

class WorkspaceWidget;
class MainToolsWidget;
class LayersListWidget;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();

private:
    void initGui();
    void createConnections();

    WorkspaceWidget* m_pWorkspace;
    MainToolsWidget* m_pToolsWidget;
    LayersListWidget* m_pLayersList;
};
