#include "PaintEventFilter.h"


void PaintEventFilter::setTool(const std::shared_ptr<DrawingTool>& spTool)
{
    m_spTool = spTool;
}

const std::shared_ptr<DrawingInstruction>& PaintEventFilter::getCurrentInstruction() const noexcept
{
    return m_spInstruction;
}

bool PaintEventFilter::eventFilter(QObject* pWatched, QEvent* pEvent)
{
    return QObject::eventFilter(pWatched, pEvent);
}
