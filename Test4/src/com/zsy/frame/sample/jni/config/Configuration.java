package com.zsy.frame.sample.jni.config;


/**
 * @description：Debug全局配置类
 * @author samy
 * @date 2014年9月10日 下午5:02:59
 */
public class Configuration {
	// public static boolean IS_DEBUG_ENABLE = BuildConfig.DEBUG;
	public static boolean IS_DEBUG_ENABLE =false;//正式环境和测试环境的切换，false:正式环境，true:测试环境
	public static boolean IS_LOG=false;//发布时改为false,不打LOG
	public static String DEBUG_TAG = "PB";
}
