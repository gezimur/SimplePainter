#pragma once

#include "DrawingTool.h"
#include "LineDrawingInstruction.h"

class LineDrawingTool: public DrawingTool
{
public:
    void startPainting(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers) final;
    void paint(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers) final;
    std::shared_ptr<DrawingInstruction> finishPainting(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers) final;

    std::shared_ptr<DrawingInstruction> getDrawingInstruction() const final;

private:
    std::shared_ptr<LineDrawingInstruction> m_spLine;
};

