#pragma once

#include <QObject>

#include "DrawingTool.h"

class QMouseEvent;

class PaintEventFilter: public QObject
{
    Q_OBJECT

signals:
    void press(const QPoint& crPoint);
    void move(const QPoint& crPoint);
    void release(const QPoint& crPoint);

    void zoomRequested(double);

private:
    bool eventFilter(QObject* pWatched, QEvent* pEvent) final;

    bool procMouseEvents(QObject* pWatched, QMouseEvent* pEvent);
};

