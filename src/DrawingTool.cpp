#include "DrawingTool.h"

void DrawingTool::setSize(int iSize)
{
    m_iSize = iSize;
}

void DrawingTool::setColor(const QColor& crColor)
{
    m_Color = crColor;
}

void DrawingTool::draw(const QMatrix4x4& crMVP) const
{
    auto spInstruction = getDrawingInstruction();
    if (spInstruction)
        spInstruction->excecute(crMVP);
}
