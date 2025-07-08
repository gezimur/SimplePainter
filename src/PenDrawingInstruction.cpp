#include "PenDrawingInstruction.h"

#include <iostream>

#include "make_gl_program.h"

PenDrawingInstruction::PenDrawingInstruction()
    : DrawingInstruction{{}, make_gl_program_for_pen()}
{

}

void PenDrawingInstruction::addPoint(const QPointF& crPoint)
{
    std::vector<float> vPointData = {crPoint.x(), crPoint.y()};

    m_vPoints.insert(m_vPoints.end(), vPointData.begin(), vPointData.end());

    m_GLVertexBuffer.bind();

    if (m_GLVertexBuffer.size() < sizeof(float) * m_vPoints.capacity())
    {
        m_GLVertexBuffer.allocate(m_vPoints.data(), sizeof(float) * m_vPoints.capacity());
    }
    else
    {
        auto iOffset = m_vPoints.size() - vPointData.size();
        m_GLVertexBuffer.write(sizeof(float) * iOffset, vPointData.data(), sizeof(float) * vPointData.size());
    }

    m_GLVertexBuffer.release();
}

void PenDrawingInstruction::shrinkToFit()
{
    auto iPrevCapacity = m_vPoints.capacity();
    m_vPoints.shrink_to_fit();
    if (iPrevCapacity == m_vPoints.capacity())
        return ;

    m_GLVertexBuffer.bind();
    m_GLVertexBuffer.allocate(m_vPoints.data(), sizeof(float) * m_vPoints.size());

    m_GLVertexBuffer.release();
}

void PenDrawingInstruction::excecuteImpl()
{
    if (m_vPoints.size() < 4)
        return ;

    glDrawArrays(GL_LINE_STRIP, 0, m_vPoints.size() / 2);
}
