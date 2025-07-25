#pragma once

#include "DrawingInstruction.h"

class FillDrawingInstruction: public DrawingInstruction
{
    explicit FillDrawingInstruction(std::size_t sPointsCnt, std::vector<QPointF> vPoints);

public:
    explicit FillDrawingInstruction(std::vector<QPointF> vPoints);

private:
    void excecuteImpl() final;

    std::size_t m_sPointsCnt;
};

