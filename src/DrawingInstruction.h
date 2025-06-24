#pragma once

#include <QColor>
#include <QPoint>

///< @todo straight line, square, elipse, fill, arbitray line
class DrawingInstruction
{
    enum drawing_instruction
    {
        none = 0,
        pen,
        line,
        square,
        elipse,
        fill
    };

public:
    DrawingInstruction() = default;

private:
    drawing_instruction m_Type = none;

    QColor m_Color;
    int m_iSize = 1;

    std::vector<QPoint> m_vPoints;
};

