#pragma once

#include <QObject>

#include "DrawingTool.h"

class QMouseEvent;

class PaintEventFilter: public QObject
{
    Q_OBJECT

signals:
    void paintStarted(const QPoint& crPoint);
    void paint(const QPoint& crPoint);
    void paintFinished(const QPoint& crPoint);

    void zoomRequested(double);

private:
    bool eventFilter(QObject* pWatched, QEvent* pEvent) final;

    bool procMouseEvents(QObject* pWatched, QMouseEvent* pEvent);
};

