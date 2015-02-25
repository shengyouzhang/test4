#include <string.h>
#include "samy_log.h"
#include "com_zsy_frame_sample_jni_control_android_mutual_javacallc_MutualProvider.h"
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
 * Class:     com_zsy_frame_sample_jni_control_android_mutual_javacallc_MutualProvider
 * Method:    add
 * Signature: (II)I
 */
jint JNICALL Java_com_zsy_frame_sample_jni_control_android_mutual_javacallc_MutualProvider_add__II(
		JNIEnv * env, jobject obj, jint x, jint y) {
	LOGI("x=%d", x);
	LOGI("y=%d", y);
	return x + y;
}
/*
 * 现在没有实现
 * Class:     com_zsy_frame_sample_jni_control_android_mutual_javacallc_MutualProvider
 * Method:    add
 * Signature: (CC)C
 */
jchar JNICALL Java_com_zsy_frame_sample_jni_control_android_mutual_javacallc_MutualProvider_add__CC(
		JNIEnv * env, jobject obj, jchar x, jchar y) {
}
/*
 *   The  strcat() function appends the src string to the dest string, over‐
 writing the terminating null byte ('\0') at the end of dest,  and  then
 adds  a  terminating  null  byte.  The strings may not overlap, and the
 dest string must have enough space for the result.
 *
 * Class:     com_zsy_frame_sample_jni_control_android_mutual_javacallc_MutualProvider
 * Method:    sayHelloInC
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
jstring JNICALL Java_com_zsy_frame_sample_jni_control_android_mutual_javacallc_MutualProvider_sayHelloInC(
		JNIEnv * env, jobject obj, jstring jstr) {
	//在c语言中 是没有java的String；把Java中的String变成C中的Char;
	char* cstr = Jstring2CStr(env, jstr);
	LOGD("cstr=%s", cstr);
	// c语言中的字符串 都是以'/0' 作为结尾
//	char arr[6] = { ' ', 'h', 'e', 'l', 'l', 'o' };
	char arr[7] = { ' ', 'h', 'e', 'l', 'l', 'o', '\0' };
	strcat(cstr, arr); //追加到cstr中的后面显示；jstrh hello
	LOGI("new cstr=%s", cstr);
	return (*env)->NewStringUTF(env, cstr); //把C中的Char变成Java中的String;
}
/*
 * env java 虚拟机 结构体c实现的指针 包含的有很多jni方法
 * jobject obj 代表的是调用这个c代码的java对象 代表的是MutualProvider的对象
 * Class:     com_zsy_frame_sample_jni_control_android_mutual_javacallc_MutualProvider
 * Method:    intMethod
 * Signature: ([I)[I
 */
JNIEXPORT jintArray JNICALL Java_com_zsy_frame_sample_jni_control_android_mutual_javacallc_MutualProvider_intMethod(
		JNIEnv * env, jobject obj, jintArray arr) {
	//1.知道数组的长度
	//2.操作这个数组里面的每一个元素
	int len = (*env)->GetArrayLength(env, arr); //获取数组的长度
	LOGI("shuzu len =%d", len);
	//  jint* GetIntArrayElements(jintArray array, jboolean* isCopy)；
//	jint* intarr = (*env)->GetIntArrayElements(env, arr, 1);
//	r9版本后，好像不支持isCopy=1类型；
	jint* intarr = (*env)->GetIntArrayElements(env, arr, 0); //获取数组的元素数据
	int i = 0; //c99对应的c语言语法
	for (; i < len; i++) {
		LOGI("before_intarr[%d]=%d", i, intarr[i]);
//		*(intarr + i) += 10;
		intarr[i] += 10;
		LOGI("after_intarr[%d]=%d", i, intarr[i]);
	}
//    void (*ReleaseIntArrayElements)(JNIEnv*, jintArray,jint*, jint);
	(*env)->ReleaseIntArrayElements(env, arr, intarr, 0); // c语言释放掉 刚才申请的内存空间
	return arr;
}
/*
 * 现在没有实现
 * Class:     com_zsy_frame_sample_jni_control_android_mutual_javacallc_MutualProvider
 * Method:    byteMethod
 * Signature: ([B)[B
 */
jbyteArray JNICALL Java_com_zsy_frame_sample_jni_control_android_mutual_javacallc_MutualProvider_byteMethod(
		JNIEnv * env, jobject obj, jbyteArray arrkey) {
	char k[16] = { '0' }; //取得解密密钥
	jbyte* bytekey = (*env)->GetByteArrayElements(env, arrkey, 0);
	int bytekeylen = (*env)->GetArrayLength(env, arrkey);
	int i = 0;
	for (i = 0; i < bytekeylen; i++) {
		k[i] = *(bytekey + i);
		//打算输出byte数组中的数据
	}
}
/*
 * jclass clazz:代表的是调用c代码 的class类;可见静态的类处理简单
 * Class:     com_zsy_frame_sample_jni_control_android_mutual_javacallc_MutualProvider
 * Method:    sub
 * Signature: (II)I
 */
jint JNICALL Java_com_zsy_frame_sample_jni_control_android_mutual_javacallc_MutualProvider_sub(
JNIEnv * env, jclass clazz, jint x, jint y) {
	LOGI("x=%d", x);
	LOGI("y=%d", y);
	return x - y;
}
