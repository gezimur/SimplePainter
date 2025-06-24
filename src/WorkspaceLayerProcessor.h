#pragma once

#include <memory>
#include <list>

#include <opencv2/core/mat.hpp>

#include "WorkspaceLayer.h"

class WorkspaceLayerProcessor
{
public:
    WorkspaceLayerProcessor();

    void addLayer(const std::string& strLayer);
    void removeLayer(const std::string& strLayer);
    void selectLayer(const std::string& strLayer);

    void shuffleLayers(const std::list<std::string>& lLayers);
    std::list<std::string> getLayersList() const;

    const std::shared_ptr<WorkspaceLayer>& getActiveLayer() const noexcept;

    cv::Mat getBackgroundFrame() const;

private:
    std::list<std::shared_ptr<WorkspaceLayer>> m_lLayers;
    std::shared_ptr<WorkspaceLayer> m_spActiveLayer;

    cv::Mat m_BackgroundFrame;
};

