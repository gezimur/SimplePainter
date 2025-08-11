#include "simple_painter_aux.h"

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


std::vector<QPointF> make_image_points(const QRectF& crRect)
{
    return std::vector<QPointF>{crRect.topLeft(), crRect.topRight(), crRect.bottomRight(),
                                crRect.topLeft(), crRect.bottomRight(), crRect.bottomLeft()};
}

void clear_current_gl()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
