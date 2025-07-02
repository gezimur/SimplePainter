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
    void onConfirm();

private:
    BasePopupWidget* makeSizeSettingsWidget();

    int m_iSize;

    QPushButton* m_pPopup;
    BaseValueSlider* m_pSizeSlider;
    BasePopupWidget* m_pSettingsWidget;
};

