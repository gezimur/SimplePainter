#include "MainToolsWidget.h"

#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>

#include "ColorSettingsWidget.h"
#include "SizeSettingsWidget.h"
#include "DrawingTools/LineDrawingTool.h"
#include "DrawingTools/drawing_tools.h"

MainToolsWidget::MainToolsWidget()
    : m_pColorSettings{new ColorSettingsWidget},
      m_pSizeSettings{new SizeSettingsWidget},
      m_pToolsComboBox{new QComboBox},
      m_pUndo{new QPushButton{"Undo"}},
      m_pRedo{new QPushButton{"Redo"}},
      m_pSave{new QPushButton{"Save"}},
      m_pOpen{new QPushButton{"Open"}}
{
    initGui();
    createConnections();

    auto iDefaultTool = static_cast<int>(drawing_tools::pen);
    m_pToolsComboBox->setCurrentIndex(iDefaultTool);
    onSwitchTool(iDefaultTool);
}

const std::shared_ptr<DrawingTool>& MainToolsWidget::getTool() const
{
    return m_spTool;
}

void MainToolsWidget::onDisable()
{
    setEnabled(false);
}

void MainToolsWidget::onEnable()
{
    setEnabled(true);
}

void MainToolsWidget::onSwitchTool(int iTool)
{
    m_spTool = make_tool(static_cast<drawing_tools>(iTool));
    m_spTool->setColor(m_pColorSettings->getColor());
    m_spTool->setSize(m_pSizeSettings->getSize());
    emit toolChanged(m_spTool);
}

void MainToolsWidget::onChangeColor(const QColor& crColor)
{
    m_spTool->setColor(crColor);
    emit toolChanged(m_spTool);
}

void MainToolsWidget::onChangeSize(int iSize)
{
    m_spTool->setSize(iSize);
    emit toolChanged(m_spTool);
}

void MainToolsWidget::onSave()
{
    
}

void MainToolsWidget::onOpen()
{
    
}

void MainToolsWidget::initGui()
{
    auto vInstructions = get_all_drawing_instructions();
    for (auto Instruction : vInstructions)
        m_pToolsComboBox->addItem(QString::fromStdString(to_str(Instruction)));

    auto pLayout = new QHBoxLayout{this};
    pLayout->addWidget(m_pToolsComboBox);
    pLayout->addWidget(m_pSizeSettings);
    pLayout->addWidget(m_pColorSettings);

    pLayout->addWidget(m_pUndo);
    pLayout->addWidget(m_pRedo);

    pLayout->addWidget(m_pSave);
    pLayout->addWidget(m_pOpen);
}

void MainToolsWidget::createConnections()
{
    bool bConnected = true;

    bConnected &= static_cast<bool>(connect(m_pToolsComboBox, SIGNAL(activated(int)), SLOT(onSwitchTool(int))));
    bConnected &= static_cast<bool>(connect(m_pColorSettings, SIGNAL(colorSelected(QColor)), SLOT(onChangeColor(QColor))));
    bConnected &= static_cast<bool>(connect(m_pSizeSettings, SIGNAL(sizeSelected(int)), SLOT(onChangeSize(int))));

    bConnected &= static_cast<bool>(connect(m_pUndo, SIGNAL(clicked(bool)), SIGNAL(undo())));
    bConnected &= static_cast<bool>(connect(m_pRedo, SIGNAL(clicked(bool)), SIGNAL(redo())));

    bConnected &= static_cast<bool>(connect(m_pSave, SIGNAL(clicked(bool)), SLOT(onSave())));
    bConnected &= static_cast<bool>(connect(m_pOpen, SIGNAL(clicked(bool)), SLOT(onOpen())));

    assert(bConnected);
}
