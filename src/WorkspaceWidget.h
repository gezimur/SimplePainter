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

private:
    void initializeGL() final;
    void resizeGL(int w, int h) final;
    void paintGL() final;

    void createConnections();

    WorkspaceLayerProcessor m_LayersProcessor;
    std::shared_ptr<WorkspaceLayer> m_spActiveLayer;

    PaintEventFilter m_PaintEventFilter;
};

