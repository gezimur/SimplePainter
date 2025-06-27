#pragma once

#include "DrawingTool.h"
#include "LineDrawingInstruction.h"

class LineDrawingTool: public DrawingTool
{
public:
    LineDrawingTool();

    void startPainting(const QPoint& crPoint) final;
    void paint(const QPoint& crPoint) final;
    std::shared_ptr<DrawingInstruction> finishPainting(const QPoint& crPoint) final;

    std::shared_ptr<DrawingInstruction> getDrawingInstruction() const final;

private:
    std::shared_ptr<LineDrawingInstruction> m_spLine;
};

