#include "LayerListItemWidget.h"

#include <QVBoxLayout>
#include <QMouseEvent>

LayerListItemWidget::LayerListItemWidget(const std::string& strName)
    : QCheckBox{QString::fromStdString(strName)},
      m_strName{strName},
      m_bSelected{false},
      m_bGrabbed{false}
{
    setAutoFillBackground(true);
    setSelected(m_bSelected);
    setChecked(true);
}

bool LayerListItemWidget::isGrabbed() const
{
    return m_bGrabbed;
}

bool LayerListItemWidget::isSelected() const
{
    return m_bSelected;
}

void LayerListItemWidget::setSelected(bool bSelect)
{
    m_bSelected = bSelect;
    if (m_bSelected)
        setPalette(QPalette(QColor{0,255,255}));
    else
        setPalette(QPalette(QColor{255,255,255}));
}

bool LayerListItemWidget::isActive() const
{
    return isChecked();
}

void LayerListItemWidget::setActive(bool bActive)
{
    setChecked(true);
}

const std::string& LayerListItemWidget::getName() const
{
    return m_strName;
}

void LayerListItemWidget::setName(const std::string& strName)
{
    m_strName = strName;
    setText(QString::fromStdString(m_strName));
}

void LayerListItemWidget::mousePressEvent(QMouseEvent* pEvent)
{
    if (pEvent->button() == Qt::LeftButton) //pEvent->isAccepted()
    {
        setSelected(true);
        m_bGrabbed = true;
        emit selected(m_strName);
    }
    QCheckBox::mousePressEvent(pEvent);
}

void LayerListItemWidget::mouseReleaseEvent(QMouseEvent* pEvent)
{
    if (pEvent->button() == Qt::LeftButton) //pEvent->isAccepted()
        m_bGrabbed = false;

    QCheckBox::mouseReleaseEvent(pEvent);
}
