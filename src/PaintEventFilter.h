#pragma once

#include <QObject>

#include "DrawingTool.h"

class PaintEventFilter: public QObject
{
public:
    void setTool(const std::shared_ptr<DrawingTool>& spTool);
    const std::shared_ptr<DrawingInstruction>& getCurrentInstruction() const noexcept;

signals:
    void paintStarted();
    void paintFinished();

    void zoomRequested(double);

private:
    bool eventFilter(QObject* pWatched, QEvent* pEvent) final;

    std::shared_ptr<DrawingTool> m_spTool;
    std::shared_ptr<DrawingInstruction> m_spInstruction;
};

