#pragma once

#include "DrawingInstruction.h"

class PenDrawingInstruction: public DrawingInstruction
{
public:
    PenDrawingInstruction();

    void addPoint(const QPointF& crPoint);
    void shrinkToFit();

private:
    void excecuteImpl() final;

    std::vector<float> m_vPoints;
};
