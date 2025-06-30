#include "WorkspacePainter.h"

WorkspacePainter::WorkspacePainter(const QSize& crSize)
    : m_Size{crSize}
{

}

void WorkspacePainter::setTool(const std::shared_ptr<DrawingTool>& spTool)
{
    m_spTool = spTool;
}

void WorkspacePainter::setSize(const QSize& crSize)
{
    m_Size = crSize;
}

void WorkspacePainter::drawCurrent(const QMatrix4x4& crMVP)
{
    if (!m_spTool)
        return ;

    auto spDrawing = m_spTool->getDrawingInstruction();

    if (spDrawing)
        spDrawing->excecute(crMVP);
}

void WorkspacePainter::onStartPaint(const QPoint& crPoint)
{
    if (!m_spTool)
        return ;

    m_spTool->startPainting(makeInversedPoint(crPoint));
}

void WorkspacePainter::onPaint(const QPoint& crPoint)
{
    if (!m_spTool)
        return ;

    m_spTool->paint(makeInversedPoint(crPoint));
}

void WorkspacePainter::onFinishPaint(const QPoint& crPoint)
{
    if (!m_spTool)
        return ;

    auto spResult = m_spTool->finishPainting(makeInversedPoint(crPoint));
    emit paintFinished(spResult);
}

QPoint WorkspacePainter::makeInversedPoint(const QPoint& crPoint) const
{
    return QPoint{crPoint.x(), m_Size.height() - crPoint.y()};
}
