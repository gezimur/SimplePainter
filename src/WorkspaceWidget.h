#pragma once

#include <QOpenGLWidget>
#include <QSize>

#include "WorkspaceLayerProcessor.h"
#include "PaintEventFilter.h"

class WorkspaceWidget: public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit WorkspaceWidget(const QSize& crFrameSize);

    void addLayer(const std::string& strLayer);
    void removeLayer(const std::string& strLayer);
    void selectLayer(const std::string& strLayer);

    void shuffleLayers(const std::vector<std::pair<std::string, bool>>& vLayers);
    std::vector<std::string> getLayersList() const;

signals:
    void paintStarted();
    void paintFinished();

public slots:
    void onUndo();
    void onRedo();
    void onUpdateTool(const std::shared_ptr<DrawingTool>& spTool);
    void onZoom(double dZoom);

private slots:
    void onProcPress(const QPoint& crPoint);
    void onProcMove(const QPoint& crPoint);
    void onProcRelease(const QPoint& crPoint);

private:
    void initializeGL() final;
    void resizeGL(int w, int h) final;
    void paintGL() final;

    void createConnections();

    QPoint mapToFrame(const QPoint& crPoint) const;

    WorkspaceLayerProcessor m_LayersProcessor;

    std::shared_ptr<DrawingTool> m_spTool;

    PaintEventFilter m_PaintEventFilter;
};

