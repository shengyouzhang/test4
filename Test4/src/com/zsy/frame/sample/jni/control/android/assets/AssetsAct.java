package com.zsy.frame.sample.jni.control.android.assets;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.zsy.frame.sample.jni.R;

public class AssetsAct extends Activity {
	Button javaShowBtn;
	Button jniShowBtn;
	TextView showTextView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_android_assets);
		initUI();
		javaShowBtn.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				String str = readFromAssets("test.txt"); // notes.txt System.getProperty("file.encoding")+"\n"
				showTextView.setText("Java读取:" + str);
			}
		});

		jniShowBtn.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				String str = AssetsJni.readFromAssets(getAssets(), "test.txt"); // notes.txt
				showTextView.setText("Jni读取:" + str);
			}
		});

	}

	public void initUI() {
		javaShowBtn = (Button) findViewById(R.id.btn_javashow);
		jniShowBtn = (Button) findViewById(R.id.btn_jnishow);
		showTextView = (TextView) findViewById(R.id.textview_show);
	}

	/**
	 * @description： 从Java层读取Assects文件夹内东西
	 * @author samy
	 * @date 2015-1-31 下午1:38:37
	 */
	public String readFromAssets(String name) {
		String resultStr = "";
		try {
			InputStream inStream = this.getResources().getAssets().open(name);
			resultStr = convertStream2String(inStream);
			// convertStreamToString(inStream);
		}
		catch (IOException e) {
			e.printStackTrace();
		}

		return resultStr;
	}

	public String convertStream2String(InputStream is) {
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		int i = 0;
		String str = "";
		// String str2 = "";
		int l = 0;
		try {
			l = is.available();
		}
		catch (IOException e1) {
			e1.printStackTrace();
		}
		byte[] buffer = new byte[l];
		try {
			while ((i = is.read()) != -1) {
				baos.write(i);
			}
			is.close();
			str = baos.toString("utf-8");
			// str2 = new String(baos.toByteArray(), "utf-8");
			// str2 = EncodingUtils.getString(buffer, "utf-8"); //gb2312
		}
		catch (IOException e) {
			e.printStackTrace();
		}
		return str;
	}

	public String convertStreamToString(InputStream is) throws IOException {
		/*
		 * 　　28 * 为了将InputStream转换成String我们使用函数BufferedReader.readLine().
		 * 　　29 * 我们迭代调用BufferedReader直到其返回null, null意味着没有其他的数据要读取了.
		 * 　　30 * 每一行将会追加到StringBuilder的末尾, StringBuilder将作为String返回。
		 * 　　31 *
		 * 　　32
		 */
		if (is != null) {
			StringBuilder sb = new StringBuilder();
			String line;
			try {
				BufferedReader reader = new BufferedReader(new InputStreamReader(is, "UTF-8"));
				while ((line = reader.readLine()) != null) {
					sb.append(line).append("\n");
				}
			}
			finally {
				is.close();
			}
			return sb.toString();
		}
		else {
			return "";
		}
	}
}
