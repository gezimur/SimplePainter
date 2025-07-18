#pragma once

#include <vector>

#include <QPointF>
#include <QRect>
#include <QOpenGLBuffer>

int get_vertex_coords_cnt();

int get_vertex_coord_size();

QOpenGLBuffer make_vertex_buffer(std::vector<QPointF> vVertex);

std::vector<QPointF> make_image_points(const QRectF& crRect);
