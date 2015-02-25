#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "samy_log.h"
#include "com_zsy_frame_sample_jni_control_android_hello_c_HelloCJni.h"
/*
 *  Class:     com_zsy_frame_sample_jni_control_android_hello_c_HelloCJni
 * Method:    hellFromC
 * Signature: ()Ljava/lang/String;
 *
 * 方法名称规定 : Java_完整包名类名_方法名()
 * JNIEnv 指针
 *jstring     (*NewStringUTF)(JNIEnv*, const char*);
 * 参数介绍 :
 * env : 代表Java环境, 通过这个环境可以调用Java中的方法
 * thiz : 代表调用JNI方法的对象, 即MainActivity对象
 */
jstring Java_com_zsy_frame_sample_jni_control_android_hello_c_HelloCJni_hellFromC(
		JNIEnv* env, jobject obj) {
//	return (*(*env)).NewStringUTF(env, "hell from c by samy");一样的哦，换一种写法；
	return (*env)->NewStringUTF(env, "hello from c by samy_c");
}

/*
 * Class:     com_zsy_frame_sample_jni_control_android_hello_c_HelloCJni
 * Method:    hell_from_c
 * Signature: ()Ljava/lang/String;
 */
jstring Java_com_zsy_frame_sample_jni_control_android_hello_c_HelloCJni_hell_1from_1c(JNIEnv* env, jobject obj) {
//	return (*(*env)).NewStringUTF(env, "hell from c by samy");一样的哦，换一种写法；
	LOGI("method called");
	LOGI("ARRAY init");
	char* a1 = (char*) malloc(sizeof(char) * 10);
	*a1 = 'a';
	*(a1 + 1) = 'b';
	*(a1 + 9) = '\0';
	LOGI("a1 = %s", a1);
	char a2[2] = { 'e', 'f' };
	LOGI("ARRAY init finish");
	LOGI("copy array");
	strcat(a1, a2); // 把a2的内容 放到a1的后面 要求a1的大小必须> a1+a2
	LOGI("a1  end = %s", a1);
	LOGI("copy array end");
	return (*env)->NewStringUTF(env, "hello from c by samy_1c");
}

/*
 * Class:     com_zsy_frame_sample_jni_control_android_hello_c_HelloCJni
 * Method:    hell_1from_1c
 * Signature: ()Ljava/lang/String;
 */
jstring Java_com_zsy_frame_sample_jni_control_android_hello_c_HelloCJni_hell_11from_11c(JNIEnv* env,
		jobject obj) {
//	return (*(*env)).NewStringUTF(env, "hell from c by samy");一样的哦，换一种写法；
	return (*env)->NewStringUTF(env, "ni hao samy + 你好？深圳1");
}
/*
 * Class:     com_zsy_frame_sample_jni_control_android_hello_c_HelloCJni
 * Method:    utf_gbk_1c
 * Signature: ()Ljava/lang/String;
 */
jstring Java_com_zsy_frame_sample_jni_control_android_hello_c_HelloCJni_utf_1gbk_11c(JNIEnv* env, jobject obj) {
	return (*env)->NewStringUTF(env, "ni hao samy + 你好？深圳2");
}
