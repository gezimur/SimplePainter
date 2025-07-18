#pragma once

#include <memory>
#include <list>

#include <QSize>

#include "WorkspaceLayer.h"
#include "ImageDrawingInstruction.h"

class WorkspaceLayerProcessor
{
public:
    void setSheetSize(const QSize& crSize);

    void addLayer(const std::string& strLayer);
    void removeLayer(const std::string& strLayer);
    void selectLayer(const std::string& strLayer);

    void shuffleLayers(const std::vector<std::pair<std::string, bool>>& vLayers);
    std::vector<std::string> getLayersList() const;

    void undoActiveLayer();
    void redoActiveLayer();
    void addToActiveLayer(const std::shared_ptr<DrawingInstruction>& spInstruction);

    bool hasChanges() const;
    void cacheVisible(const QMatrix4x4& crMVP);
    void drawCached(const QMatrix4x4& MVP) const;

private:
    std::vector<std::shared_ptr<WorkspaceLayer>>::const_iterator findLayer(const std::string& strLayer) const;

    bool m_bChanges = true;
    std::vector<std::shared_ptr<WorkspaceLayer>> m_vLayers;
    std::shared_ptr<WorkspaceLayer> m_spActiveLayer;
    std::shared_ptr<ImageDrawingInstruction> m_spCachedImage;
};

