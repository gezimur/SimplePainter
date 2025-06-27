#include "WorkspaceLayer.h"

WorkspaceLayer::WorkspaceLayer(const std::string& strName)
    : m_strName{strName},
      m_bVisible{true}
{

}

void WorkspaceLayer::setName(const std::string& strName)
{
    m_strName = strName;
}

const std::string& WorkspaceLayer::getName() const noexcept
{
    return m_strName;
}

void WorkspaceLayer::setVisible(bool bVisible)
{
    m_bVisible = bVisible;
}

void WorkspaceLayer::undo()
{
    if (m_vActive.empty())
        return ;

    auto spInstruction = m_vActive.back();
    m_vActive.erase(m_vActive.rbegin().base());
    m_vRedo.push_back(spInstruction);
}

void WorkspaceLayer::redo()
{
    if (m_vRedo.empty())
        return ;

    auto spInstruction = m_vRedo.back();
    m_vRedo.erase(m_vRedo.rbegin().base());
    m_vActive.push_back(spInstruction);
}

void WorkspaceLayer::addInstruction(const std::shared_ptr<DrawingInstruction>& spInstruction)
{
    m_vActive.push_back(spInstruction);
    m_vRedo.clear();
}

std::vector<std::shared_ptr<DrawingInstruction> > WorkspaceLayer::getActive() const
{
    if (m_bVisible)
        return m_vActive;
    else
        return {};
}

void WorkspaceLayer::draw(const QMatrix4x4& crMVP)
{
    if (!m_bVisible)
        return;

    for (const auto& spInstruction : m_vActive)
        spInstruction->excecute(crMVP);
}
