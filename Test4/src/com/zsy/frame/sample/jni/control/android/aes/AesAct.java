package com.zsy.frame.sample.jni.control.android.aes;

import com.zsy.frame.sample.jni.R;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class AesAct extends Activity {
	private byte[] miwenbyte;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_android_aes);

		final EditText jiamiKey = (EditText) this.findViewById(R.id.jiamiKey);
		final EditText jiamimingwen = (EditText) this.findViewById(R.id.jiamimingwen);
		final TextView miwen = (TextView) this.findViewById(R.id.miwen);
		final EditText jiemikey = (EditText) this.findViewById(R.id.jiemiKey);
		final EditText jiemimingwen = (EditText) this.findViewById(R.id.jiemimingwen);
		Button jiamiBUTTON = (Button) this.findViewById(R.id.jiamibutton);
		Button jiemiBUTTON = (Button) this.findViewById(R.id.jiemibutton);

		jiamiBUTTON.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				byte[] key = { '1', '1' };
				byte[] mingWen = { 'a', 'b', 'c' };

				key = jiamiKey.getText().toString().getBytes();
				mingWen = jiamimingwen.getText().toString().getBytes();

				if (key.length >= 16 || mingWen.length >= 16) {
					Toast.makeText(getApplicationContext(), "输入必须小于16个字节", 1).show();
					return;
				}

				miwenbyte = new AesJni().AES_Encrypt(key, mingWen); // 进行加密

				miwen.setText("密文长度:" + miwenbyte.length + "    内容: ");
				for (int i = 0; i < miwenbyte.length; i++) {
					miwen.append((char) miwenbyte[i] + "");
				}

			}
		});

		jiemiBUTTON.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				byte[] key = jiemikey.getText().toString().getBytes();
				byte[] bufferjiemi = new AesJni().AES_Decrypt(key, miwenbyte); // 解密

				jiemimingwen.setText("明文长度:" + bufferjiemi.length + "   内容: ");
				for (int i = 0; i < bufferjiemi.length; i++) {
					jiemimingwen.append((char) bufferjiemi[i] + "");
				}
			}
		});
	}
}
