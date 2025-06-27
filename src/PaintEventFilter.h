#pragma once

#include <QObject>

#include "DrawingTool.h"

class QMouseEvent;

class PaintEventFilter: public QObject
{
    Q_OBJECT

public:
    void setTool(const std::shared_ptr<DrawingTool>& spTool);
    void setSize(const QSize& crSize);

    std::shared_ptr<DrawingInstruction> getCurrentInstruction() ;

signals:
    void paintStarted();
    void paintFinished(std::shared_ptr<DrawingInstruction>);

    void zoomRequested(double);

private:
    bool eventFilter(QObject* pWatched, QEvent* pEvent) final;

    bool procMouseEvents(QObject* pWatched, QMouseEvent* pEvent);

    bool startPainting(const QPoint& crPoint);
    bool paint(const QPoint& crPoint);
    bool finishPainting(const QPoint& crPoint);

    QSize  m_Size;
    std::shared_ptr<DrawingTool> m_spTool;
};

