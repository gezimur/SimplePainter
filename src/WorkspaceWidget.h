#pragma once

#include <QOpenGLWidget>

#include "WorkspaceLayerProcessor.h"
#include "PaintEventFilter.h"

class WorkspaceWidget: public QOpenGLWidget
{
public:
    WorkspaceWidget();

    void undo();
    void redo();

    void addLayer(const std::string& strLayer);
    void removeLayer(const std::string& strLayer);
    void selectLayer(const std::string& strLayer);

    void shuffleLayers(const std::list<std::string>& lLayers);
    std::list<std::string> getLayersList() const;

private:
    void initializeGL() final;
    void resizeGL(int w, int h) final;
    void paintGL() final;

    WorkspaceLayerProcessor m_LayersProcessor;
    std::shared_ptr<WorkspaceLayer> m_spActiveLayer;

    PaintEventFilter m_PaintEventFilter;
};

