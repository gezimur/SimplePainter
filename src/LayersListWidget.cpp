#include "LayersListWidget.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMouseEvent>

#include "LayerListItemWidget.h"

inline const std::string c_strDefaultLayerName = "New preset";

std::vector<LayerListItemWidget*> get_layers_widgets(QVBoxLayout* pLayout)
{
    std::vector<LayerListItemWidget*> vRes;
    for (auto i = 0; i < pLayout->count(); ++i)
    {
        auto pPresetWdg = dynamic_cast<LayerListItemWidget*>(pLayout->itemAt(i)->widget());
        if (!pPresetWdg)
            continue ;

        vRes.push_back(pPresetWdg);
    }
    return vRes;
}

std::string make_name_with_suffix(const std::string& strName, unsigned uSuffix)
{
    if (uSuffix)
        return strName + "(" + std::to_string(uSuffix) + ")";
    else
        return strName;
}

unsigned get_same_presets_cnt(const std::vector<LayerListItemWidget*>& vPresets, const std::string& strName, unsigned uSuffix)
{
    auto strNameWithSuffix = make_name_with_suffix(strName, uSuffix);
    return std::count_if(vPresets.begin(), vPresets.end(), [&strNameWithSuffix](const LayerListItemWidget* pWdg)
    {
        return pWdg->getName() == strNameWithSuffix;
    });
}

std::string make_unique_name(QVBoxLayout* pLayout, const std::string& strName)
{
    auto strUniqueName = strName;
    unsigned uSuffix{0};

    auto vPresetsWdg = get_layers_widgets(pLayout);

    unsigned uSameNames = get_same_presets_cnt(vPresetsWdg, strUniqueName, uSuffix);
    while (uSameNames)
    {
        ++uSuffix;
        uSameNames = get_same_presets_cnt(vPresetsWdg, strUniqueName, uSuffix);
    }

    if (!uSuffix)
        return strName;

    return make_name_with_suffix(strUniqueName, uSuffix);
}

LayersListWidget::LayersListWidget()
    : m_pNameEditor{new QLineEdit},
      m_pAddButton{new QPushButton{"Add"}},
      m_pRemoveButton{new QPushButton{"Remove"}},
      m_pLayersLayout{nullptr},
      m_pSelected{nullptr}
{
    initGui();
    createConnections();
}

void LayersListWidget::onProcNameChanged()
{
    if (!m_pSelected)
        return ;

    auto strPrevName = m_pSelected->getName();
    auto strName = m_pNameEditor->text().toStdString();

    if (strName == strPrevName)
        return ;

    strName = make_unique_name(m_pLayersLayout, strName);
    m_pSelected->setName(strName);

    emit layerRenamed(strPrevName, strName);
}

void LayersListWidget::onProcAdd()
{
    selectImpl(new LayerListItemWidget{make_unique_name(m_pLayersLayout, c_strDefaultLayerName)});
    m_pLayersLayout->addWidget(m_pSelected, 0, Qt::AlignTop);

    bool bConnected = true;
    bConnected = static_cast<bool>(connect(m_pSelected, SIGNAL(toggled(bool)), SLOT(onProcShaffle())));
    bConnected = static_cast<bool>(connect(m_pSelected, SIGNAL(selected(std::string)), SLOT(onSelect(std::string))));
    assert(bConnected);

    emit layerAdded(m_pSelected->getName());
}

void LayersListWidget::onProcRemove()
{
    if (!m_pSelected)
        return ;

    auto strName = m_pSelected->getName();

    m_pLayersLayout->removeWidget(m_pSelected);
    delete m_pSelected;
    m_pSelected = nullptr;

    m_pNameEditor->setDisabled(true);
    m_pNameEditor->clear();

    emit layerRemoved(strName);
}

void LayersListWidget::onSelect(const std::string& strName)
{
    auto pLayer = dynamic_cast<LayerListItemWidget*>(sender());
    assert(pLayer && pLayer->getName() == strName);

    selectImpl(pLayer);
}

void LayersListWidget::onProcShaffle()
{
    emit layersShuffled(getLayersInfo());
}

void LayersListWidget::initGui()
{
    auto pToolsLayout = new QGridLayout;
    pToolsLayout->addWidget(m_pAddButton, 0, 0);
    pToolsLayout->addWidget(m_pRemoveButton, 0, 1);
    pToolsLayout->addWidget(m_pNameEditor, 1, 0, 1, 2);

    m_pLayersLayout = new QVBoxLayout;

    auto pMainLayout = new QVBoxLayout{this};
    pMainLayout->addLayout(pToolsLayout);
    pMainLayout->addLayout(m_pLayersLayout);
    pMainLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void LayersListWidget::createConnections()
{
    bool bConnected = true;

    bConnected &= static_cast<bool>(connect(m_pAddButton, SIGNAL(clicked(bool)), SLOT(onProcAdd())));
    bConnected &= static_cast<bool>(connect(m_pRemoveButton, SIGNAL(clicked(bool)), SLOT(onProcRemove())));
    bConnected &= static_cast<bool>(connect(m_pNameEditor, SIGNAL(editingFinished()), SLOT(onProcNameChanged())));

    assert(bConnected);
}

void LayersListWidget::mouseMoveEvent(QMouseEvent* pEvent)
{
    if (!m_pSelected || !m_pSelected->isGrabbed())
        return ;


    auto iPosibleIndex = (pEvent->pos().y() - m_pLayersLayout->contentsRect().top()) / m_pSelected->height();

    if (iPosibleIndex < 0 || iPosibleIndex >= m_pLayersLayout->count())
        return ;

    auto iSelectedIndex = m_pLayersLayout->indexOf(m_pSelected);

    if (iSelectedIndex == iPosibleIndex)
        return ;

    m_pLayersLayout->removeWidget(m_pSelected);
    m_pLayersLayout->insertWidget(iPosibleIndex, m_pSelected);

    onProcShaffle();
}

std::vector<std::pair<std::string, bool>> LayersListWidget::getLayersInfo() const
{
    std::vector<std::pair<std::string, bool>> vRes;
    vRes.reserve(m_pLayersLayout->count());

    auto vLayers = get_layers_widgets(m_pLayersLayout);
    std::transform(vLayers.begin(), vLayers.end(), std::back_inserter(vRes), [](LayerListItemWidget* pLayer)
    {
        return std::make_pair(pLayer->getName(), pLayer->isActive());
    });

    return vRes;
}

void LayersListWidget::selectImpl(LayerListItemWidget* pWidget)
{
    if (!pWidget)
        return ;

    if (m_pSelected)
        m_pSelected->setSelected(false);
    m_pSelected = pWidget;
    m_pSelected->setSelected(true);

    m_pNameEditor->setEnabled(true);
    m_pNameEditor->setText(QString::fromStdString(pWidget->getName()));

    emit layerSelected(pWidget->getName());
}
