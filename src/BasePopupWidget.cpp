#include "BasePopupWidget.h"

#include <QResizeEvent>

BasePopupWidget::BasePopupWidget(Qt::Corner Corner)
    : m_bVisible{false},
      m_PopupFrom{Corner}
{
    setWindowFlags(Qt::Popup | Qt::CustomizeWindowHint);
    setWindowModality(Qt::NonModal);
    hide();
}

void BasePopupWidget::popup(const QPoint &crPoint)
{
    m_bVisible = true;
    m_PopupPoint = crPoint;
    move(m_PopupPoint - getCorner());
    show();
}

void BasePopupWidget::resizeEvent(QResizeEvent *pEvent)
{
    if (m_bVisible)
        popup(m_PopupPoint);

    QWidget::resizeEvent(pEvent);
}

void BasePopupWidget::hideEvent(QHideEvent* pEvent)
{
    m_bVisible = false;
    QWidget::hideEvent(pEvent);
}

QPoint BasePopupWidget::getCorner() const
{
    switch (m_PopupFrom) {
    case Qt::TopLeftCorner:
        return rect().topLeft();
    case Qt::TopRightCorner:
        return rect().topRight();
    case Qt::BottomLeftCorner:
        return rect().bottomLeft();
    case Qt::BottomRightCorner:
        return rect().bottomRight();
    default:
    {
        assert("BasePopupWidget::getCorner: Invalid corner specified");
        return QPoint{};
    }
    }
}
