#include "SizeSettingsWidget.h"

#include <QPushButton>
#include <QVBoxLayout>

SizeSettingsWidget::SizeSettingsWidget()
    : m_pSelect{new QPushButton{"Size"}}
{
    auto pLayout = new QVBoxLayout{this};
    pLayout->addWidget(m_pSelect);

    bool bConnected = true;
    bConnected &= static_cast<bool>(connect(m_pSelect, SIGNAL(clicked(bool)), SLOT(onSelectSize())));
    assert(bConnected);
}

void SizeSettingsWidget::onSelectSize()
{
    emit sizeSelected(1);
}
