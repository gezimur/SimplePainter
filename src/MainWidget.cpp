#include "MainWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include "WorkspaceWidget.h"
#include "MainToolsWidget.h"
#include "LayersListWidget.h"

MainWidget::MainWidget()
    : m_pWorkspace{new WorkspaceWidget{QSize{400, 400}}},
      m_pToolsWidget{new MainToolsWidget},
      m_pLayersList{new LayersListWidget}
{
    initGui();
    createConnections();

    m_pWorkspace->onUpdateTool(m_pToolsWidget->getTool());
}

void MainWidget::initGui()
{
    auto pLayersLayout = new QHBoxLayout;
    pLayersLayout->addWidget(m_pLayersList);
    pLayersLayout->addWidget(m_pWorkspace, 100);

    auto pLayout = new QVBoxLayout{this};
    pLayout->addLayout(pLayersLayout, 100);
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

    bConnected &= static_cast<bool>(connect(m_pWorkspace, SIGNAL(paintStarted()), m_pToolsWidget, SLOT(onDisable())));
    bConnected &= static_cast<bool>(connect(m_pWorkspace, SIGNAL(paintFinished()), m_pToolsWidget, SLOT(onEnable())));

    bConnected &= static_cast<bool>(connect(m_pLayersList, SIGNAL(layersShuffled(const std::vector<std::pair<std::string, bool>>&)), m_pWorkspace, SLOT(onShuffleLayers(const std::vector<std::pair<std::string, bool>>&))));
    bConnected &= static_cast<bool>(connect(m_pLayersList, SIGNAL(layerAdded(const std::string&)), m_pWorkspace, SLOT(onAddLayer(const std::string&))));
    bConnected &= static_cast<bool>(connect(m_pLayersList, SIGNAL(layerRemoved(const std::string&)), m_pWorkspace, SLOT(onRemoveLayer(const std::string&))));
    bConnected &= static_cast<bool>(connect(m_pLayersList, SIGNAL(layerSelected(const std::string&)), m_pWorkspace, SLOT(onSelectLayer(const std::string&))));
    bConnected &= static_cast<bool>(connect(m_pLayersList, SIGNAL(layerRenamed(const std::string&, const std::string&)), m_pWorkspace, SLOT(onRenameLayer(const std::string&, const std::string&))));

    assert(bConnected);
}
