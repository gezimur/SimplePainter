#pragma once

#include <memory>
#include <vector>
#include <string>

#include "DrawingInstruction.h"

class WorkspaceLayer
{
public:
    WorkspaceLayer();

    void setName(const std::string& strName) noexcept;
    const std::string& getName() const noexcept;

    void undo();
    void redo();

    void addInstruction(const std::shared_ptr<DrawingInstruction>& spInstruction);

    const std::vector<std::shared_ptr<DrawingInstruction>>& getActive() const noexcept;

private:
    std::string m_strName;

    std::vector<std::shared_ptr<DrawingInstruction>> m_vActive;
    std::vector<std::shared_ptr<DrawingInstruction>> m_vRedo;
};

