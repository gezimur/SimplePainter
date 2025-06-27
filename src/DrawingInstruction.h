#pragma once

#include <memory>

#include <QColor>
#include <QPoint>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

///< @todo straight line, square, elipse, fill, arbitray line
class DrawingInstruction
{
    enum drawing_instruction
    {
        none = 0,
        pen,
        line,
        square,
        elipse,
        fill
    };

public:
    explicit DrawingInstruction(std::vector<QPointF> vVertex, std::unique_ptr<QOpenGLShaderProgram> upGLProgram);

    void excecute(const QMatrix4x4& crMVP);

    void setColor(const QColor& crColor);
    void setSize(int iSize);

protected:
    virtual void bind(const QMatrix4x4& crMVP);
    virtual void release();

    virtual void excecuteImpl() = 0;

    QColor m_Color;
    int m_iSize = 15;

    QOpenGLBuffer m_GLVertexBuffer;

    std::unique_ptr<QOpenGLShaderProgram> m_upGLProgram;

    int m_iVertexLocation;
    int m_iColorLocation;
    int m_iMVPLocation;
};

