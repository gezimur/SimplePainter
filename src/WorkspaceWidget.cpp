#include "WorkspaceWidget.h"

#include "LineDrawingTool.h" ///< @todo remove

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
    : m_Painter{crFrameSize}
{
    createConnections();

    setMinimumSize(crFrameSize);

    installEventFilter(&m_PaintEventFilter);
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
    m_Painter.setTool(spTool);
}

void WorkspaceWidget::onZoom(double dZoom)
{

}

void WorkspaceWidget::onAddInstruction(std::shared_ptr<DrawingInstruction> spInstruction)
{
    if (spInstruction)
        m_LayersProcessor.getActiveLayer()->addInstruction(spInstruction);
}

void WorkspaceWidget::initializeGL()
{
    glEnable(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_LayersProcessor.addLayer("Default");
}

void WorkspaceWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    m_Painter.setSize(QSize{w, h});
}

void WorkspaceWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    auto MVP = make_projection(size()) * make_view() * make_model();

    m_LayersProcessor.drawVisible(MVP);
    m_Painter.drawCurrent(MVP);

    update();
}

void WorkspaceWidget::createConnections()
{
    bool bConnected = true;

    bConnected &= static_cast<bool>(connect(&m_PaintEventFilter, SIGNAL(paintStarted(const QPoint&)), &m_Painter, SLOT(onStartPaint(const QPoint&))));
    bConnected &= static_cast<bool>(connect(&m_PaintEventFilter, SIGNAL(paint(const QPoint&)), &m_Painter, SLOT(onPaint(const QPoint&))));
    bConnected &= static_cast<bool>(connect(&m_PaintEventFilter, SIGNAL(paintFinished(const QPoint&)), &m_Painter, SLOT(onFinishPaint(const QPoint&))));
    bConnected &= static_cast<bool>(connect(&m_Painter, SIGNAL(paintFinished(std::shared_ptr<DrawingInstruction>)), SLOT(onAddInstruction(std::shared_ptr<DrawingInstruction>))));
    bConnected &= static_cast<bool>(connect(&m_PaintEventFilter, SIGNAL(zoomRequested(double)), SLOT(onZoom(double))));

    assert(bConnected);
}
