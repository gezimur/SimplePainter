#pragma once

#include <QSize>
#include <QPoint>
#include <QMatrix4x4>

class WorkspaceScene
{
public:
    explicit WorkspaceScene(const QSize& crSize);

    void resize(const QSize& crSize);
    void translate(const QPoint& crShift);
    void scale(const QPointF& crPointOnFrame, double dScale);

    QMatrix4x4 getMVP() const;
    QMatrix4x4 getBaseMVP() const;

    QPointF cvtToFrame(const QPointF& crPointOnWindow) const;

private:
    float getScale() const;

    QSize m_Size;

    QMatrix4x4 m_Model;
    QMatrix4x4 m_View;
    QMatrix4x4 m_Projection;

    float m_fBaseProjectionVal;
};

