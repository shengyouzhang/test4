#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "samy_log.h"
#include "com_zsy_frame_sample_jni_control_android_mutual_ccalljava_CallbackProvider.h"
#include "com_zsy_frame_sample_jni_control_android_mutual_ccalljava_CcalljavaAct.h"

/**
 * 返回值 char* 这个代表char数组的首地址
 *  Jstring2CStr 把java中的jstring的类型转化成一个c语言中的char 字符串
 */
char* Jstring2CStr(JNIEnv* env, jstring jstr) {
	char* rtn = NULL;
	jclass clsstring = (*env)->FindClass(env, "java/lang/String"); //String
	jstring strencode = (*env)->NewStringUTF(env, "GB2312"); // 得到一个java字符串 "GB2312"
	jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes",
			"(Ljava/lang/String;)[B"); //[ String.getBytes("gb2312");
	jbyteArray barr = (jbyteArray)(*env)->CallObjectMethod(env, jstr, mid,
			strencode); // String .getByte("GB2312");
	jsize alen = (*env)->GetArrayLength(env, barr); // byte数组的长度
	jbyte* ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
	if (alen > 0) {
		rtn = (char*) malloc(alen + 1); //"\0"
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	(*env)->ReleaseByteArrayElements(env, barr, ba, 0); //
	return rtn;
}

/*
 * JNINativeMethod的定义如下：（其实这里讲的就是动态注册JNI）
 * 获取类中对应JNI的类型；进入bin/classes 运行：javap -s com.zsy.frame.sample.jni.control.android.mutual.ccalljava.CallbackProvider
 * 有的情况不行的话直接进入到class的当前目录下运行命令
 * 其实这个在生成的头文件.h中就可以看到，native的方法返回值的信息，但是不能看到非native的方法的参数信息；
 * Class:     com_zsy_frame_sample_jni_control_android_mutual_ccalljava_CallbackProvider
 * Method:    callmethod1
 * Signature: ()V
 */
void JNICALL Java_com_zsy_frame_sample_jni_control_android_mutual_ccalljava_CallbackProvider_callmethod1
(JNIEnv * env, jobject obj){
	//在c代码里面调用java代码里面的方法
		// java 反射
	    //1 . 找到java代码的 class文件;Class:     com_zsy_frame_sample_jni_control_android_mutual_ccalljava_CallbackProvider
		//    jclass      (*FindClass)(JNIEnv*, const char*);
		//	其实这个如果处理好的话应该配置到全局变量中显示；
		jclass dpclazz = (*env)->FindClass(env,"com/zsy/frame/sample/jni/control/android/mutual/ccalljava/CallbackProvider");
		if(dpclazz==0){
			LOGI("find class error");
return;
		}
		LOGI("find class ");

//2 寻找class里面的方法
//   jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);Signature: ()V
jmethodID method1 = (*env)->GetMethodID(env,dpclazz,"helloFromJava","()V");
		if(method1==0){
			LOGI("find method1 error");
return;
		}
		LOGI("find method1 ");
//3 .调用这个方法
//    void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
(*env)->CallVoidMethod(env,obj,method1);
}

/*
 * Class:     com_zsy_frame_sample_jni_control_android_mutual_ccalljava_CallbackProvider
 * Method:    callmethod2
 * Signature: ()V
 */
 void JNICALL Java_com_zsy_frame_sample_jni_control_android_mutual_ccalljava_CallbackProvider_callmethod2
(JNIEnv * env, jobject obj){
	// java 反射
   //1 . 找到java代码的 class文件
	//    jclass      (*FindClass)(JNIEnv*, const char*);
	jclass dpclazz = (*env)->FindClass(env,"com/zsy/frame/sample/jni/control/android/mutual/ccalljava/CallbackProvider");
	if(dpclazz==0){
		LOGI("find class error");
return;
	}
	LOGI("find class ");

//2 寻找class里面的方法
//   jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
jmethodID method2 = (*env)->GetMethodID(env,dpclazz,"Add","(II)I");
	if(method2==0){
		LOGI("find method2 error");
return;
	}
	LOGI("find method2 ");
// 3 调用这个方法
//    jint        (*CallIntMethod)(JNIEnv*, jobject, jmethodID, ...);
int result = (*env)->CallIntMethod(env,obj,method2,3,5);
	LOGI("c code  RESULT = %d", result);
}

