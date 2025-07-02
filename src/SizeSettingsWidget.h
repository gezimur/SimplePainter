#pragma once

#include <QWidget>

class QPushButton;
class BasePopupWidget;
class BaseValueSlider;

class SizeSettingsWidget: public QWidget
{
    Q_OBJECT

public:
    SizeSettingsWidget();

    int getSize() const noexcept;

signals:
    void sizeSelected(int);

private slots:
    void onPopup();

private:
    BasePopupWidget* makeSizeSettingsWidget();

    QPushButton* m_pPopup;
    BaseValueSlider* m_pSizeSlider;
    BasePopupWidget* m_pSettingsWidget;
};

