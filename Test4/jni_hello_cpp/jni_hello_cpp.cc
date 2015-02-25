#include <stdio.h>
#include <stdlib.h>
#include "samy_log.h"
#include "com_zsy_frame_sample_jni_control_android_hello_cpp_HelloCppCJni.h"

/**
 * 类似于Java反射机制;把java中的String类型变成C语言中的char型；在后面会依次解析
 */
char* Jstring2CStr(JNIEnv* env, jstring jstr) {
	char* rtn = NULL;
	jclass clsstring = (env)->FindClass("java/lang/String");
	jstring strencode = (env)->NewStringUTF("GB2312");
	jmethodID mid = (env)->GetMethodID(clsstring, "getBytes",
			"(Ljava/lang/String;)[B");
	jbyteArray barr = (jbyteArray)(env)->CallObjectMethod(jstr, mid, strencode); // String .getByte("GB2312");
	jsize alen = (env)->GetArrayLength(barr);
	jbyte* ba = (env)->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0) {
		rtn = (char*) malloc(alen + 1); //"\0"
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	(env)->ReleaseByteArrayElements(barr, ba, 0); //
	return rtn;
}

/*
 * Class:     com_zsy_frame_sample_jni_control_android_hello_cpp_HelloCppCJni
 * Method:    hellFromCPP
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_zsy_frame_sample_jni_control_android_hello_cpp_HelloCppCJni_hellFromCPP__(
		JNIEnv * env, jobject obj) {
	//   return 	(*env)->NewStringUTF(env,"haha from c");
	return env->NewStringUTF("haha from cpp end with cc by samy");
}

/*
 * Class:     com_zsy_frame_sample_jni_control_android_hello_cpp_HelloCppCJni
 * Method:    hellFromCPP
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_zsy_frame_sample_jni_control_android_hello_cpp_HelloCppCJni_hellFromCPP__Ljava_lang_String_2(
		JNIEnv * env, jobject obj, jstring str) {
	char* cstr = Jstring2CStr(env, str);//拿到Java中的String对象再次变化成char型打印出来；
	LOGI("%s", cstr);
	return env->NewStringUTF("haha from cc with string");
}
