package com.zsy.frame.sample.jni.control.android.mutual.javacallc;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import com.zsy.frame.sample.jni.R;

public class JavacallcAct extends Activity {
	static {
		System.loadLibrary("jni_mutual_javacallc");
	}

	private MutualProvider mutualProvider;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_android_mutual_javacallc);

		mutualProvider = new MutualProvider();
	}

	public void callclick(View view) {
		switch (view.getId()) {
			case R.id.button1:
				int result = mutualProvider.add(5, 8);
				Toast.makeText(this, "相加的结果" + result, Toast.LENGTH_SHORT).show();
				break;
			case R.id.button2:
				String str = mutualProvider.sayHelloInC("haha ");
				Toast.makeText(this, str, Toast.LENGTH_SHORT).show();
				break;
			case R.id.button3:
				int[] arr = { 1, 2, 3, 4, 5 };
				mutualProvider.intMethod(arr);
				StringBuffer buffer = new StringBuffer();
				for (int i = 0; i < arr.length; i++) {
					buffer.append(arr[i]).append(" ");
				}
				Toast.makeText(this, "从C层处理后的数据为：" + buffer.toString(), Toast.LENGTH_SHORT).show();
				break;
			case R.id.button4:
				Toast.makeText(this, MutualProvider.sub(10, 4)+"", Toast.LENGTH_SHORT).show();
				break;
		}
	}
}
