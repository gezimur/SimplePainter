#include "FillDrawingInstruction.h"

#include "make_gl_program.h"

FillDrawingInstruction::FillDrawingInstruction(std::size_t sPointsCnt, std::vector<QPointF> vPoints)
    : DrawingInstruction{std::move(vPoints), make_gl_program_for_fill()},
      m_sPointsCnt{sPointsCnt}
{

}

FillDrawingInstruction::FillDrawingInstruction(std::vector<QPointF> vPoints)
    : FillDrawingInstruction{vPoints.size(), std::move(vPoints)}
{

}

void FillDrawingInstruction::excecuteImpl()
{
    glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(m_sPointsCnt));
}
