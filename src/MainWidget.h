#pragma once

#include <QWidget>

class WorkspaceWidget;
class MainToolsWidget;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();

private:
    WorkspaceWidget* m_pWorkspace;
    MainToolsWidget* m_pToolsWidget;
};
