#pragma once

#include <memory>
#include <list>

#include <QSize>

#include "WorkspaceLayer.h"

class WorkspaceLayerProcessor
{
public:
    void addLayer(const std::string& strLayer);
    void removeLayer(const std::string& strLayer);
    void selectLayer(const std::string& strLayer);

    void shuffleLayers(const std::vector<std::pair<std::string, bool>>& vLayers);
    std::vector<std::string> getLayersList() const;

    const std::shared_ptr<WorkspaceLayer>& getActiveLayer() const noexcept;

    void drawVisible(const QMatrix4x4& crMVP);

private:
    std::vector<std::shared_ptr<WorkspaceLayer>>::const_iterator findLayer(const std::string& strLayer) const;

    std::vector<std::shared_ptr<WorkspaceLayer>> m_vLayers;
    std::shared_ptr<WorkspaceLayer> m_spActiveLayer;
};

