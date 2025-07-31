#include "FillDrawingTool.h"

#include <iostream>
#include <queue>

#include <QGLPixelBuffer>

std::vector<QPoint> fill_color_bfs(QImage&& rvImg, const QColor& crFillColor, const QPoint& crPoint)
{
    auto Img = std::move(rvImg);
    const static std::vector<QPoint> c_vDirections = {QPoint{0, -1}, QPoint{0, 1}, QPoint{-1, 0}, QPoint{1, 0}};

    std::vector<QPoint> vRes{crPoint};
    const auto Color = Img.pixel(crPoint);


    std::queue<QPoint> vCheck;
    vCheck.push(crPoint);

    while (!vCheck.empty())
    {
        auto Point = vCheck.front();
        vCheck.pop();

        for (const auto& crDirection : c_vDirections)
        {
            auto NextCheck = Point + crDirection;
            if (!Img.rect().contains(NextCheck))
                continue;

            if (Color == Img.pixel(NextCheck))
            {
                Img.setPixel(NextCheck, crFillColor.rgb());
                vRes.push_back(NextCheck);
                vCheck.push(NextCheck);
            }
        }

        if (vRes.size() > Img.rect().width() * Img.rect().height())
            return vRes;
    }

    return vRes;
}

void FillDrawingTool::startPainting(const QPoint& /*crPoint*/, WorkspaceLayerProcessor& /*rLayers*/)
{

}

void FillDrawingTool::paint(const QPoint& /*crPoint*/, WorkspaceLayerProcessor& /*rLayers*/)
{

}

std::shared_ptr<DrawingInstruction> FillDrawingTool::finishPainting(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers)
{
    auto Image = rLayers.getCached();
    auto iHeight = Image.height();
    auto vFillPoints = fill_color_bfs(std::move(Image), m_Color, QPoint{crPoint.x(), Image.height() - crPoint.y()});

    std::vector<QPointF> vValidRes;
    vValidRes.reserve(vFillPoints.size());
    std::transform(vFillPoints.begin(), vFillPoints.end(), std::back_inserter(vValidRes), [iHeight](const QPoint& crPoint)
    {
        return QPointF{crPoint.x(), iHeight - crPoint.y()};
    });

    auto spFill = std::make_shared<FillDrawingInstruction>(vValidRes);
    spFill->setColor(m_Color);

    return spFill;
}

std::shared_ptr<DrawingInstruction> FillDrawingTool::getDrawingInstruction() const
{
    return nullptr;
}
