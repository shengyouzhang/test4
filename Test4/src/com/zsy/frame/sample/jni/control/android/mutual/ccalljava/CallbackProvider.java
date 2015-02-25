package com.zsy.frame.sample.jni.control.android.mutual.ccalljava;


/**
 * @description：回调机制
 * @author samy
 * @date 2015-1-31 下午6:00:03
 */
public class CallbackProvider {
	/**
	 * @description： C调用java空方法;callmethod1();
	 * @author samy
	 * @date 2014年10月6日 下午4:18:56
	 */
	public void helloFromJava() {
		System.out.println("hello from java");
	}

	/**
	 * @description：C调用java中的带两个int参数的方法;callmethod2();
	 * @author samy
	 * @date 2014年10月6日 下午4:19:15
	 */
	public int Add(int x, int y) {
		int result = x + y;
		System.out.println("java result:" + result);
		return result;
	}

	/**
	 * @description：C调用java中参数为string的方法;callmethod3();
	 * @author samy
	 * @date 2014年10月6日 下午4:19:34
	 */
	public void printString(String s) {
		System.out.println("java: " + s);
	}

	/**
	 * @description：调用一个静态的c代码;callmethod4();
	 * @author samy
	 * @date 2014年10月6日 下午4:20:08
	 */
	public static void printStaticStr(String s) {
		System.out.println("java static:" + s);
	}

	// 让c代码调用对应的java代码
	public native void callmethod1();

	public native void callmethod2();

	public native void callmethod3();

	public native void callmethod4();
}
