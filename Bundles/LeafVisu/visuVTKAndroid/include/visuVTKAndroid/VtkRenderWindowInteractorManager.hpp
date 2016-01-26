/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVTKANDROID_VTKRENDERWINDOWINTERACTORMANAGER_HPP__
#define __VISUVTKANDROID_VTKRENDERWINDOWINTERACTORMANAGER_HPP__

#include <string>

#include <fwCore/base.hpp>

#include <fwRenderVTK/IVtkRenderWindowInteractorManager.hpp>

#include "visuVTKAndroid/config.hpp"

class vtkRenderWindowInteractor;

namespace visuVTKAndroid
{

/**
 * @brief   Defines a class to manage vtkRenderWindowInteractor in a window.
 * @class   VtkRenderWindowInteractorManager
 *
 */
class VISUVTKANDROID_CLASS_API VtkRenderWindowInteractorManager : public ::fwRenderVTK::
                                                                  IVtkRenderWindowInteractorManager
{

public:

    fwCoreNonInstanciableClassDefinitionsMacro( (VtkRenderWindowInteractorManager)
                                                (::fwRenderVTK::IVtkRenderWindowInteractorManager) )

    VISUVTKANDROID_API VtkRenderWindowInteractorManager(::fwRenderVTK::IVtkRenderWindowInteractorManager::Key key);

    VISUVTKANDROID_API virtual ~VtkRenderWindowInteractorManager();

    /// Creates an interactor and installs it in window.
    VISUVTKANDROID_API virtual void installInteractor(::fwGui::container::fwContainer::sptr _parent);

    /// Deletes interactor and manage correctly the window (removing layout).
    VISUVTKANDROID_API virtual void uninstallInteractor();

    /// Return a pointer on interactor
    VISUVTKANDROID_API virtual vtkRenderWindowInteractor * getInteractor();

private:

    vtkRenderWindowInteractor *m_interactor;
};

} // namespace visuVTKAndroid

#endif // __VISUVTKANDROID_VTKRENDERWINDOWINTERACTORMANAGER_HPP__
