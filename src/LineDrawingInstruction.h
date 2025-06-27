#pragma once

#include "DrawingInstruction.h"

class LineDrawingInstruction: public DrawingInstruction
{
public:
    explicit LineDrawingInstruction(const QPointF& crFrom, const QPointF& crTo);

private:
    void excecuteImpl() final;
};

