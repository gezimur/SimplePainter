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
        emit paintStarted(pEvent->pos());
        return true;
    case QEvent::MouseMove:
        emit paint(pEvent->pos());
        return true;
    case QEvent::MouseButtonRelease:
        emit paintFinished(pEvent->pos());
        return true;
    default:
        return QObject::eventFilter(pWatched, pEvent);
    }
}
