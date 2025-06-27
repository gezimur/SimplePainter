#include "MainWidget.h"

#include <QVBoxLayout>

#include "WorkspaceWidget.h"
#include "MainToolsWidget.h"

MainWidget::MainWidget()
    : m_pWorkspace{new WorkspaceWidget{QSize{400, 400}}},
      m_pToolsWidget{new MainToolsWidget}
{
    initGui();
    createConnections();
}

void MainWidget::initGui()
{
    auto pLayout = new QVBoxLayout{this};
    pLayout->addWidget(m_pWorkspace, 100);
    pLayout->addWidget(m_pToolsWidget);
}

void MainWidget::createConnections()
{
    bool bConnected = true;

    bConnected &= static_cast<bool>(connect(m_pToolsWidget, SIGNAL(undo()), m_pWorkspace, SLOT(onUndo())));
    bConnected &= static_cast<bool>(connect(m_pToolsWidget, SIGNAL(redo()), m_pWorkspace, SLOT(onRedo())));
    bConnected &= static_cast<bool>(connect(m_pToolsWidget, SIGNAL(toolChanged(std::shared_ptr<DrawingTool>)), m_pWorkspace, SLOT(onUpdateTool(std::shared_ptr<DrawingTool>))));
//    void save();
//    void open();

    bConnected &= static_cast<bool>(connect(m_pWorkspace, SIGNAL(paintStarted()), m_pToolsWidget, SLOT(hide())));
    bConnected &= static_cast<bool>(connect(m_pWorkspace, SIGNAL(paintFinished()), m_pToolsWidget, SLOT(show())));

    assert(bConnected);
}
