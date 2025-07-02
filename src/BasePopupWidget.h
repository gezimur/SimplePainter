#pragma once

#include <QWidget>

class BasePopupWidget: public QWidget
{
    Q_OBJECT

public:
    explicit BasePopupWidget(Qt::Corner Corner = Qt::BottomLeftCorner);

    void popup(const QPoint& crPoint);

private:
    void resizeEvent(QResizeEvent* pEvent) final;
    void hideEvent(QHideEvent* pEvent) final;

    QPoint getCorner() const;

    bool m_bVisible;
    Qt::Corner m_PopupFrom;

    QPoint m_PopupPoint;
};

