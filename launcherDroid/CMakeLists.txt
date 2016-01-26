fwLoadProperties()

fwUseForwardInclude(fwCore fwRuntime)

find_library(ANDROID_NATIVE_APP_GLUE_LIB android_native_app)
fwLink(
    ${ANDROID_NATIVE_APP_GLUE_LIB}
    log
    android
)
