#include "ColorSettingsWidget.h"

#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>

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
    m_pSettingsWidget->move(GlobalPoint -  QPoint{0, m_pSettingsWidget->height()});
    m_pSettingsWidget->show();
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

QWidget* ColorSettingsWidget::makeColorSettingsWidget()
{
    auto pSettingsWidget = new QWidget;

    auto pRed = makeColorComponentSlider(color_components::red);
    auto pGreen = makeColorComponentSlider(color_components::green);
    auto pBlue = makeColorComponentSlider(color_components::blue);
    auto pConfirm = new QPushButton{"Confirm"};

    auto pSettingsLayout = new QVBoxLayout{pSettingsWidget};
    pSettingsLayout->addWidget(pRed);
    pSettingsLayout->addWidget(pGreen);
    pSettingsLayout->addWidget(pBlue);
    pSettingsLayout->addWidget(pConfirm);

    pSettingsWidget->setWindowFlags(Qt::Popup | Qt::CustomizeWindowHint);
    pSettingsWidget->setWindowModality(Qt::NonModal);
    pSettingsWidget->hide();

    bool bConnected = true;
    bConnected &= static_cast<bool>(connect(pConfirm, SIGNAL(clicked(bool)), SLOT(onConfirm())));
    assert(bConnected);

    return pSettingsWidget;
}

QSlider* ColorSettingsWidget::makeColorComponentSlider(color_components Component)
{
    auto pSlider = new QSlider(Qt::Horizontal);
    pSlider->setRange(0, 255);

    bool bConnected = true;
    bConnected &= static_cast<bool>(connect(pSlider, &QSlider::sliderMoved, this, [this, Component](int iValue)
    {
        setColorComponent(iValue, Component);
    }));
    assert(bConnected);

    return pSlider;
}
