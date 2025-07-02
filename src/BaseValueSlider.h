#pragma once

#include <QWidget>

class QSlider;
class QLabel;

class BaseValueSlider: public QWidget
{
    Q_OBJECT

public:
    explicit BaseValueSlider(const QString& qstrDescription, const QString& qstrValueFormat = "%0");

    void setRange(int iMin, int iMax);

    void setValue(int iValue);
    int getValue() const;

signals:
    void valueSelected(int);

private slots:
    void onProcValueSelected();
    void onProcValueChanged(int iValue);

private:
    QString m_qstrValueFormat;

    QLabel* m_pDescription;
    QSlider* m_pSlider;
    QLabel* m_pValue;
};

