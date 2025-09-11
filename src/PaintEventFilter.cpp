#include "PaintEventFilter.h"

#include <QEvent>
#include <QMouseEvent>
#include <QWheelEvent>

bool PaintEventFilter::eventFilter(QObject* pWatched, QEvent* pEvent)
{
    switch (pEvent->type()) {
    case QEvent::MouseButtonPress:
        return procMousePress(static_cast<QMouseEvent*>(pEvent));
    case QEvent::MouseMove:
        return procMouseMove(static_cast<QMouseEvent*>(pEvent));
    case QEvent::MouseButtonRelease:
        return procMouseRelease(static_cast<QMouseEvent*>(pEvent));
    case QEvent::Wheel:
        return procWheel(static_cast<QWheelEvent*>(pEvent));
    default:
        return QObject::eventFilter(pWatched, pEvent);
    }
}

bool PaintEventFilter::procMousePress(QMouseEvent* pEvent)
{
    if (pEvent->buttons() & Qt::LeftButton)
        emit press(pEvent->pos());
    else if (pEvent->buttons() & Qt::MiddleButton)
        m_optTranslateFrom = pEvent->pos();
    else
        return false;

    return true;
}

bool PaintEventFilter::procMouseMove(QMouseEvent* pEvent)
{
    if (pEvent->buttons() & Qt::LeftButton)
        emit move(pEvent->pos());
    else if (m_optTranslateFrom.has_value() && pEvent->buttons() & Qt::MiddleButton)
    {
        emit translate(pEvent->pos() - m_optTranslateFrom.value());
        m_optTranslateFrom = pEvent->pos();
    }
    else
        return false;

    return true;
}

bool PaintEventFilter::procMouseRelease(QMouseEvent* pEvent)
{
    if (pEvent->button() & Qt::LeftButton)
        emit release(pEvent->pos());
    else if (pEvent->button() & Qt::MiddleButton)
        m_optTranslateFrom.reset();
    else
        return false;

    return true;
}

bool PaintEventFilter::procWheel(QWheelEvent* pEvent)
{
    emit zoomRequested(pEvent->delta() / 1000.0, pEvent->pos());
    return true;
}
