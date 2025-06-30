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
    void setSize(int iSize);
    void setColor(const QColor& crColor);

    virtual void startPainting(const QPoint& crPoint) = 0;
    virtual void paint(const QPoint& crPoint) = 0;
    virtual std::shared_ptr<DrawingInstruction> finishPainting(const QPoint& crPoint) = 0;

    virtual std::shared_ptr<DrawingInstruction> getDrawingInstruction() const = 0;

protected:
    drawing_tool m_Type;

    QColor m_Color;
    int m_iSize;
};

