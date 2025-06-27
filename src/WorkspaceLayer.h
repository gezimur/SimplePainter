#pragma once

#include <memory>
#include <vector>
#include <string>

#include "DrawingInstruction.h"

class WorkspaceLayer
{
public:
    explicit WorkspaceLayer(const std::string& strName);

    void setName(const std::string& strName) ;
    const std::string& getName() const noexcept;

    void setVisible(bool bVisible);

    void undo();
    void redo();

    void addInstruction(const std::shared_ptr<DrawingInstruction>& spInstruction);

    std::vector<std::shared_ptr<DrawingInstruction>> getActive() const;

    void draw(const QMatrix4x4& crMVP);

private:
    std::string m_strName;
    bool m_bVisible;

    std::vector<std::shared_ptr<DrawingInstruction>> m_vActive;
    std::vector<std::shared_ptr<DrawingInstruction>> m_vRedo;
};

