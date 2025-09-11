#include "WorkspaceWidget.h"

#include "DrawingTools/simple_painter_aux.h"

WorkspaceWidget::WorkspaceWidget(const QSize& crFrameSize)
    : m_Scene{crFrameSize}
{
    createConnections();

    setMinimumSize(crFrameSize);

    installEventFilter(&m_PaintEventFilter);
}

void WorkspaceWidget::onAddLayer(const std::string& strLayer)
{
    m_LayersProcessor.addLayer(strLayer);
}

void WorkspaceWidget::onRemoveLayer(const std::string& strLayer)
{
    m_LayersProcessor.removeLayer(strLayer);
}

void WorkspaceWidget::onSelectLayer(const std::string& strLayer)
{
    m_LayersProcessor.selectLayer(strLayer);
}

void WorkspaceWidget::onRenameLayer(const std::string& strPrev, const std::string& strNew)
{
    m_LayersProcessor.renameLayer(strPrev, strNew);
}

void WorkspaceWidget::onShuffleLayers(const std::vector<std::pair<std::string, bool>>& vLayers)
{
    m_LayersProcessor.shuffleLayers(vLayers);
}

void WorkspaceWidget::onUndo()
{
    m_LayersProcessor.undoActiveLayer();
}

void WorkspaceWidget::onRedo()
{
    m_LayersProcessor.redoActiveLayer();
}

void WorkspaceWidget::onUpdateTool(const std::shared_ptr<DrawingTool>& spTool)
{
    m_spTool = spTool;
}

void WorkspaceWidget::onZoom(double dZoom, const QPoint& crPoint)
{
    m_Scene.scale(mapToFrame(crPoint), dZoom);
}

void WorkspaceWidget::onProcPress(const QPoint& crPoint)
{
    if (m_spTool)
        m_spTool->startPainting(mapToFrame(crPoint), m_LayersProcessor);
}

void WorkspaceWidget::onProcMove(const QPoint& crPoint)
{
    if (m_spTool)
        m_spTool->paint(mapToFrame(crPoint), m_LayersProcessor);
}

void WorkspaceWidget::onProcRelease(const QPoint& crPoint)
{
    if (!m_spTool)
        return ;

    auto spResult = m_spTool->finishPainting(mapToFrame(crPoint), m_LayersProcessor);
    if (spResult)
        m_LayersProcessor.addToActiveLayer(spResult);
}

void WorkspaceWidget::onProcTranslate(const QPoint& crShift)
{
    m_Scene.translate(QPoint{crShift.x(), -crShift.y()});
}

void WorkspaceWidget::initializeGL()
{
    glEnable(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    clear_current_gl();

    m_LayersProcessor.setSheetSize(size());
}

void WorkspaceWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    m_Scene.resize(QSize{w, h});
}

void WorkspaceWidget::paintGL()
{
    if (m_LayersProcessor.hasChanges())
    {
        m_LayersProcessor.cacheVisible(m_Scene.getBaseMVP());
    }

    clear_current_gl();

    auto MVP = m_Scene.getMVP();
    m_LayersProcessor.drawCached(MVP);

    if (m_spTool)
        m_spTool->draw(MVP);

    update();
}

void WorkspaceWidget::createConnections()
{
    bool bConnected = true;

    bConnected &= static_cast<bool>(connect(&m_PaintEventFilter, SIGNAL(press(const QPoint&)), SLOT(onProcPress(const QPoint&))));
    bConnected &= static_cast<bool>(connect(&m_PaintEventFilter, SIGNAL(move(const QPoint&)), SLOT(onProcMove(const QPoint&))));
    bConnected &= static_cast<bool>(connect(&m_PaintEventFilter, SIGNAL(release(const QPoint&)), SLOT(onProcRelease(const QPoint&))));

    bConnected &= static_cast<bool>(connect(&m_PaintEventFilter, SIGNAL(translate(const QPoint&)), SLOT(onProcTranslate(const QPoint&))));

    bConnected &= static_cast<bool>(connect(&m_PaintEventFilter, SIGNAL(zoomRequested(double, const QPoint&)), SLOT(onZoom(double, const QPoint&))));

    assert(bConnected);
}

QPoint WorkspaceWidget::mapToFrame(const QPoint& crPoint) const
{
    return m_Scene.cvtToFrame(QPointF{crPoint.x(), size().height() - crPoint.y()}).toPoint();
}
