#pragma once

#include <QOpenGLWidget>
#include <QSize>

#include "WorkspaceScene.h"
#include "WorkspaceLayerProcessor.h"
#include "PaintEventFilter.h"

class WorkspaceWidget: public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit WorkspaceWidget(const QSize& crFrameSize);

signals:
    void paintStarted();
    void paintFinished();

public slots:
    void onAddLayer(const std::string& strLayer);
    void onRemoveLayer(const std::string& strLayer);
    void onSelectLayer(const std::string& strLayer);
    void onRenameLayer(const std::string& strPrev, const std::string& strNew);

    void onShuffleLayers(const std::vector<std::pair<std::string, bool>>& vLayers);

    void onUndo();
    void onRedo();
    void onUpdateTool(const std::shared_ptr<DrawingTool>& spTool);
    void onZoom(double dZoom, const QPoint& crPoint);

private slots:
    void onProcPress(const QPoint& crPoint);
    void onProcMove(const QPoint& crPoint);
    void onProcRelease(const QPoint& crPoint);
    void onProcTranslate(const QPoint& crShift);

private:
    void initializeGL() final;
    void resizeGL(int w, int h) final;
    void paintGL() final;

    void createConnections();

    QPoint mapToFrame(const QPoint& crPoint) const;

    WorkspaceLayerProcessor m_LayersProcessor;
    WorkspaceScene m_Scene;

    std::shared_ptr<DrawingTool> m_spTool;

    PaintEventFilter m_PaintEventFilter;
};

