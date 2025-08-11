#include "WorkspaceWidget.h"

#include "simple_painter_aux.h"

QMatrix4x4 make_projection(const QSize& crSize)
{
    QMatrix4x4 Result;
    Result.ortho(0.0f,
                 static_cast<float>(crSize.width()),
                 0.0f,
                 static_cast<float>(crSize.height()),
                 0.0f,
                 100.0f);

    return Result;
}

QMatrix4x4 make_view()
{
    QMatrix4x4 Result;
    Result.lookAt(QVector3D{0, 0, 1}, QVector3D{0, 0, 0}, QVector3D{0, 1, 0});
    return Result;
}

QMatrix4x4 make_model()
{
    QMatrix4x4 Result{1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f};
    return Result;
}

WorkspaceWidget::WorkspaceWidget(const QSize& crFrameSize)
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

void WorkspaceWidget::onZoom(double dZoom)
{

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
}

void WorkspaceWidget::paintGL()
{
    if (m_LayersProcessor.hasChanges())
    {
        auto BaseMVP = make_projection(size()) * make_view() * make_model();

        m_LayersProcessor.cacheVisible(BaseMVP);
    }

    clear_current_gl();

    auto MVP = make_projection(size()) * make_view() * make_model();

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

    bConnected &= static_cast<bool>(connect(&m_PaintEventFilter, SIGNAL(zoomRequested(double)), SLOT(onZoom(double))));

    assert(bConnected);
}

QPoint WorkspaceWidget::mapToFrame(const QPoint& crPoint) const
{
    return QPoint{crPoint.x(), size().height() - crPoint.y()};
}
