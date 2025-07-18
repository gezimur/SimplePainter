#include "PaintEventFilter.h"

#include <QEvent>
#include <QMouseEvent>


bool PaintEventFilter::eventFilter(QObject* pWatched, QEvent* pEvent)
{
    switch (pEvent->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease:
        return procMouseEvents(pWatched, static_cast<QMouseEvent*>(pEvent));
    default:
        return QObject::eventFilter(pWatched, pEvent);
    }
}

bool PaintEventFilter::procMouseEvents(QObject* pWatched, QMouseEvent* pEvent)
{
    if ( !(pEvent->buttons() && Qt::LeftButton || pEvent->button() == Qt::LeftButton) )
        return false;

    switch (pEvent->type()) {
    case QEvent::MouseButtonPress:
        emit press(pEvent->pos());
        return true;
    case QEvent::MouseMove:
        emit move(pEvent->pos());
        return true;
    case QEvent::MouseButtonRelease:
        emit release(pEvent->pos());
        return true;
    default:
        return QObject::eventFilter(pWatched, pEvent);
    }
}
