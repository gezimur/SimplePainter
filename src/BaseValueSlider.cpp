#include "BaseValueSlider.h"

#include <QLabel>
#include <QSlider>
#include <QHBoxLayout>

BaseValueSlider::BaseValueSlider(const QString& qstrDescription, const QString& qstrValueFormat)
    : m_qstrValueFormat{qstrValueFormat},
      m_pDescription{new QLabel{qstrDescription + ": "}},
      m_pSlider{new QSlider{Qt::Horizontal}},
      m_pValue{new QLabel{m_qstrValueFormat.arg(QString::number(0))}}
{
    auto pLayout = new QHBoxLayout{this};
    pLayout->addWidget(m_pDescription);
    pLayout->addWidget(m_pSlider);
    pLayout->addWidget(m_pValue);

    auto bConnection = true;
    bConnection &= static_cast<bool>(connect(m_pSlider, SIGNAL(valueChanged(int)), SLOT(onProcValueChanged(int))));
    assert(bConnection);
}

void BaseValueSlider::setRange(int iMin, int iMax)
{
    m_pSlider->blockSignals(true);
    m_pSlider->setRange(iMin, iMax);
    m_pSlider->blockSignals(false);
}

void BaseValueSlider::setValue(int iValue)
{
    m_pSlider->blockSignals(true);
    m_pSlider->setValue(iValue);
    m_pSlider->blockSignals(false);
}

int BaseValueSlider::getValue() const
{
    return m_pSlider->value();
}

void BaseValueSlider::onProcValueChanged(int iValue)
{
    m_pValue->setText(m_qstrValueFormat.arg(QString::number(iValue)));
    emit valueChanged(iValue);
}
