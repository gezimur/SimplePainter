#include "DrawingInstruction.h"

#include <iostream>

#include "make_gl_program.h"

int get_vertex_coords_cnt()
{
    return 2;
}

int get_vertex_coord_size()
{
    return get_vertex_coords_cnt() * sizeof(float);
}

QOpenGLBuffer make_vertex_buffer(std::vector<QPointF> vVertex)
{
    std::vector<float> vData;
    vData.reserve(vVertex.size() * 2);

    for (const auto& crPoint : vVertex)
    {
        vData.push_back(crPoint.x());
        vData.push_back(crPoint.y());
    }

    QOpenGLBuffer Buffer;

    Buffer.create();
    Buffer.bind();

    Buffer.allocate(vData.data(), vData.size() * sizeof(float));

    Buffer.release();

    return Buffer;
}

DrawingInstruction::DrawingInstruction(std::vector<QPointF> vVertex, std::unique_ptr<QOpenGLShaderProgram> upGLProgram)
    : m_GLVertexBuffer{make_vertex_buffer(std::move(vVertex))},
      m_upGLProgram{std::move(upGLProgram)},
      m_iVertexLocation{m_upGLProgram->attributeLocation(get_vertex_var_name())},
      m_iColorLocation{m_upGLProgram->uniformLocation(get_color_var_name())},
      m_iMVPLocation{m_upGLProgram->uniformLocation(get_mvp_var_name())}
{

}

void DrawingInstruction::excecute(const QMatrix4x4& crMVP)
{
    bind(crMVP);

    excecuteImpl();

    release();
}

void DrawingInstruction::setColor(const QColor& crColor)
{
    m_Color = crColor;
}

void DrawingInstruction::setSize(int iSize)
{
    m_iSize = iSize;
}

void DrawingInstruction::bind(const QMatrix4x4& crMVP)
{
    m_upGLProgram->bind();

    m_upGLProgram->setUniformValue(m_iColorLocation, m_Color);
    m_upGLProgram->setUniformValue(m_iMVPLocation, crMVP);

    m_upGLProgram->enableAttributeArray(m_iVertexLocation);

    m_GLVertexBuffer.bind();
    m_upGLProgram->setAttributeBuffer(m_iVertexLocation, GL_FLOAT, 0, get_vertex_coords_cnt());
    m_GLVertexBuffer.release();

    glLineWidth(m_iSize);
}

void DrawingInstruction::release()
{
    m_upGLProgram->disableAttributeArray(m_iVertexLocation);
    m_upGLProgram->release();

}
