#pragma once

#include <QOpenGLFramebufferObject>

#include "DrawingInstruction.h"

class ImageDrawingInstruction : public DrawingInstruction
{
public:
    explicit ImageDrawingInstruction(const QRect& crRect);

    void bindFrameBuffer();
    void releaseFrameBuffer();

private:
    void bind(const QMatrix4x4& crMVP) final;
    void release() final;

    void excecuteImpl() final;

    QOpenGLBuffer m_ImageVertexBuffer;
    QOpenGLFramebufferObject m_FrameBuffer;

    int m_iImageVertexLocation;
    int m_iImageSamplerLocation;
};

