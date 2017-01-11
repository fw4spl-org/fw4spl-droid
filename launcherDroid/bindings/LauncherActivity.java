package ${ANDROID_APK_PACKAGE};

public class LauncherActivity extends android.app.NativeActivity
{
    static
    {
       System.loadLibrary("gnustl_shared");
       System.loadLibrary("fwRuntime");
       System.loadLibrary("launcherDroid");
       ${LIBS_TO_LOAD}
    }
 }
