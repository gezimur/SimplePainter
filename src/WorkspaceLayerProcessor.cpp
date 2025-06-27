#include "WorkspaceLayerProcessor.h"

void WorkspaceLayerProcessor::addLayer(const std::string& strLayer)
{
    auto it = findLayer(strLayer);
    if (m_vLayers.end() == it)
        m_vLayers.push_back(std::make_shared<WorkspaceLayer>(strLayer));
}

void WorkspaceLayerProcessor::removeLayer(const std::string& strLayer)
{
    auto it = findLayer(strLayer);
    if (m_vLayers.end() != it)
        m_vLayers.erase(it);
}

void WorkspaceLayerProcessor::selectLayer(const std::string& strLayer)
{
    auto it = findLayer(strLayer);
    if (m_vLayers.end() != it)
        m_spActiveLayer = *it;
}

void WorkspaceLayerProcessor::shuffleLayers(const std::vector<std::pair<std::string, bool>>& vLayers)
{
    assert(vLayers.size() == vLayers.size());

    std::vector<std::shared_ptr<WorkspaceLayer>> vShuffledLayers;
    vShuffledLayers.reserve(vLayers.size());

    for (const auto& [strLayerName, bVisible] : vLayers) ///< @todo make faster
    {
        auto it = findLayer(strLayerName);
        assert(m_vLayers.end() != it);

        auto spLayer = *it;
        spLayer->setVisible(bVisible);
        vShuffledLayers.push_back(spLayer);
    }

    m_vLayers = vShuffledLayers;
}

std::vector<std::string> WorkspaceLayerProcessor::getLayersList() const
{
    std::vector<std::string> vRes;
    vRes.reserve(m_vLayers.size());
    std::transform(m_vLayers.begin(), m_vLayers.end(), std::back_inserter(vRes), [](const std::shared_ptr<WorkspaceLayer>& spLayer)
    {
        return spLayer->getName();
    });
    return vRes;
}

const std::shared_ptr<WorkspaceLayer>& WorkspaceLayerProcessor::getActiveLayer() const noexcept
{
    return m_spActiveLayer;
}

void WorkspaceLayerProcessor::drawVisible(const QMatrix4x4& crMVP)
{
    for (const auto& spLayer : m_vLayers)
        spLayer->draw(crMVP);
}

std::vector<std::shared_ptr<WorkspaceLayer>>::const_iterator WorkspaceLayerProcessor::findLayer(const std::string& strLayer) const
{
    return std::find_if(m_vLayers.begin(), m_vLayers.end(), [strLayer](const std::shared_ptr<WorkspaceLayer>& spLayer)
    {
        return strLayer == spLayer->getName();
    });
}
