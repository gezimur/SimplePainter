#include "LineDrawingTool.h"

void LineDrawingTool::startPainting(const QPoint& crPoint)
{
    m_spLine = std::make_shared<LineDrawingInstruction>(crPoint, crPoint);
    m_spLine->setColor(m_Color);
    m_spLine->setSize(m_iSize);
}

void LineDrawingTool::paint(const QPoint& crPoint)
{
    if (m_spLine)
        m_spLine->changeSecondPoint(crPoint);
}

std::shared_ptr<DrawingInstruction> LineDrawingTool::finishPainting(const QPoint& crPoint)
{
    if (m_spLine)
        m_spLine->changeSecondPoint(crPoint);

    auto spLine = m_spLine;
    m_spLine.reset();
    return spLine;
}

std::shared_ptr<DrawingInstruction> LineDrawingTool::getDrawingInstruction() const
{
    return m_spLine;
}
