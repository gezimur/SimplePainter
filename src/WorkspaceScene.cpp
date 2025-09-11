#include "WorkspaceScene.h"

QMatrix4x4 make_projection(const QSize& crSize)
{
    QMatrix4x4 Result;
    Result.ortho(0.0f,
                 static_cast<float>(crSize.width()),
                 0.0f,
                 static_cast<float>(crSize.height()),
                 0.0f,
                 100.0f);

    return Result;
}

QMatrix4x4 make_view()
{
    QMatrix4x4 Result;
    Result.lookAt(QVector3D{0, 0, 1}, QVector3D{0, 0, 0}, QVector3D{0, 1, 0});
    return Result;
}

QMatrix4x4 make_model()
{
    QMatrix4x4 Result{1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f};
    return Result;
}

WorkspaceScene::WorkspaceScene(const QSize& crSize)
    : m_Size{crSize},
      m_Model{make_model()},
      m_View{make_view()},
      m_Projection{make_projection(crSize)},
      m_fBaseProjectionVal{m_Projection.column(0).x()}
{

}

void WorkspaceScene::resize(const QSize& crSize)
{
    m_Size = crSize;
    m_Projection = make_projection(crSize);
    m_View = make_view();
    m_fBaseProjectionVal = m_Projection.column(0).x();
}

void WorkspaceScene::translate(const QPoint& crShift)
{
    auto fScale = getScale();

    auto fX = m_View.column(3).x() + crShift.x() / fScale;
    auto fY = m_View.column(3).y() + crShift.y() / fScale;
    auto fZ = m_View.column(3).z();
    auto fW = m_View.column(3).w();

    m_View.setColumn(3, QVector4D(fX, fY, fZ, fW));
}

void WorkspaceScene::scale(const QPointF& crPointOnFrame, double dScale)
{
    float fScale = getScale();
    float fMultiply = 1.0 + dScale;
    float fNewScale = fScale * fMultiply;

    if (fNewScale < 1.0)
    {
        resize(m_Size);
    }
    else
    {
        auto PointOnGL = (getMVP() * crPointOnFrame);

        m_Projection.scale(1.0 + dScale);

        auto NewPointOnFrame = (getMVP().inverted() * PointOnGL);
        auto ShiftOnWindow = (NewPointOnFrame - crPointOnFrame) * fNewScale;

        translate(ShiftOnWindow.toPoint());
    }
}

QMatrix4x4 WorkspaceScene::getMVP() const
{
    return m_Projection * m_View * m_Model;
}

QMatrix4x4 WorkspaceScene::getBaseMVP() const
{
    return make_projection(m_Size) * make_view() * make_model();
}

QPointF WorkspaceScene::cvtToFrame(const QPointF& crPointOnWindow) const
{
    float fScale = getScale();
    auto FrameShift = QPointF{m_View.column(3).x(), m_View.column(3).y()};
    return crPointOnWindow / fScale - FrameShift;
}

float WorkspaceScene::getScale() const
{
    return m_Projection.column(0).x() / m_fBaseProjectionVal;
}
