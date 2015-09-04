/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVTKDROIDADAPTOR_SMESH_HPP__
#define __VISUVTKDROIDADAPTOR_SMESH_HPP__

#include "visuVTKDroidAdaptor/config.hpp"

#include <fwData/Mesh.hpp>
#include <fwRenderVTK/IVtkAdaptorService.hpp>

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkTransform.h>


namespace visuVTKDroidAdaptor
{

class VISUVTKDROIDADAPTOR_CLASS_API SMesh : public ::fwRenderVTK::IVtkAdaptorService
{
public:
    fwCoreServiceClassDefinitionsMacro ( (SMesh)(::fwRenderVTK::IVtkAdaptorService) );

    VISUVTKDROIDADAPTOR_API SMesh();
    VISUVTKDROIDADAPTOR_API virtual ~SMesh();

    VISUVTKDROIDADAPTOR_API void setAutoResetCamera(bool autoResetCamera);
protected:

    VISUVTKDROIDADAPTOR_API void doStart    () throw(fwTools::Failed);
    VISUVTKDROIDADAPTOR_API void configuring() throw(fwTools::Failed);
    VISUVTKDROIDADAPTOR_API void doStop     () throw(fwTools::Failed);
    VISUVTKDROIDADAPTOR_API void doSwap   () throw(fwTools::Failed);
    VISUVTKDROIDADAPTOR_API void doUpdate   () throw(fwTools::Failed);

private:

    /**
     * @name Slots methods
     * @{
     */

    /// Slot:  used to update the whole mesh
    void modifyMesh();

    /// Slot:  used to update point colors
    void updatePointColors();

    /// Slot: used to update cell colors
    void updateCellColors();

    /// Slot: used to update mesh vertex
    void updateVertex();

    /// Slot: used to show point colors
    void showPointColors();

    /// Slot: used to show cell colors
    void showCellColors();

    /// Slot: used to hide colors
    void hideColors();

    /// Slot: used to update visibility
    void updateVisibility(bool isVisible);


    /**
     * @}
     */

    void buildPipeline();
    void updateMesh( ::fwData::Mesh::sptr mesh );

    /// To store the polyData
    vtkSmartPointer<vtkPolyData> m_polyData;

    /// Vtk mapper
    vtkSmartPointer<vtkPolyDataMapper> m_mapper;

    ///Vtk Actor
    vtkSmartPointer<vtkActor> m_actor;

    bool m_autoResetCamera;

    vtkSmartPointer<vtkTransform> m_transform;


};



} //namespace visuVTKDroidAdaptor

#endif //__VISUVTKDROIDADAPTOR_SMESH_HPP__
