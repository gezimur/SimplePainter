#pragma once

#include <memory>
#include <string>
#include <vector>

class DrawingTool;

enum class drawing_tools
{
    none = 0,
    pen,
    line,
    square,
    elipse,
    fill,
    ///< @todo image

    cnt
};

std::shared_ptr<DrawingTool> make_tool(drawing_tools Type);

std::string to_str(drawing_tools Type);

std::vector<drawing_tools> get_all_drawing_instructions();
