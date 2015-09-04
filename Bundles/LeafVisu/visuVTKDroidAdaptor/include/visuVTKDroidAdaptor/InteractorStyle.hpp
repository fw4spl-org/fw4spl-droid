/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVTKDROIDADAPTOR_INTERACTORSTYLE_HPP__
#define __VISUVTKDROIDADAPTOR_INTERACTORSTYLE_HPP__

#include "visuVTKDroidAdaptor/config.hpp"

#include <fwRenderVTK/IVtkAdaptorService.hpp>

class vtkInteractorStyle;

namespace visuVTKDroidAdaptor
{



class VISUVTKDROIDADAPTOR_CLASS_API InteractorStyle : public ::fwRenderVTK::IVtkAdaptorService
{

public:

    fwCoreServiceClassDefinitionsMacro ( (InteractorStyle)(::fwRenderVTK::IVtkAdaptorService) );

    VISUVTKDROIDADAPTOR_API InteractorStyle() throw();

    VISUVTKDROIDADAPTOR_API virtual ~InteractorStyle() throw();

protected:

    VISUVTKDROIDADAPTOR_API void doStart() throw(fwTools::Failed);
    VISUVTKDROIDADAPTOR_API void doStop() throw(fwTools::Failed);

    VISUVTKDROIDADAPTOR_API void configuring() throw(fwTools::Failed);
    VISUVTKDROIDADAPTOR_API void doSwap() throw(fwTools::Failed);
    // redraw all (stop then restart sub services)
    VISUVTKDROIDADAPTOR_API void doUpdate() throw(fwTools::Failed);

    void setInteractorStyle(vtkInteractorStyle *interactor);

    std::string m_configuredStyle;
    vtkInteractorStyle *m_interactorStyle;
};




} //namespace visuVTKDroidAdaptor

#endif // __VISUVTKDROIDADAPTOR_INTERACTORSTYLE_HPP__
