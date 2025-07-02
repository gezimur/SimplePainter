#include "drawing_tools.h"

#include <cassert>

#include "LineDrawingTool.h"

std::shared_ptr<DrawingTool> make_tool(drawing_tools Type)
{
    switch(Type)
    {
    case drawing_tools::pen:
        return std::make_shared<LineDrawingTool>(); ///< @todo
    case drawing_tools::line:
        return std::make_shared<LineDrawingTool>();
    case drawing_tools::square:
        return std::make_shared<LineDrawingTool>(); ///< @todo
    case drawing_tools::elipse:
        return std::make_shared<LineDrawingTool>(); ///< @todo
    case drawing_tools::fill:
        return std::make_shared<LineDrawingTool>(); ///< @todo
    default:
    {
        assert("Invalid tool passed");
        return {};
    }
    };
}

std::string to_str(drawing_tools Type)
{
    switch(Type)
    {
    case drawing_tools::pen:
        return "Pen";
    case drawing_tools::line:
        return "Line";
    case drawing_tools::square:
        return "Square";
    case drawing_tools::elipse:
        return "Elipse";
    case drawing_tools::fill:
        return "Fill";
    default:
    {
        assert("Invalid instruction passed");
        return {};
    }
    };
}

std::vector<drawing_tools> get_all_drawing_instructions()
{
    std::vector<drawing_tools> vInstructions;
    vInstructions.reserve(static_cast<std::size_t>(drawing_tools::cnt));
    for (auto i = 0; i < static_cast<int>(drawing_tools::cnt); ++i)
        vInstructions.push_back(static_cast<drawing_tools>(i));

    return vInstructions;
}

