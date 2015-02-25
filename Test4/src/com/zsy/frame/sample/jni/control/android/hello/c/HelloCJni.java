package com.zsy.frame.sample.jni.control.android.hello.c;

public class HelloCJni {
	public native String hellFromC();

	public native String hell_from_c();

	public native String hell_1from_1c();

	public native String utf_gbk_1c();

	static {
		System.loadLibrary("jni_hello_c");
	}
}
