#include "ColorSettingsWidget.h"

#include <QPushButton>
#include <QVBoxLayout>

ColorSettingsWidget::ColorSettingsWidget()
    : m_pSelect{new QPushButton{"Color"}}
{
    auto pLayout = new QVBoxLayout{this};
    pLayout->addWidget(m_pSelect);

    bool bConnected = true;
    bConnected &= static_cast<bool>(connect(m_pSelect, SIGNAL(clicked(bool)), SLOT(onSelectColor())));
    assert(bConnected);
}

void ColorSettingsWidget::onSelectColor()
{
    emit colorSelected(QColor{0,0,0,0});
}
