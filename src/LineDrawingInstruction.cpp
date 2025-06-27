#include "LineDrawingInstruction.h"

#include "make_gl_program.h"

LineDrawingInstruction::LineDrawingInstruction(const QPointF& crFrom, const QPointF& crTo)
    : DrawingInstruction{std::vector<QPointF>{crFrom, crTo}, make_gl_program_for_line()}
{
    
}

void LineDrawingInstruction::excecuteImpl()
{
    glDrawArrays(GL_LINES, 0, 2);
}
