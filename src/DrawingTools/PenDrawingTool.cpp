#include "PenDrawingTool.h"

void PenDrawingTool::startPainting(const QPoint& crPoint, WorkspaceLayerProcessor& /*rLayers*/)
{
    m_spLine = std::make_shared<PenDrawingInstruction>();
    m_spLine->setColor(m_Color);
    m_spLine->setSize(m_iSize);
    m_PrevPoint = crPoint;
}

void PenDrawingTool::paint(const QPoint& crPoint, WorkspaceLayerProcessor& /*rLayers*/)
{
    if (crPoint == m_PrevPoint)
        return ;

    if (m_spLine)
        m_spLine->addPoint(crPoint);

    m_PrevPoint = crPoint;
}

std::shared_ptr<DrawingInstruction> PenDrawingTool::finishPainting(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers)
{
    paint(crPoint, rLayers);
    m_spLine->shrinkToFit();

    m_PrevPoint = QPoint{};
    auto spLine = m_spLine;
    m_spLine.reset();
    return spLine;
}

std::shared_ptr<DrawingInstruction> PenDrawingTool::getDrawingInstruction() const
{
    return m_spLine;
}
