#pragma once

#include <QObject>

#include "DrawingTool.h"

class PaintEventFilter: public QObject
{
public:
    PaintEventFilter();

    void setTool(const std::shared_ptr<DrawingTool>& spTool);

signals:
    void paintStarted();
    void painting(std::shared_ptr<DrawingInstruction> spInstruction);
    void paintFinished();

private:
    bool eventFilter(QObject* pWatched, QEvent* pEvent) final;

    std::shared_ptr<DrawingTool> m_spTool;
    std::shared_ptr<DrawingInstruction> m_spInstruction;
};

