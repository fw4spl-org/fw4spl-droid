/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVTKDROIDADAPTOR_SVIDEOADAPTER_HPP__
#define __VISUVTKDROIDADAPTOR_SVIDEOADAPTER_HPP__

#include <fwRenderVTK/IVtkAdaptorService.hpp>

#include "visuVTKDroidAdaptor/config.hpp"

class vtkActor;
class vtkImageData;
class vtkTexture;

namespace visuVTKDroidAdaptor
{

/**
 * @brief   Adaptor to render a video frame as a background of a renderer.
 * @class   SVideoAdapter
 */

class VISUVTKDROIDADAPTOR_CLASS_API SVideoAdapter : public ::fwRenderVTK::IVtkAdaptorService
{

public:
    fwCoreServiceClassDefinitionsMacro ( (SVideoAdapter)(::fwRenderVTK::IVtkAdaptorService) );

    /// Constructor
    SVideoAdapter() throw();

    /// Destructor
    virtual ~SVideoAdapter() throw();

    /**
     * @brief Returns proposals to connect service slots to associated object signals,
     * this method is used for obj/srv auto connection
     *
     * Connect Image::s_MODIFIED_SIG to this::s_UPDATE_IMAGE_SLOT
     * Connect Image::s_VISIBILITY_MODIFIED_SIG to this::s_UPDATE_IMAGE_OPACITY_SLOT
     * Connect Image::s_TRANSPARENCY_MODIFIED_SIG to this::s_UPDATE_IMAGE_OPACITY_SLOT
     * Connect Image::s_BUFFER_MODIFIED_SIG to this::s_UPDATE_SLOT
     */
    VISUVTKDROIDADAPTOR_API virtual KeyConnectionsType getObjSrvConnections() const;

protected:

    /// Create the actor and mapper used to show the video frame.
    VISUVTKDROIDADAPTOR_API void doStart() throw(fwTools::Failed);

    /**
     * @verbatim
       <adaptor id="video" class="::visuVTKDroidAdaptor::SVideoAdapter" objectId="imageKey">
        <config renderer="default" cameraUID="..." />
       </adaptor>
       @endverbatim
     * - \b renderer : defines the renderer to show the arrow. It must be different from the 3D objects renderer.
     */
    VISUVTKDROIDADAPTOR_API void configuring() throw(fwTools::Failed);

    /// Calls doUpdate()
    VISUVTKDROIDADAPTOR_API void doSwap() throw(fwTools::Failed);

    /// Updated the frame from the current Image.
    VISUVTKDROIDADAPTOR_API void doUpdate() throw(fwTools::Failed);

    /// Removes the actor from the renderer
    VISUVTKDROIDADAPTOR_API void doStop() throw(fwTools::Failed);

private:

    /// Slot: Update image opacity and visibility
    void updateImageOpacity();

    /// Slot: update image
    void updateImage();

    vtkImageData* m_imageData; ///< vtk image created from current data Image. It is shown in the frame.
    vtkTexture* m_texture;  ///< texture used to show the image
    vtkActor* m_actor;  ///< actor to show frame

    bool m_isTextureInit; /// true if the texture is initialized
};

} //namespace visuVTKDroidAdaptor

#endif /* __VISUVTKDROIDADAPTOR_SVIDEOADAPTER_HPP__ */
