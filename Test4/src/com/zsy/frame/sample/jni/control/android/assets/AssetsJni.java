package com.zsy.frame.sample.jni.control.android.assets;

import android.content.res.AssetManager;

public class AssetsJni {
	static {
		System.loadLibrary("jni_control_android_assets_AssetsJni");
	}

	// 发现这个用onekey_javah不好使，所以现在用最笨的版本，直接用手写配置
	public static native String readFromAssets(AssetManager assetManager, String name);
}
