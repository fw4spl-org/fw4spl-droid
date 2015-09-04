/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "visuVTKAndroid/VtkRenderWindowInteractorManager.hpp"
#include "visuVTKAndroid/Plugin.hpp"

#include <fwRuntime/profile/Profile.hpp>

#include <fwRenderVTK/registry/macros.hpp>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAndroidRenderWindowInteractor.h>

#include <android_native_app_glue.h>

//-----------------------------------------------------------------------------

fwRenderVTKRegisterMacro( ::visuVTKAndroid::VtkRenderWindowInteractorManager,
                          ::fwRenderVTK::IVtkRenderWindowInteractorManager::REGISTRY_KEY );

//-----------------------------------------------------------------------------

namespace visuVTKAndroid
{

//-----------------------------------------------------------------------------

VtkRenderWindowInteractorManager::VtkRenderWindowInteractorManager(
    ::fwRenderVTK::IVtkRenderWindowInteractorManager::Key key ) : m_interactor(nullptr)
{
}

//-----------------------------------------------------------------------------

VtkRenderWindowInteractorManager::~VtkRenderWindowInteractorManager()
{
}

//-----------------------------------------------------------------------------

void VtkRenderWindowInteractorManager::installInteractor()
{
    ::fwRuntime::profile::Profile::sptr profile = ::fwRuntime::profile::getCurrentProfile();
    SLM_ASSERT("Profile is not initialized", profile);
    SLM_ASSERT("Android window not yet available", profile->getApp()->window);

    vtkAndroidRenderWindowInteractor* interactor = vtkAndroidRenderWindowInteractor::New();
    interactor->SetAndroidApplication(profile->getApp());
    vtkRenderWindow* renWin = vtkRenderWindow::New();
    interactor->SetRenderWindow(renWin);

    int width  = ANativeWindow_getWidth(profile->getApp()->window);
    int height = ANativeWindow_getHeight(profile->getApp()->window);
    OSLM_TRACE("Config Resized to " << width << " by " << height);

    renWin->SetWindowId(profile->getApp()->window);
    renWin->Start();

    interactor->Initialize();

    SLM_ASSERT("RenderWindow not mapped", interactor->GetRenderWindow()->GetMapped());

    if (width != interactor->GetSize()[0] || height != interactor->GetSize()[1])
    {
        interactor->UpdateSize(width,height);
        interactor->GetRenderWindow()->Render();
    }

    m_interactor = interactor;
}

//-----------------------------------------------------------------------------

void VtkRenderWindowInteractorManager::uninstallInteractor()
{
    SLM_TRACE("Destroying Window");
    m_interactor->GetRenderWindow()->Finalize();
    m_interactor = nullptr;
}

//-----------------------------------------------------------------------------

::vtkRenderWindowInteractor * VtkRenderWindowInteractorManager::getInteractor()
{
    return m_interactor;
}

//-----------------------------------------------------------------------------

} // namespace visuVTKAndroid




