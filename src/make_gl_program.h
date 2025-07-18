#pragma once

#include <memory>

#include <QString>

class QOpenGLShaderProgram;

QString get_vertex_var_name();
QString get_input_image_vertex_var_name();
QString get_color_var_name();
QString get_mvp_var_name();
QString get_image_sampler_name();

std::unique_ptr<QOpenGLShaderProgram> make_gl_program_for_line();
std::unique_ptr<QOpenGLShaderProgram> make_gl_program_for_pen();
std::unique_ptr<QOpenGLShaderProgram> make_gl_program_for_image();
