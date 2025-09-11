#pragma once

#include <memory>

#include <QPoint>
#include <QColor>

#include "DrawingInstruction.h"
#include "../WorkspaceLayerProcessor.h"

class DrawingTool
{
public:
    void setSize(int iSize);
    void setColor(const QColor& crColor);

    virtual void startPainting(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers) = 0;
    virtual void paint(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers) = 0;
    virtual std::shared_ptr<DrawingInstruction> finishPainting(const QPoint& crPoint, WorkspaceLayerProcessor& rLayers) = 0;

    virtual std::shared_ptr<DrawingInstruction> getDrawingInstruction() const = 0;

    void draw(const QMatrix4x4& crMVP) const;

protected:
    QColor m_Color = QColor{0, 0, 0, 0};
    int m_iSize = 1;
};

