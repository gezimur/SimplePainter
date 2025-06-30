#pragma once

#include <QObject>

#include "DrawingTool.h"

class WorkspacePainter: public QObject
{
    Q_OBJECT

public:
    explicit WorkspacePainter(const QSize& crSize);

    void setTool(const std::shared_ptr<DrawingTool>& spTool);
    void setSize(const QSize& crSize);

    void drawCurrent(const QMatrix4x4& crMVP);

public slots:
    void onStartPaint(const QPoint& crPoint);
    void onPaint(const QPoint& crPoint);
    void onFinishPaint(const QPoint& crPoint);

signals:
    void paintFinished(std::shared_ptr<DrawingInstruction>);

private:
    QPoint makeInversedPoint(const QPoint& crPoint) const;

    QSize  m_Size;
    std::shared_ptr<DrawingTool> m_spTool;
};

