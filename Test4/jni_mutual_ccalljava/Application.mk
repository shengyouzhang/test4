#APP_STL:=gnustl_static
#APP_CPPFLAGS:=-frtti -fexceptions 
# APP_PLATFORM := android-14的版本号必须跟AndroidManifest.xml中的    android:minSdkVersion="14"保持一致
APP_PLATFORM := android-14
#APP_ABI := all//arm64-v8a;armeabi;armeabi-v7a;mips;mips64;x86;x86_64
APP_ABI := armeabi armeabi-v7a x86