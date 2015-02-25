package com.zsy.frame.sample.jni.control.android.mutual.ccalljava;

/**
 * @description：尽量把跟底层交互的方法放在同一个类中；
 * @author samy
 * @date 2014年10月5日 下午7:51:39
 */
public class MutualProvider {
	/**
	 * @description：把两个java中的int传递给c语言, c语言处理完毕后,把相加的结果返回给java
	 * @author samy
	 * @date 2014年10月5日 下午7:50:46
	 */
	public native int add(int x, int y);

	public native char add(char x, char y); // String

	/**
	 * @description：把java中的string传递给c语言, c语言获取到java中的string之后 ,在string后面添加 一个hello 字符串
	 * @author samy
	 * @date 2014年10月5日 下午7:50:57
	 */
	public native String sayHelloInC(String s);

	/**
	 * @description：把java中的一个int数组 传递给c语言,c语言处理完毕这个java数组; 把int数组中的每一个元素+10 ;然后把结果返回给java
	 * @author samy
	 * @date 2014年10月5日 下午7:51:07
	 */
	public native int[] intMethod(int[] iNum);

	public native byte[] byteMethod(byte[] iByte);

	/**
	 * @description：static类型的；
	 * @author samy
	 * @date 2014年10月5日 下午8:03:55
	 */
	public static native int sub(int x, int y);
}
