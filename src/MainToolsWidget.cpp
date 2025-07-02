#include "MainToolsWidget.h"

#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>

#include "ColorSettingsWidget.h"
#include "SizeSettingsWidget.h"
#include "LineDrawingTool.h"

MainToolsWidget::MainToolsWidget()
    : m_spTool{std::make_shared<LineDrawingTool>()},
      m_pColorSettings{new ColorSettingsWidget},
      m_pSizeSettings{new SizeSettingsWidget},
      m_pToolsComboBox{new QComboBox},
      m_pUndo{new QPushButton{"Undo"}},
      m_pRedo{new QPushButton{"Redo"}},
      m_pSave{new QPushButton{"Save"}},
      m_pOpen{new QPushButton{"Open"}}
{
    initGui();
    createConnections();
}

void MainToolsWidget::onDisable()
{
    setEnabled(false);
}

void MainToolsWidget::onEnable()
{
    setEnabled(true);
}

void MainToolsWidget::onChangeDrawingTool()
{
    m_spTool->setColor(m_pColorSettings->getColor());
    m_spTool->setSize(m_pSizeSettings->getSize());
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

    bConnected &= static_cast<bool>(connect(m_pToolsComboBox, SIGNAL(activated(int)), SLOT(onChangeDrawingTool())));
    bConnected &= static_cast<bool>(connect(m_pColorSettings, SIGNAL(colorSelected(QColor)), SLOT(onChangeDrawingTool())));
    bConnected &= static_cast<bool>(connect(m_pSizeSettings, SIGNAL(sizeSelected(int)), SLOT(onChangeDrawingTool())));

    bConnected &= static_cast<bool>(connect(m_pUndo, SIGNAL(clicked(bool)), SIGNAL(undo())));
    bConnected &= static_cast<bool>(connect(m_pRedo, SIGNAL(clicked(bool)), SIGNAL(redo())));

    bConnected &= static_cast<bool>(connect(m_pSave, SIGNAL(clicked(bool)), SLOT(onSave())));
    bConnected &= static_cast<bool>(connect(m_pOpen, SIGNAL(clicked(bool)), SLOT(onOpen())));

    assert(bConnected);
}
