package com.zsy.frame.sample.jni.control.android.mutual.ccalljava;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;

import com.zsy.frame.sample.jni.R;

public class CcalljavaAct extends Activity {
	static {
		System.loadLibrary("jni_mutual_ccalljava");
	}

	/**
	 * @description：在C语言中调用这个方法后，用这个方法去调用CallbackProvider里面的helloFromJava方法；和第一个显示的一样；
	 * @author samy
	 * @date 2014年10月6日 下午6:09:59
	 * ps:这里不好用onekey_javah功能实现；目前只有用最原始的方法生产.h文件
	 * date 2015-2-12 下午9:12:44 (mod )
	 * 是可以用onekey_javah;不过的配置一个1.6版本的JDK去运行编译；
	 */
	public native void call_activity_method1();

	private CallbackProvider callbackProvider;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_android_mutual_ccalljava);
		callbackProvider = new CallbackProvider();
	}

	public void callclick(View view) {
		switch (view.getId()) {
			case R.id.button1:
				callbackProvider.callmethod1();
				break;
			case R.id.button2:
				callbackProvider.callmethod2();
				break;
			case R.id.button3:
				callbackProvider.callmethod3();
				break;
			case R.id.button4:
				callbackProvider.callmethod4();
				break;
			case R.id.button5:
				call_activity_method1();
				break;
		}
	}
}
