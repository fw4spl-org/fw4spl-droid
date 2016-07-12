/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "uiDroidQt/STransformEditor.hpp"

#include <fwData/TransformationMatrix3D.hpp>
#include <fwDataTools/TransformationMatrix3D.hpp>

#include <fwGuiQt/container/QtContainer.hpp>

#include <fwCom/Slot.hpp>
#include <fwCom/Slot.hxx>
#include <fwCom/Slots.hpp>
#include <fwCom/Slots.hxx>

#include <fwCom/Signal.hxx>

#include <fwServices/macros.hpp>

#include <QHBoxLayout>
#include <QRadioButton>
#include <QGroupBox>
#include <QPushButton>
#include <QButtonGroup>

namespace uiDroidQt
{

//------------------------------------------------------------------------
fwServicesRegisterMacro( ::gui::editor::IEditor, ::uiDroidQt::STransformEditor, ::fwData::TransformationMatrix3D);

static const ::fwCom::Signals::SignalKeyType s_INCREMENTED_SIG = "incremented";
//------------------------------------------------------------------------------

STransformEditor::STransformEditor() throw() : m_selectedAxis("x"), m_increment(10)
{
    m_sigIncremented = newSignal< IncrSignalType >(s_INCREMENTED_SIG);
}

//------------------------------------------------------------------------------

STransformEditor::~STransformEditor() throw()
{
}

//------------------------------------------------------------------------------

void STransformEditor::configuring() throw (::fwTools::Failed)
{
    this->initialize();
}
//------------------------------------------------------------------------------

void STransformEditor::starting() throw (::fwTools::Failed)
{
    this->create();
    ::fwGuiQt::container::QtContainer::sptr qtContainer =
        ::fwGuiQt::container::QtContainer::dynamicCast( this->getContainer() );

    QWidget* const container = qtContainer->getQtContainer();
    SLM_ASSERT("container not instanced", container);

    QHBoxLayout* layout = new QHBoxLayout(container);

    QGroupBox* groupBoxAxis         = new QGroupBox(container);
    QHBoxLayout* layoutGroupBoxAxis = new QHBoxLayout(groupBoxAxis);
    groupBoxAxis->setLayout(layoutGroupBoxAxis);
    m_buttonGroupAxis = new QButtonGroup(groupBoxAxis);

    QRadioButton *buttonX = new QRadioButton ( tr("X"), groupBoxAxis );
    buttonX->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_buttonGroupAxis->addButton(buttonX, 0);
    layoutGroupBoxAxis->addWidget(buttonX);
    buttonX->setChecked(true);

    QRadioButton *buttonY = new QRadioButton ( tr("Y"), groupBoxAxis );
    buttonY->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_buttonGroupAxis->addButton(buttonY, 1);
    layoutGroupBoxAxis->addWidget(buttonY);

    QRadioButton *buttonZ = new QRadioButton ( tr("Z"), groupBoxAxis );
    buttonZ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_buttonGroupAxis->addButton(buttonZ, 2);
    layoutGroupBoxAxis->addWidget(buttonZ);

    m_buttonIncr = new QPushButton(tr("+"));
    m_buttonDecr = new QPushButton(tr("-"));
    QHBoxLayout* layoutGroupBoxButton = new QHBoxLayout(container);
    layoutGroupBoxButton->addWidget(m_buttonIncr);
    layoutGroupBoxButton->addWidget(m_buttonDecr);

    layout->addWidget(groupBoxAxis);
    layout->addLayout(layoutGroupBoxButton);

    QObject::connect(m_buttonGroupAxis.data(), SIGNAL(buttonClicked(int)), this, SLOT(onChangeAxis(int)));
    QObject::connect(m_buttonIncr.data(), &QPushButton::pressed, this, &STransformEditor::onIncrement );
    QObject::connect(m_buttonDecr.data(), &QPushButton::pressed, this, &STransformEditor::onDecrement );
}

//------------------------------------------------------------------------------

void STransformEditor::stopping() throw (::fwTools::Failed)
{
    QObject::disconnect(m_buttonGroupAxis.data(), SIGNAL(buttonClicked(int)), this, SLOT(onChangeAxis(int)));
    QObject::disconnect(m_buttonIncr.data(), &QPushButton::pressed, this, &STransformEditor::onIncrement );
    QObject::disconnect(m_buttonDecr.data(), &QPushButton::pressed, this, &STransformEditor::onDecrement );

    this->getContainer()->clean();
    this->destroy();
}

//------------------------------------------------------------------------------

void STransformEditor::onIncrement()
{
    m_sigIncremented->asyncEmit(m_selectedAxis, m_increment);
}

//------------------------------------------------------------------------------

void STransformEditor::onDecrement()
{
    m_sigIncremented->asyncEmit(m_selectedAxis, -m_increment);
}

//------------------------------------------------------------------------------

void STransformEditor::onChangeAxis(int axis)
{
    switch(axis)
    {
        case 0:
        {
            m_selectedAxis = "x";
            break;
        }
        case 1:
        {
            m_selectedAxis = "y";
            break;
        }
        case 2:
        {
            m_selectedAxis = "z";
            break;
        }
    }
}

//------------------------------------------------------------------------------

void STransformEditor::updating() throw (::fwTools::Failed)
{
}

} // namespace uiDroidQt

