#include "ImageDrawingInstruction.h"

#include <iostream>
#include <QImage>

#include "make_gl_program.h"
#include "simple_painter_aux.h"

ImageDrawingInstruction::ImageDrawingInstruction(const QRect& crRect)
    : DrawingInstruction{make_image_points(crRect), make_gl_program_for_image()},
      m_ImageVertexBuffer{make_vertex_buffer(make_image_points(QRectF{0.0, 0.0, 1.0, 1.0}))},
      m_FrameBuffer{crRect.size()},
      m_iImageVertexLocation{m_upGLProgram->attributeLocation(get_input_image_vertex_var_name())},
      m_iImageSamplerLocation{m_upGLProgram->attributeLocation(get_image_sampler_name())}
{

}

void ImageDrawingInstruction::bindFrameBuffer()
{
    m_FrameBuffer.bind();
}

void ImageDrawingInstruction::releaseFrameBuffer()
{
    m_FrameBuffer.release();
}

void ImageDrawingInstruction::bind(const QMatrix4x4& crMVP)
{
    DrawingInstruction::bind(crMVP);

    m_upGLProgram->enableAttributeArray(m_iImageVertexLocation);

    m_ImageVertexBuffer.bind();
    m_upGLProgram->setAttributeBuffer(m_iImageVertexLocation, GL_FLOAT, 0, get_vertex_coords_cnt());
    m_ImageVertexBuffer.release();

    m_upGLProgram->setUniformValue(m_iImageSamplerLocation, 0);
    glBindTexture(GL_TEXTURE_2D, m_FrameBuffer.texture());
}

void ImageDrawingInstruction::release()
{
    m_upGLProgram->disableAttributeArray(m_iImageVertexLocation);

    DrawingInstruction::release();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void ImageDrawingInstruction::excecuteImpl()
{
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(6));
}
