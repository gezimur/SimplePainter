#include "DrawingTool.h"

DrawingTool::DrawingTool(drawing_tool Type)
    : m_Type{Type},
      m_Color{QColor{0,0,0,0}},
      m_iSize{1}
{

}

void DrawingTool::setSize(int iSize)
{
    m_iSize = iSize;
}

void DrawingTool::setColor(const QColor& crColor)
{
    m_Color = crColor;
}
