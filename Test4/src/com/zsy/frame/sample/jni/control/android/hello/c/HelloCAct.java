package com.zsy.frame.sample.jni.control.android.hello.c;

import java.io.UnsupportedEncodingException;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import com.zsy.frame.sample.jni.R;

public class HelloCAct extends Activity {
	private HelloCJni helloCJni;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_android_hello_c);
		helloCJni = new HelloCJni();
	}

	
	public void callclick(View view) {
		switch (view.getId()) {
			case R.id.button1:
				// showToastMsg(msg);
				Toast.makeText(this, helloCJni.hellFromC(), Toast.LENGTH_SHORT).show();
				break;
			case R.id.button2:
				Toast.makeText(this, helloCJni.hell_from_c(), Toast.LENGTH_SHORT).show();
				break;
			case R.id.button3:
				try {
					Toast.makeText(this, new String(helloCJni.hell_1from_1c().getBytes("iso-8859-1"), "utf-8"), Toast.LENGTH_SHORT).show();
				} catch (UnsupportedEncodingException e) {
					e.printStackTrace();
				}
				break;
			case R.id.button4:
				Toast.makeText(this, helloCJni.utf_gbk_1c(), Toast.LENGTH_SHORT).show();
				break;
		}
	}
}
