#include "PaintEventFilter.h"

#include <QEvent>
#include <QMouseEvent>

void PaintEventFilter::setTool(const std::shared_ptr<DrawingTool>& spTool)
{
    m_spTool = spTool;
}

void PaintEventFilter::setSize(const QSize& crSize)
{
    m_Size = crSize;
}

std::shared_ptr<DrawingInstruction> PaintEventFilter::getCurrentInstruction()
{
    return m_spTool->getDrawingInstruction();
}

bool PaintEventFilter::eventFilter(QObject* pWatched, QEvent* pEvent)
{
    if (!m_spTool)
        return QObject::eventFilter(pWatched, pEvent);

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

    auto Point = QPoint{pEvent->pos().x(), m_Size.height() - pEvent->pos().y()};

    switch (pEvent->type()) {
    case QEvent::MouseButtonPress:
        return startPainting(Point);
    case QEvent::MouseMove:
        return paint(Point);
    case QEvent::MouseButtonRelease:
        return finishPainting(Point);
    default:
        return QObject::eventFilter(pWatched, pEvent);
    }
}

bool PaintEventFilter::startPainting(const QPoint& crPoint)
{
    assert(m_spTool);
    m_spTool->startPainting(crPoint);

    emit paintStarted();

    return true;
}

bool PaintEventFilter::paint(const QPoint& crPoint)
{
    assert(m_spTool);
    m_spTool->paint(crPoint);

    return true;
}

bool PaintEventFilter::finishPainting(const QPoint& crPoint)
{
    assert(m_spTool);
    emit paintFinished(m_spTool->finishPainting(crPoint));

    return true;
}
