#include "LineDrawingInstruction.h"

#include "make_gl_program.h"

LineDrawingInstruction::LineDrawingInstruction(const QPointF& crFrom, const QPointF& crTo)
    : DrawingInstruction{std::vector<QPointF>{crFrom, crTo}, make_gl_program_for_line()}
{
    
}

void LineDrawingInstruction::changeSecondPoint(const QPointF& crPoint)
{
    std::vector<float> vData = {crPoint.x(), crPoint.y()};

    QOpenGLBuffer Buffer;

    Buffer.create();
    m_GLVertexBuffer.bind();

    m_GLVertexBuffer.write(sizeof(float) * 2, vData.data(), sizeof(float) * 2);

    m_GLVertexBuffer.release();
}

void LineDrawingInstruction::excecuteImpl()
{
    glDrawArrays(GL_LINES, 0, 2);
}
