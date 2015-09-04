/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVTKDROIDADAPTOR_STRANSFORM_HPP__
#define __VISUVTKDROIDADAPTOR_STRANSFORM_HPP__

#include <vector>

#include <fwRenderVTK/IVtkAdaptorService.hpp>

#include "visuVTKDroidAdaptor/config.hpp"

#include <vtkSmartPointer.h>

class vtkTransform;

namespace visuVTKDroidAdaptor
{

/**
 * @brief Adaptor to manage a TransformationMatrix3D from a vtkTransform and vice versa
 * @class Transform
 */
class VISUVTKDROIDADAPTOR_CLASS_API STransform : public ::fwRenderVTK::IVtkAdaptorService
{

public:

    fwCoreServiceClassDefinitionsMacro ( (STransform)(::fwRenderVTK::IVtkAdaptorService) );

    /// Constructor
    VISUVTKDROIDADAPTOR_API STransform() throw();
    /// Destructor
    VISUVTKDROIDADAPTOR_API virtual ~STransform() throw();

    /// Set a new vtkTransform
    VISUVTKDROIDADAPTOR_API void setTransform(vtkTransform *t);

    /// Returns the current vtkTransform
    VISUVTKDROIDADAPTOR_API vtkTransform *getTransform();

    /// Updates the TransformationMatrix3D from the vtkTransform
    VISUVTKDROIDADAPTOR_API void updateFromVtk();

protected:

    /// Calls doUpdate()
    VISUVTKDROIDADAPTOR_API void doStart() throw(fwTools::Failed);

    /**
     * @brief Configure the adaptor.
     * @verbatim
       <adaptor id="tmAdaptor" class="::visuVTKDroidAdaptor::Transform" objectId="tm3dKey" >
        <config transform="transform" autoRender="true" parent="parentTransform" />
       </adaptor>
       @endverbatim
     * With :
     *  - \b transform (mandatory) : the vtkTransform to associate to the adaptor
     *  - \b autoRender (optional, "true" by default): if autoRender=true,  the scene is automatically rendered after
     *    doStart, doUpdate, doSwap and doStop if m_vtkPipelineModified=true.
     *  - \b parent (optional): id of the parent vtkTransform, it will be concatenated with this current vtkTransform.
     */
    VISUVTKDROIDADAPTOR_API void configuring() throw(fwTools::Failed);

    /// Calls doUpdate()
    VISUVTKDROIDADAPTOR_API void doSwap() throw(fwTools::Failed);

    /// Updates the vtkTransform from the TransformationMatrix3D
    VISUVTKDROIDADAPTOR_API void doUpdate() throw(fwTools::Failed);

    /// Does nothing
    VISUVTKDROIDADAPTOR_API void doStop() throw(fwTools::Failed);

    /// Current vtkTransform
    vtkTransform* m_transform;

    /// Command used to listen m_transform changes
    vtkCommand* m_transformCommand;

    /// Parent vtkTransform id (optional)
    std::string m_parentId;

    /// Parent vtkTransform (optional)
    vtkSmartPointer<vtkTransform> m_parentTransform;
};

} //namespace visuVTKDroidAdaptor

#endif // __VISUVTKDROIDADAPTOR_STRANSFORM_HPP__
