#pragma once

#include <QObject>

#include "DrawingTool.h"

class QMouseEvent;
class QWheelEvent;

class PaintEventFilter: public QObject
{
    Q_OBJECT

signals:
    void press(const QPoint& crPoint);
    void move(const QPoint& crPoint);
    void release(const QPoint& crPoint);

    void translate(const QPoint& crShift);

    void zoomRequested(double, const QPoint&);

private:
    bool eventFilter(QObject* pWatched, QEvent* pEvent) final;

    bool procMousePress(QMouseEvent* pEvent);
    bool procMouseMove(QMouseEvent* pEvent);
    bool procMouseRelease(QMouseEvent* pEvent);
    bool procWheel(QWheelEvent* pEvent);

    std::optional<QPoint> m_optTranslateFrom;
};

