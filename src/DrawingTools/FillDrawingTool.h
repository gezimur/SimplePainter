#pragma once

#include "DrawingTool.h"
#include "FillDrawingInstruction.h"

class FillDrawingTool: public DrawingTool
{
public:
    void startPainting(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers) final;
    void paint(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers) final;
    std::shared_ptr<DrawingInstruction> finishPainting(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers) final;

    std::shared_ptr<DrawingInstruction> getDrawingInstruction() const final;
};

