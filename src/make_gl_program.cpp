#include "make_gl_program.h"

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

QString get_vertex_var_name()
{
    return "VertexPosition";
}

QString get_color_var_name()
{
    return "VertexColor";
}

QString get_mvp_var_name()
{
    return "MVP";
}

QString get_pixel_color_name()
{
    return "PixelColor";
}

std::unique_ptr<QOpenGLShaderProgram> make_gl_program_for_line()
{
    auto pVertexShader = new QOpenGLShader{QOpenGLShader::Vertex};
    pVertexShader->compileSourceCode(QString(
                                         "#version 330 core\n"

                                         "layout(location = 0) in vec2 %1;\n"
                                         "uniform vec4 %2;\n"
                                         "uniform mat4 %3;\n"

                                         "out vec4 %4;\n"

                                         "void main()\n"
                                         "{\n"
                                         "PixelColor = %2;\n"
                                         "gl_Position = %3 * vec4(%1, 0.0, 1.0);\n"
                                         "}").arg(get_vertex_var_name(),
                                                  get_color_var_name(),
                                                  get_mvp_var_name(),
                                                  get_pixel_color_name()));


    auto pFragmentShader = new QOpenGLShader{QOpenGLShader::Fragment};
    pFragmentShader->compileSourceCode(QString(
                                         "#version 330 core\n"

                                         "in vec4 %1;\n"
                                         "out vec4 color;\n"

                                         "void main()\n"
                                         "{\n"
                                             "color = PixelColor;\n"
                                         "}").arg(get_pixel_color_name()));


    auto upProgram = std::make_unique<QOpenGLShaderProgram>();
    upProgram->addShader(pVertexShader);
    upProgram->addShader(pFragmentShader);
    upProgram->link();

    return upProgram;
}
