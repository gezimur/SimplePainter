#pragma once

#include <QWidget>

class QPushButton;
class QSlider;

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

    QWidget* makeColorSettingsWidget();
    QSlider* makeColorComponentSlider(color_components Component);

    QColor m_Color;

    QPushButton* m_pPopup;
    QWidget* m_pSettingsWidget;
};

