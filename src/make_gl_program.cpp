#include "make_gl_program.h"

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

QString get_vertex_var_name()
{
    return "VertexPosition";
}

QString get_input_image_vertex_var_name()
{
    return "ImageVertexPosition";
}

QString get_image_vertex_var_name()
{
    return "ImageVertexPosition2";
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

QString get_image_sampler_name()
{
    return "ImageSampler";
}

QString get_line_vertex_code()
{
    return QString("#version 330 core\n"

                   "layout(location = 0) in vec2 %1;\n"
                   "uniform vec4 %2;\n"
                   "uniform mat4 %3;\n"
                   "out vec4 %4;\n"

                   "void main()\n"
                   "{\n"
                   "%4 = %2;\n"
                   "gl_Position = %3 * vec4(%1, 0.0, 1.0);\n"
                   "}").arg(get_vertex_var_name(),
                            get_color_var_name(),
                            get_mvp_var_name(),
                            get_pixel_color_name());
}

QString get_line_fragment_code()
{
    return QString("#version 330 core\n"

                   "in vec4 %1;\n"
                   "out vec4 color;\n"

                   "void main()\n"
                   "{\n"
                   "color = %1;\n"
                   "}").arg(get_pixel_color_name());
}

QString get_image_vertex_code()
{
    return QString("#version 330 core\n"

                   "layout(location = 0) in vec2 %1;\n"
                   "layout(location = 1) in vec2 %2;\n"
                   "uniform mat4 %3;\n"
                   "out vec2 %4;\n"

                   "void main()\n"
                   "{\n"
                   "%4 = %2;\n"
                   "gl_Position = %3 * vec4(%1, 0.0, 1.0);\n"
                   "}").arg(
                            get_vertex_var_name(),
                            get_input_image_vertex_var_name(),
                            get_mvp_var_name(),
                            get_image_vertex_var_name());
}

QString get_image_fragment_code()
{
    return QString("#version 330 core\n"

                   "in vec2 %1;\n"
                   "uniform sampler2D %2;\n"

                   "out vec4 color;\n"

                   "void main()\n"
                   "{\n"
                   "color = texture( %2, %1);\n"
                   "}").arg(get_image_vertex_var_name(),
                            get_image_sampler_name());
}

QString get_pen_vertex_code()
{
    return get_line_vertex_code();
}

QString get_pen_fragment_code()
{
    return get_line_fragment_code();
}

std::unique_ptr<QOpenGLShaderProgram> make_gl_program(const QString& qstrVertexCode, const QString& qstrFragmentCode)
{
    auto pVertexShader = new QOpenGLShader{QOpenGLShader::Vertex};
    pVertexShader->compileSourceCode(qstrVertexCode);

    auto pFragmentShader = new QOpenGLShader{QOpenGLShader::Fragment};
    pFragmentShader->compileSourceCode(qstrFragmentCode);

    auto upProgram = std::make_unique<QOpenGLShaderProgram>();
    upProgram->addShader(pVertexShader);
    upProgram->addShader(pFragmentShader);
    upProgram->link();

    return upProgram;
}

std::unique_ptr<QOpenGLShaderProgram> make_gl_program_for_line()
{
    return make_gl_program(get_line_vertex_code(), get_line_fragment_code());
}

std::unique_ptr<QOpenGLShaderProgram> make_gl_program_for_pen()
{
    return make_gl_program(get_pen_vertex_code(), get_pen_fragment_code());
}

std::unique_ptr<QOpenGLShaderProgram> make_gl_program_for_image()
{
    return make_gl_program(get_image_vertex_code(), get_image_fragment_code());
}
