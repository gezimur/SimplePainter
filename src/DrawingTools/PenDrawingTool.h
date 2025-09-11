#pragma once

#include "DrawingTool.h"
#include "PenDrawingInstruction.h"

class PenDrawingTool: public DrawingTool
{
public:
    void startPainting(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers) final;
    void paint(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers) final;
    std::shared_ptr<DrawingInstruction> finishPainting(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers) final;

    std::shared_ptr<DrawingInstruction> getDrawingInstruction() const final;

private:
    QPoint m_PrevPoint;
    std::shared_ptr<PenDrawingInstruction> m_spLine;
};
