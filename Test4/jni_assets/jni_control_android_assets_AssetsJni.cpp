#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <jni.h>
#include <sys/types.h>
#include <stdlib.h>
#include "samy_log.h"

/*
 * AAssetManager这几个方法还是编译不过去；
 * Class:     com_zsy_frame_sample_jni_control_android_assets_AssetsJni
 * Method:    readFromAssets
 * Signature: (Landroid/content/res/AssetManager;Ljava/lang/String;)Ljava/lang/String;
 */
jstring JNICALL Java_com_zsy_frame_sample_jni_control_android_assets_AssetsJni_readFromAssets(
		JNIEnv* env, jclass clazz, jobject assetManager, jstring name) {
	LOGI("readFromAssets enter...");
//jclass this,
	jstring resultStr;
	LOGI("readFromAssets enter111...");
	AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
	LOGI("readFromAssets enter000...");
	if (mgr == NULL) {
		LOGI(" %s", "AAssetManager==NULL");
		return 0;
	}

	/*获取文件名并打开*/
	jboolean iscopy;
	const char *mfile = env->GetStringUTFChars(name, &iscopy); //(*env)->GetStringUTFChars(name, &iscopy); env,
	AAsset* asset = AAssetManager_open(mgr, mfile, AASSET_MODE_UNKNOWN);
	env->ReleaseStringUTFChars(name, mfile); //env,
	if (asset == NULL) {
		LOGI(" %s", "asset==NULL");
		return 0;
	}
	/*获取文件大小linux中的off_t类型默认是32位的long int*/
	off_t bufferSize = AAsset_getLength(asset);
//	LOGI("file size : %d\n", bufferSize);
//	LOGI("file size : %ld\n", bufferSize);
//	LOGI("file size : %jd\n", bufferSize);
	char *buffer = (char *) malloc(bufferSize + 1);
	buffer[bufferSize] = 0;
	int numBytesRead = AAsset_read(asset, buffer, bufferSize);
	LOGI("readFromAssets: %s", buffer);
	resultStr = env->NewStringUTF(buffer);
	free(buffer);
	/*关闭文件*/
	AAsset_close(asset);
	LOGI("readFromAssets exit...");
	return resultStr;
}
