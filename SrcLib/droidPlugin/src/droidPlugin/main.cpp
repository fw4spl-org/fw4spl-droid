/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <qpa/qplatformintegrationplugin.h>
#include "droidPlugin/DroidIntegration.hpp"

QT_BEGIN_NAMESPACE

class DroidIntegrationPlugin : public QPlatformIntegrationPlugin
{

Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformIntegrationFactoryInterface_iid FILE "DroidPlugin.json")
public:
    QPlatformIntegration *create(const QString&, const QStringList&) Q_DECL_OVERRIDE;
};

//--------------------------------------------------------------------------------

QPlatformIntegration* DroidIntegrationPlugin::create(const QString& system, const QStringList& paramList)
{
    Q_UNUSED(paramList);
    if (!system.compare(QLatin1String("droidplugin"), Qt::CaseInsensitive))
    {
        return new DroidIntegration;
    }

    return 0;
}

//--------------------------------------------------------------------------------

QT_END_NAMESPACE

#include "main.moc"
