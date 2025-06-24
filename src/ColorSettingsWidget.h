#pragma once

#include <QWidget>

class QPushButton;

class ColorSettingsWidget: public QWidget
{
    Q_OBJECT

public:
    ColorSettingsWidget();

signals:
    void colorSelected(QColor);

private slots:
    void onSelectColor();

private:
    QPushButton* m_pSelect;
};

