/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "uiDroidQt/SOrganMaterialEditor.hpp"

#include <fwGuiQt/container/QtContainer.hpp>

#include <fwCom/Slot.hpp>
#include <fwCom/Slot.hxx>
#include <fwCom/Slots.hpp>
#include <fwCom/Slots.hxx>

#include <fwCom/Signal.hxx>

#include <fwData/Material.hpp>
#include <fwData/Reconstruction.hpp>
#include <fwMedData/ModelSeries.hpp>

#include <fwServices/macros.hpp>

#include <QHBoxLayout>
#include <QPushButton>

namespace uiDroidQt
{

//------------------------------------------------------------------------
fwServicesRegisterMacro( ::gui::editor::IEditor, ::uiDroidQt::SOrganMaterialEditor, ::fwMedData::ModelSeries);

//------------------------------------------------------------------------------

SOrganMaterialEditor::SOrganMaterialEditor() throw()
{
}

//------------------------------------------------------------------------------

SOrganMaterialEditor::~SOrganMaterialEditor() throw()
{
}

//------------------------------------------------------------------------------

void SOrganMaterialEditor::configuring() throw (::fwTools::Failed)
{
    this->initialize();
}
//------------------------------------------------------------------------------

void SOrganMaterialEditor::starting() throw (::fwTools::Failed)
{
    this->create();
    ::fwGuiQt::container::QtContainer::sptr qtContainer =
        ::fwGuiQt::container::QtContainer::dynamicCast( this->getContainer() );

    QWidget* const container = qtContainer->getQtContainer();
    SLM_ASSERT("container not instanced", container);

    QHBoxLayout* layout = new QHBoxLayout(container);

    m_button = new QPushButton(tr("+"));
    m_button->setAutoRepeat(true);

    QHBoxLayout* layoutGroupBoxButton = new QHBoxLayout(container);
    layoutGroupBoxButton->addWidget(m_button);
    layout->addLayout(layoutGroupBoxButton);

    QObject::connect(m_button.data(), &QPushButton::pressed, this, &SOrganMaterialEditor::changeOpacity);
}

//------------------------------------------------------------------------------

void SOrganMaterialEditor::stopping() throw (::fwTools::Failed)
{
    QObject::disconnect(m_button.data(), &QPushButton::pressed, this, &SOrganMaterialEditor::changeOpacity);

    this->getContainer()->clean();
    this->destroy();
}

//------------------------------------------------------------------------------

void SOrganMaterialEditor::changeOpacity()
{
    ::fwMedData::ModelSeries::sptr modelSeries = this->getObject< ::fwMedData::ModelSeries>();
    SLM_ASSERT("No modelSeries!", modelSeries);

    std::vector< SPTR(::fwData::Reconstruction) > reconstructionDB = modelSeries->getReconstructionDB();

    for (auto rec : reconstructionDB)
    {
        if ("Liver" == rec->getStructureType())
        {
            ::fwData::Material::sptr material = rec->getMaterial();
            material->diffuse()->alpha()      = 0.5f;

            ::fwData::Object::ModifiedSignalType::sptr sig;
            sig = material->signal< ::fwData::Object::ModifiedSignalType >(::fwData::Object::s_MODIFIED_SIG);
            sig->asyncEmit();
        }
    }


}

//------------------------------------------------------------------------------

void SOrganMaterialEditor::updating() throw (::fwTools::Failed)
{
}

} // namespace uiDroidQt

