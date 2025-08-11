#pragma once

#include <QWidget>

class QPushButton;
class QSlider;
class BasePopupWidget;
class BaseValueSlider;

class ColorSettingsWidget: public QWidget
{
    Q_OBJECT

    enum class color_components
    {
        red = 0,
        green,
        blue
    };

public:
    ColorSettingsWidget();

    const QColor& getColor() const noexcept;

signals:
    void colorSelected(QColor);

private slots:
    void onPopup();
    void onConfirm();

private:
    void setColorComponent(int iValue, color_components Component);
    QString getColorComponentName(color_components Component) const;

    BasePopupWidget* makeColorSettingsWidget();
    BaseValueSlider* makeColorComponentSlider(int iDefaultValue, color_components Component);

    QColor m_Color;

    QPushButton* m_pPopup;
    BasePopupWidget* m_pSettingsWidget;
};

