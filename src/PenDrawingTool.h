#pragma once

#include "DrawingTool.h"
#include "PenDrawingInstruction.h"

class PenDrawingTool: public DrawingTool
{
public:
    void startPainting(const QPoint& crPoint) final;
    void paint(const QPoint& crPoint) final;
    std::shared_ptr<DrawingInstruction> finishPainting(const QPoint& crPoint) final;

    std::shared_ptr<DrawingInstruction> getDrawingInstruction() const final;

private:
    QPoint m_PrevPoint;
    std::shared_ptr<PenDrawingInstruction> m_spLine;
};
