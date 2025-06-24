#include "WorkspaceWidget.h"

WorkspaceWidget::WorkspaceWidget(const QSize& crFrameSize)
    : m_LayersProcessor{crFrameSize}
{
    setMinimumSize(crFrameSize);
}

void WorkspaceWidget::addLayer(const std::string& strLayer)
{
    m_LayersProcessor.addLayer(strLayer);
}

void WorkspaceWidget::removeLayer(const std::string& strLayer)
{
    m_LayersProcessor.removeLayer(strLayer);
}

void WorkspaceWidget::selectLayer(const std::string& strLayer)
{
    m_LayersProcessor.selectLayer(strLayer);
}

void WorkspaceWidget::shuffleLayers(const std::vector<std::pair<std::string, bool>>& vLayers)
{
    m_LayersProcessor.shuffleLayers(vLayers);
}

std::vector<std::string> WorkspaceWidget::getLayersList() const
{
    return m_LayersProcessor.getLayersList();
}

void WorkspaceWidget::onUndo()
{
    assert(m_LayersProcessor.getActiveLayer());
    m_LayersProcessor.getActiveLayer()->undo();
}

void WorkspaceWidget::onRedo()
{
    assert(m_LayersProcessor.getActiveLayer());
    m_LayersProcessor.getActiveLayer()->redo();
}

void WorkspaceWidget::onUpdateTool(const std::shared_ptr<DrawingTool>& spTool)
{
    m_PaintEventFilter.setTool(spTool);
}

void WorkspaceWidget::onZoom(double dZoom)
{

}

void WorkspaceWidget::initializeGL()
{

}

void WorkspaceWidget::resizeGL(int w, int h)
{

}

void WorkspaceWidget::paintGL()
{

}

void WorkspaceWidget::createConnections()
{
    bool bConnected = true;

    bConnected &= static_cast<bool>(connect(&m_PaintEventFilter, SIGNAL(paintStarted()), SIGNAL(paintStarted())));
    bConnected &= static_cast<bool>(connect(&m_PaintEventFilter, SIGNAL(paintFinished()), SIGNAL(paintFinished())));
    bConnected &= static_cast<bool>(connect(&m_PaintEventFilter, SIGNAL(zoomRequested(double)), SLOT(onZoom(double))));

    assert(bConnected);
}
