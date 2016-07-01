/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <fstream>

#include <fwRuntime/operations.hpp>
#include <fwRuntime/profile/Profile.hpp>
#include <fwRuntime/io/ProfileReader.hpp>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include <android_native_app_glue.h>
#include <android/asset_manager.h>

#include <string>

namespace android
{

} //namespace android

//------------------------------------------------------------------------------

char* readAsset(AAssetManager* assetManager, const std::string &assetName, size_t& assetLength )
{
    SLM_INFO(" try to read "+assetName);

    AAsset* assetFile = AAssetManager_open(assetManager, assetName.c_str(), AASSET_MODE_UNKNOWN);
    SLM_ASSERT("Cannot open '"+assetName+"'", assetFile);

    assetLength = AAsset_getLength(assetFile);

    size_t dotIndex       = assetName.find_last_of(".");
    std::string extension = assetName.substr(dotIndex, assetName.size());

    char* assetBuffer;
    if( extension != ".so")
    {
        assetBuffer = new char[assetLength+1];
        AAsset_read(assetFile,assetBuffer, assetLength);
        assetBuffer[assetLength] = 0;
    }
    else
    {
        assetBuffer = new char[assetLength];
        AAsset_read(assetFile,assetBuffer, assetLength);
    }

    AAsset_close(assetFile);

    return assetBuffer;
}

//------------------------------------------------------------------------------

void writeAsset(AAssetManager* assetManager, const std::string &assetList, const ::boost::filesystem::path &intPath)
{
    std::vector<std::string> assetsVector;
    ::boost::split(assetsVector, assetList, ::boost::is_any_of(";"));

    for (std::string asset : assetsVector)
    {
        ::boost::filesystem::path destPath = intPath/asset;
        ::boost::filesystem::path dirPath  = destPath.parent_path();

        if(!::boost::filesystem::exists(dirPath))
        {
            bool res = ::boost::filesystem::create_directories(dirPath);
            SLM_ASSERT(" Failed to create '"+dirPath.string()+"' path", res);
        }

        if(!::boost::filesystem::exists(destPath))
        {
            size_t assetLength = 0;
            char* assetBuffer  = readAsset(assetManager, asset, assetLength);
            SLM_INFO(" try to write "+destPath.string());

            std::ofstream outfile(destPath.c_str());
            SLM_ASSERT(" Couldn't open "+destPath.string()+" ",outfile.is_open());
            outfile.write (assetBuffer,assetLength);
            outfile.close();

            delete[] assetBuffer;
        }
        else
        {
            SLM_INFO(" File to write "+destPath.string()+" already exist!");
        }
    }
}
//------------------------------------------------------------------------------

void android_main(struct android_app* app)
{
    // Make sure glue isn't stripped.
    app_dummy();

    ::boost::filesystem::path intPath(app->activity->internalDataPath);
    intPath = intPath.parent_path();

    AAssetManager* assetManager = app->activity->assetManager;
    size_t assetLength;
    char* assetBuffer = readAsset(assetManager,"assets.txt", assetLength);
    std::string assetList(assetBuffer);
    delete[] assetBuffer;
    writeAsset(assetManager, assetList, intPath);

    ::boost::filesystem::path profilePath = intPath / "profile.xml";
    char* profileBuffer = readAsset(assetManager, "profile.xml", assetLength);
    std::ofstream outfile(profilePath.string().c_str());
    SLM_ASSERT(" Couldn't open "+profilePath.string()+" ",outfile.is_open());
    outfile.write (profileBuffer, assetLength);
    outfile.close();
    delete[] profileBuffer;

    ::fwRuntime::Runtime::getDefault()->setWorkingPath(intPath);

    ::boost::filesystem::path bundlePath(intPath/"Bundles/");

    OSLM_FATAL_IF( "Bundle path " << bundlePath << " doesn't exist or isn't a directory.",
                   !::boost::filesystem::is_directory(bundlePath));

    bundlePath = ::boost::filesystem::absolute(bundlePath);
    ::fwRuntime::addBundles( bundlePath );

    ::boost::filesystem::path profileFile(intPath/"profile.xml");
    if ( ::boost::filesystem::is_regular_file(profileFile))
    {
        ::fwRuntime::profile::Profile::sptr profile;

        try
        {
            profile = ::fwRuntime::io::ProfileReader::createProfile(profileFile);
            ::fwRuntime::profile::setCurrentProfile(profile);

            profile->setApp(app);

            profile->start();
            profile->run();
            profile->stop();
        }
        catch(std::exception &e)
        {
            OSLM_FATAL( e.what() );
        }
        catch(...)
        {
            SLM_FATAL( "An unrecoverable error has occurred." );
        }
    }
    else
    {
        OSLM_ERROR( "Profile file " << profileFile << " do not exists or is not a regular file.");
    }

}
