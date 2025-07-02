#include "ColorSettingsWidget.h"

#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>

#include "BasePopupWidget.h"
#include "BaseValueSlider.h"

ColorSettingsWidget::ColorSettingsWidget()
    : m_pPopup{new QPushButton{"Color"}},
      m_pSettingsWidget{makeColorSettingsWidget()}
{
    auto pLayout = new QVBoxLayout{this};
    pLayout->addWidget(m_pPopup);

    bool bConnected = true;
    bConnected &= static_cast<bool>(connect(m_pPopup, SIGNAL(clicked(bool)), SLOT(onPopup())));
    assert(bConnected);
}

const QColor& ColorSettingsWidget::getColor() const noexcept
{
    return m_Color;
}

void ColorSettingsWidget::onPopup()
{
    auto GlobalPoint = mapToGlobal(m_pPopup->geometry().topLeft());
    m_pSettingsWidget->popup(GlobalPoint);
}

void ColorSettingsWidget::onConfirm()
{
    m_pSettingsWidget->hide();
    emit colorSelected(m_Color);
}

void ColorSettingsWidget::setColorComponent(int iValue, color_components Component)
{
    switch (Component)
    {
    case color_components::red:
        m_Color.setRed(iValue);
        break;
    case color_components::green:
        m_Color.setGreen(iValue);
        break;
    case color_components::blue:
        m_Color.setBlue(iValue);
    }
}

QString ColorSettingsWidget::getColorComponentName(color_components Component) const
{
    switch (Component)
    {
    case color_components::red:
        return "Red";
    case color_components::green:
        return "Green";
    case color_components::blue:
        return "Blue";
    default:
    {
        assert("Invalid component passed");
        return "";
    }
    }
}

BasePopupWidget* ColorSettingsWidget::makeColorSettingsWidget()
{
    auto pSettingsWidget = new BasePopupWidget;

    auto pRed = makeColorComponentSlider(color_components::red);
    auto pGreen = makeColorComponentSlider(color_components::green);
    auto pBlue = makeColorComponentSlider(color_components::blue);
    auto pConfirm = new QPushButton{"Confirm"};

    auto pSettingsLayout = new QVBoxLayout{pSettingsWidget};
    pSettingsLayout->addWidget(pRed);
    pSettingsLayout->addWidget(pGreen);
    pSettingsLayout->addWidget(pBlue);
    pSettingsLayout->addWidget(pConfirm);

    bool bConnected = true;
    bConnected &= static_cast<bool>(connect(pConfirm, SIGNAL(clicked(bool)), SLOT(onConfirm())));
    assert(bConnected);

    return pSettingsWidget;
}

BaseValueSlider* ColorSettingsWidget::makeColorComponentSlider(color_components Component)
{
    auto pSlider = new BaseValueSlider(getColorComponentName(Component));
    pSlider->setRange(0, 255);

    bool bConnected = true;
    bConnected &= static_cast<bool>(connect(pSlider, &BaseValueSlider::valueChanged, this, [this, Component](int iValue)
    {
        setColorComponent(iValue, Component);
    }));
    assert(bConnected);

    return pSlider;
}
