package com.zsy.frame.sample.jni.control.android.hello.cpp;

public class HelloCppCJni {
	static {
		System.loadLibrary("jni_hello_cpp");
	}
	
	public native String hellFromCPP();

	public native String hellFromCPP(String str);
}
