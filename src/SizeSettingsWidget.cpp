#include "SizeSettingsWidget.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>

#include "BasePopupWidget.h"
#include "BaseValueSlider.h"

SizeSettingsWidget::SizeSettingsWidget()
    : m_pPopup{new QPushButton{"Size"}},
      m_pSettingsWidget{makeSizeSettingsWidget()}
{
    auto pLayout = new QVBoxLayout{this};
    pLayout->addWidget(m_pPopup);

    bool bConnected = true;
    bConnected &= static_cast<bool>(connect(m_pPopup, SIGNAL(clicked(bool)), SLOT(onPopup())));
    assert(bConnected);
}

int SizeSettingsWidget::getSize() const noexcept
{
    return m_iSize;
}

void SizeSettingsWidget::onPopup()
{
    auto GlobalPoint = mapToGlobal(m_pPopup->geometry().topLeft());
    m_pSettingsWidget->popup(GlobalPoint);
}

void SizeSettingsWidget::onConfirm()
{
    m_iSize = m_pSizeSlider->getValue();
    emit sizeSelected(m_iSize);
}

BasePopupWidget* SizeSettingsWidget::makeSizeSettingsWidget()
{
    auto pSettingsWidget = new BasePopupWidget;

    m_pSizeSlider = new BaseValueSlider("Size");
    m_pSizeSlider->setRange(1, 10);

    auto pConfirm = new QPushButton{"Confirm"};

    auto pSettingsLayout = new QVBoxLayout{pSettingsWidget};
    pSettingsLayout->addWidget(m_pSizeSlider);
    pSettingsLayout->addWidget(pConfirm);

    bool bConnected = true;
    bConnected &= static_cast<bool>(connect(pConfirm, SIGNAL(clicked(bool)), SLOT(onConfirm())));
    assert(bConnected);

    return pSettingsWidget;
}
