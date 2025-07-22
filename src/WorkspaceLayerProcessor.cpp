#include "WorkspaceLayerProcessor.h"

void WorkspaceLayerProcessor::setSheetSize(const QSize& crSize)
{
    m_spCachedImage = std::make_shared<ImageDrawingInstruction>(QRect{QPoint{0, 0}, crSize});
}

void WorkspaceLayerProcessor::addLayer(const std::string& strLayer)
{
    auto it = findLayer(strLayer);
    if (m_vLayers.end() == it)
    {
        m_spActiveLayer = std::make_shared<WorkspaceLayer>(strLayer);
        m_vLayers.push_back(m_spActiveLayer);
    }
    m_bChanges = true;
}

void WorkspaceLayerProcessor::removeLayer(const std::string& strLayer)
{
    auto it = findLayer(strLayer);
    if (m_vLayers.end() != it)
        m_vLayers.erase(it);
    m_bChanges = true;
}

void WorkspaceLayerProcessor::selectLayer(const std::string& strLayer)
{
    auto it = findLayer(strLayer);
    if (m_vLayers.end() != it)
        m_spActiveLayer = *it;
    m_bChanges = true;
}

void WorkspaceLayerProcessor::renameLayer(const std::string& strPrev, const std::string& strNew)
{
    auto it = findLayer(strPrev);
    if (m_vLayers.end() != it)
        (*it)->setName(strNew);
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
    m_bChanges = true;
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

void WorkspaceLayerProcessor::undoActiveLayer()
{
    if (m_spActiveLayer)
        m_spActiveLayer->undo();
    m_bChanges = true;
}

void WorkspaceLayerProcessor::redoActiveLayer()
{
    if (m_spActiveLayer)
        m_spActiveLayer->redo();
    m_bChanges = true;
}

void WorkspaceLayerProcessor::addToActiveLayer(const std::shared_ptr<DrawingInstruction>& spInstruction)
{
    if (m_spActiveLayer)
        m_spActiveLayer->addInstruction(spInstruction);
    m_bChanges = true;
}

bool WorkspaceLayerProcessor::hasChanges() const
{
    return m_bChanges;
}

void WorkspaceLayerProcessor::cacheVisible(const QMatrix4x4& crMVP)
{
    m_spCachedImage->bindFrameBuffer();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    for (const auto& spLayer : m_vLayers)
    {
        if (spLayer != m_spActiveLayer)
            spLayer->draw(crMVP);
    }
    if (m_spActiveLayer)
        m_spActiveLayer->draw(crMVP);

    m_spCachedImage->releaseFrameBuffer();

    m_bChanges = false;
}

void WorkspaceLayerProcessor::drawCached(const QMatrix4x4& MVP) const
{
    m_spCachedImage->excecute(MVP);
}

std::vector<std::shared_ptr<WorkspaceLayer>>::const_iterator WorkspaceLayerProcessor::findLayer(const std::string& strLayer) const
{
    return std::find_if(m_vLayers.begin(), m_vLayers.end(), [strLayer](const std::shared_ptr<WorkspaceLayer>& spLayer)
    {
        return strLayer == spLayer->getName();
    });
}
