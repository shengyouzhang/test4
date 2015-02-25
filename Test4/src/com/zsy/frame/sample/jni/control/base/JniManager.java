package com.zsy.frame.sample.jni.control.base;

/**
 * @description：Jni管理类
 * @author samy
 * @date 2015-1-26 下午1:34:26
 */
public class JniManager {
	static {
		// 加载so文件
		System.loadLibrary("samy_url");
	}
	private static JniManager mJniManager;

	/**
	 * 获取单例对象
	 * 
	 * @return
	 */
	public static JniManager getInstance() {
		if (mJniManager == null) {
			mJniManager = new JniManager();
		}
		return mJniManager;
	}

	public native String getUrl(boolean isDebug);
}
