#pragma once

#include <QWidget>

class QPushButton;

class SizeSettingsWidget: public QWidget
{
    Q_OBJECT

public:
    SizeSettingsWidget();

signals:
    void sizeSelected(int);

private slots:
    void onSelectSize();

private:
    QPushButton* m_pSelect;
};

