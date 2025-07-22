#pragma once

#include <QWidget>

class QVBoxLayout;
class QLineEdit;
class QPushButton;
class LayerListItemWidget;

class LayersListWidget: public QWidget
{
    Q_OBJECT

public:
    LayersListWidget();

signals:
    void layersShuffled(const std::vector<std::pair<std::string, bool>>&);
    void layerAdded(const std::string& );
    void layerRemoved(const std::string& );
    void layerSelected(const std::string& );
    void layerRenamed(const std::string&, const std::string&);

private slots:
    void onProcNameChanged();
    void onProcAdd();
    void onProcRemove();

    void onSelect(const std::string& strName);
    void onProcShaffle();

private:
    void initGui();
    void createConnections();

    void mouseMoveEvent(QMouseEvent* pEvent) final;
    std::vector<std::pair<std::string, bool>> getLayersInfo() const;

    void selectImpl(LayerListItemWidget* pWidget);

    QLineEdit* m_pNameEditor;
    QPushButton* m_pAddButton;
    QPushButton* m_pRemoveButton;

    QVBoxLayout* m_pLayersLayout;
    LayerListItemWidget* m_pSelected;
};

