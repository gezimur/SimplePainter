#include "DrawingTool.h"

DrawingTool::DrawingTool(drawing_tool Type)
    : m_Type{Type},
      m_Color{QColor{0,0,0,0}},
      m_iSize{1}
{

}

DrawingTool::DrawingTool()
    : DrawingTool{drawing_tool::none}
{

}

void DrawingTool::pressTool(const QPoint& crPoint)
{

}

void DrawingTool::moveTool(const QPoint& crPoint)
{

}

void DrawingTool::releaseTool(const QPoint& crPoint)
{

}

std::shared_ptr<DrawingInstruction> DrawingTool::getDrawingInstruction() const
{
    return {};
}