/*
 * Class:     com_zsy_frame_sample_jni_control_android_mutual_ccalljava_CallbackProvider
 * Method:    callmethod3
 * Signature: ()V
 */
 void JNICALL Java_com_zsy_frame_sample_jni_control_android_mutual_ccalljava_CallbackProvider_callmethod3
(JNIEnv * env , jobject obj){
	  //1 . 找到java代码的 class文件
		//    jclass      (*FindClass)(JNIEnv*, const char*);
		jclass dpclazz = (*env)->FindClass(env,"com/zsy/frame/sample/jni/control/android/mutual/ccalljava/CallbackProvider");
		if(dpclazz==0){
			LOGI("find class error");
return;
		}
		LOGI("find class ");

//2 寻找class里面的方法ID
//   jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
jmethodID method3 = (*env)->GetMethodID(env,dpclazz,"printString","(Ljava/lang/String;)V");
		if(method3==0){
			LOGI("find method3 error");
return;
		}
		LOGI("find method3 ");

//3 .调用这个方法
//    void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
(*env)->CallVoidMethod(env,obj,method3,(*env)->NewStringUTF(env,"haha from in c"));

}

/*
 * Class:     com_zsy_frame_sample_jni_control_android_mutual_ccalljava_CallbackProvider
 * Method:    callmethod4
 * Signature: ()V
 */
 void JNICALL Java_com_zsy_frame_sample_jni_control_android_mutual_ccalljava_CallbackProvider_callmethod4
(JNIEnv * env, jobject obj) {
//1 . 找到java代码的 class文件
//    jclass      (*FindClass)(JNIEnv*, const char*);
jclass dpclazz = (*env)->FindClass(env,"com/zsy/frame/sample/jni/control/android/mutual/ccalljava/CallbackProvider");
if(dpclazz==0) {
	LOGI("find class error");
return;
}
LOGI("find class ");

//2 寻找class里面的方法
//   jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
// 注意 :如果要寻找的方法是静态的方法 那就不能直接去获取methodid
//jmethodID method4 = (*env)->GetMethodID(env,dpclazz,"printStaticStr","(Ljava/lang/String;)V");
//    jmethodID   (*GetStaticMethodID)(JNIEnv*, jclass, const char*, const char*);
jmethodID method4 = (*env)->GetStaticMethodID(env,dpclazz,"printStaticStr","(Ljava/lang/String;)V");
if(method4==0) {
	LOGI("find method4 error");
return;
}
LOGI("find method4 ");

//3.调用一个静态的java方法
//    void        (*CallStaticVoidMethod)(JNIEnv*, jclass, jmethodID, ...);
(*env)->CallStaticVoidMethod(env,dpclazz,method4,(*env)->NewStringUTF(env,"static haha in c"));
}
void JNICALL Java_com_zsy_frame_sample_jni_control_android_mutual_ccalljava_CcalljavaAct_call_1activity_1method1
(JNIEnv * env, jobject obj) {
	//在c代码里面调用java代码里面的方法
	// java 反射
	//1 . 找到java代码的 class文件
	//    jclass      (*FindClass)(JNIEnv*, const char*);
	jclass dpclazz = (*env)->FindClass(env,"com/zsy/frame/sample/jni/control/android/mutual/ccalljava/CallbackProvider");
	if(dpclazz==0) {
		LOGI("find class error");
		return;
	}
	LOGI("find class ");

	//2 寻找class里面的方法
	//   jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
	jmethodID method1 = (*env)->GetMethodID(env,dpclazz,"helloFromJava","()V");
	if(method1==0) {
		LOGI("find method1 error");
		return;
	}
	LOGI("find method1 ");
	//3 .调用这个方法
	//    void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
	//    jobject     (*NewObject)(JNIEnv*, jclass, jmethodID, ...);
	//  jobject     (*AllocObject)(JNIEnv*, jclass);
	jobject dpobj= (*env)->AllocObject(env,dpclazz);//分配新 Java 对象而不调用该对象的任何构造函数。返回该对象的引用。

	(*env)->CallVoidMethod(env,dpobj,method1);
}
