#pragma once

#include "DrawingInstruction.h"

class LineDrawingInstruction: public DrawingInstruction
{
public:
    explicit LineDrawingInstruction(const QPointF& crFrom, const QPointF& crTo);

    void changeSecondPoint(const QPointF& crPoint);

private:
    void excecuteImpl() final;
};

