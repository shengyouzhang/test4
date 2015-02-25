package com.zsy.frame.sample.jni.control.android.hello.cpp;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import com.zsy.frame.sample.jni.R;

public class HelloCppCAct extends Activity {
	private HelloCppCJni helloCppCJni;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_android_hello_cpp);
		helloCppCJni = new HelloCppCJni();
	}

	public void callclick(View view) {
		switch (view.getId()) {
			case R.id.button1:
				Toast.makeText(this, helloCppCJni.hellFromCPP(), Toast.LENGTH_SHORT).show();
				break;
			case R.id.button2:
				Toast.makeText(this, helloCppCJni.hellFromCPP("by with String"), Toast.LENGTH_SHORT).show();
				break;
		// case R.id.button3:
		// try {
		// Toast.makeText(this, new String(hell_1from_1c().getBytes("iso-8859-1"),"utf-8"), Toast.LENGTH_SHORT).show();
		// }
		// catch (UnsupportedEncodingException e) {
		// e.printStackTrace();
		// }
		// break;
		// case R.id.button4:
		// Toast.makeText(this, utf_gbk_1c(), Toast.LENGTH_SHORT).show();
		// break;
		}
	}
}
