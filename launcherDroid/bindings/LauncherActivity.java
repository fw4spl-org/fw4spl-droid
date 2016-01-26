package ${ANDROID_APK_PACKAGE};

import android.content.res.AssetManager;
import android.util.Log;
import android.os.Bundle;
import java.io.IOException;

public class LauncherActivity extends android.app.NativeActivity
{
    private static final String TAG = "LauncherActivity";

    static
    {
       System.loadLibrary("gnustl_shared");
       System.loadLibrary("fwRuntime");
       System.loadLibrary("launcherDroid");
       ${LIBS_TO_LOAD}
    }

 }
