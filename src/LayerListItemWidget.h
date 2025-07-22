#pragma once

#include <QCheckBox>

class LayerListItemWidget: public QCheckBox
{
    Q_OBJECT

public:
    explicit LayerListItemWidget(const std::string& strName);

    bool isGrabbed() const;

    bool isSelected() const;
    void setSelected(bool bSelect);

    bool isActive() const;
    void setActive(bool bActive);

    const std::string& getName() const;
    void setName(const std::string& strName);

signals:
    void selected(const std::string& );

private:
    void mousePressEvent(QMouseEvent* pEvent);
    void mouseReleaseEvent(QMouseEvent* pEvent);

    std::string m_strName;
    bool m_bSelected;
    bool m_bGrabbed;
};

