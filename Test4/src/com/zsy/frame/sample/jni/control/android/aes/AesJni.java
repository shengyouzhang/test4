package com.zsy.frame.sample.jni.control.android.aes;

public class AesJni {
	static {
		System.loadLibrary("jni_aes");
	}
	
	/*
	 * 功能：加密 参数：key 加密密钥； mingwen 需要加密的明文 返回：返回密文16个字节
	 */
	public native byte[] AES_Encrypt(byte[] key, byte[] mingWen);

	/*
	 * 功能：解密 参数：key 解密密钥； miWen 需要解密的明文 返回值：返回明文 小于16个字节
	 */
	public native byte[] AES_Decrypt(byte[] key, byte[] miWen);
}
