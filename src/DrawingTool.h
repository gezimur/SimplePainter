#pragma once

#include <memory>

#include <QPoint>
#include <QColor>

#include "DrawingInstruction.h"

class DrawingTool
{
protected:
    enum drawing_tool
    {
        none = 0,
        pen,
        line,
        square,
        elipse,
        fill
    };

    explicit DrawingTool(drawing_tool Type);

public:
    void pressTool(const QPoint& crPoint);
    void moveTool(const QPoint& crPoint);
    void releaseTool(const QPoint& crPoint);

    std::shared_ptr<DrawingInstruction> getDrawingInstruction() const;

private:
    drawing_tool Type;

    QColor m_Color;
    int m_iSize;

    std::vector<QPoint> vPoints;
};

