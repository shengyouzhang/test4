#include <string.h>
#include "samy_log.h"
#include "com_zsy_frame_sample_jni_control_android_aes_AesJni.h"

//! AES状态矩阵列数目4

//! AES迭代计算轮次，初始值为零，由密钥位数决定其具体值
int Nr = 0;
//! 密钥32位字大小，初始值为零，由密钥位数决定其具体值
int Nk = 0;
//! 明文/密文输入分组数组
unsigned char in[16];
//! 密文/明文输出分组数组
unsigned char out[16];
//! 4×4状态矩阵
unsigned char state[4][4];
//unsigned int state[4][4];
//! round key数组，保存经过膨胀后的子密钥
unsigned char RoundKey[240];
//! 用于AES计算的输入密钥
unsigned char Key[32];

char jieMi[16]; //用来存储解密了的明文数据
int jieMiLen = 0; //用来存储解密了的明文长度

//! 迭代轮次常数数组，在密钥膨胀中取值Rcon[1]-Rcon[10]
int Rcon[255] = { 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
		0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97,
		0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4,
		0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83,
		0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
		0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc,
		0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91,
		0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33,
		0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
		0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
		0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa,
		0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25,
		0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d,
		0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
		0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4,
		0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61,
		0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74,
		0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
		0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97,
		0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4,
		0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83,
		0x1d, 0x3a, 0x74, 0xe8, 0xcb };
/////////////////////////////////////////////////////////////////////////////////

int sbox[256] = {
		//0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
		0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b,
		0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
		0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7, 0xfd, 0x93, 0x26,
		0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
		0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2,
		0xeb, 0x27, 0xb2, 0x75, 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
		0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed,
		0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
		0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f,
		0x50, 0x3c, 0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
		0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c, 0x13, 0xec,
		0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
		0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14,
		0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
		0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d,
		0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
		0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f,
		0x4b, 0xbd, 0x8b, 0x8a, 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
		0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11,
		0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
		0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f,
		0xb0, 0x54, 0xbb, 0x16 };

//*****************************************************************************/

int rsbox[256] = { 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40,
		0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f,
		0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, 0x54, 0x7b,
		0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa,
		0xc3, 0x4e, 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b,
		0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68,
		0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, 0x6c, 0x70,
		0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d,
		0x9d, 0x84, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4,
		0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f,
		0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, 0x3a, 0x91,
		0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4,
		0xe6, 0x73, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9,
		0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29,
		0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, 0xfc, 0x56,
		0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd,
		0x5a, 0xf4, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12,
		0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5,
		0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, 0xa0, 0xe0,
		0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53,
		0x99, 0x61, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69,
		0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };
/******************************************************************************/

//	名称：KeyExpansion
//	功能：密钥膨胀，原始128位密钥经过膨胀会产生(11*4)个字的子密钥，提供(Nr+1)次AddRoundKey变换
//  参数：无(内部使用全局变量)
//	返回：无
//  备注：膨胀算法是以字(4字节，32比特)为基础的
/******************************************************************************/
void KeyExpansion() {
	int i;
	unsigned char temp[4], k;

	//! 第一轮次密钥就是原始密钥
	for (i = 0; i < Nk; i++) {
		RoundKey[i * 4] = Key[i * 4];
		RoundKey[i * 4 + 1] = Key[i * 4 + 1];
		RoundKey[i * 4 + 2] = Key[i * 4 + 2];
		RoundKey[i * 4 + 3] = Key[i * 4 + 3];
	}

	//! 所有其它轮次密钥均来源于上轮次密钥
	while (i < (4 * (Nr + 1))) {
		temp[0] = RoundKey[(i - 1) * 4 + 0];
		temp[1] = RoundKey[(i - 1) * 4 + 1];
		temp[2] = RoundKey[(i - 1) * 4 + 2];
		temp[3] = RoundKey[(i - 1) * 4 + 3];

		if (i % Nk == 0) {
			k = temp[0];
			temp[0] = temp[1];
			temp[1] = temp[2];
			temp[2] = temp[3];
			temp[3] = k;
			//! 密钥膨胀SubWord操作，对32位字进行S盒转换
			temp[0] = sbox[temp[0]];
			temp[1] = sbox[temp[1]];
			temp[2] = sbox[temp[2]];
			temp[3] = sbox[temp[3]];
			temp[0] = temp[0] ^ Rcon[i / Nk];

		} else if (Nk > 6 && i % Nk == 4) {
			//! 密钥膨胀SubWord操作
			temp[0] = sbox[temp[0]];
			temp[1] = sbox[temp[1]];
			temp[2] = sbox[temp[2]];
			temp[3] = sbox[temp[3]];
		}
		RoundKey[i * 4 + 0] = RoundKey[(i - Nk) * 4 + 0] ^ temp[0];
		RoundKey[i * 4 + 1] = RoundKey[(i - Nk) * 4 + 1] ^ temp[1];
		RoundKey[i * 4 + 2] = RoundKey[(i - Nk) * 4 + 2] ^ temp[2];
		RoundKey[i * 4 + 3] = RoundKey[(i - Nk) * 4 + 3] ^ temp[3];
		i++;
	}
}

/******************************************************************************/
//	名称：AddRoundKey
//	功能：将传入的加密矩阵与由密钥膨胀生成的子密钥矩阵进行
//		  异或运算，生成新的加密矩阵
//  参数：迭代轮次
//	返回：无
/******************************************************************************/
void AddRoundKey(int round) {

	state[0][0] ^= RoundKey[round * 4 * 4 + 0 + 0 * 4];
	state[0][1] ^= RoundKey[round * 4 * 4 + 0 + 1 * 4];
	state[0][2] ^= RoundKey[round * 4 * 4 + 0 + 2 * 4];
	state[0][3] ^= RoundKey[round * 4 * 4 + 0 + 3 * 4];

	state[1][0] ^= RoundKey[round * 4 * 4 + 1 + 0 * 4];
	state[1][1] ^= RoundKey[round * 4 * 4 + 1 + 1 * 4];
	state[1][2] ^= RoundKey[round * 4 * 4 + 1 + 2 * 4];
	state[1][3] ^= RoundKey[round * 4 * 4 + 1 + 3 * 4];

	state[2][0] ^= RoundKey[round * 4 * 4 + 2 + 0 * 4];
	state[2][1] ^= RoundKey[round * 4 * 4 + 2 + 1 * 4];
	state[2][2] ^= RoundKey[round * 4 * 4 + 2 + 2 * 4];
	state[2][3] ^= RoundKey[round * 4 * 4 + 2 + 3 * 4];

	state[0][0] ^= RoundKey[round * 4 * 4 + 2 + 0 * 4];
	state[0][1] ^= RoundKey[round * 4 * 4 + 2 + 1 * 4];
	state[0][2] ^= RoundKey[round * 4 * 4 + 2 + 2 * 4];
	state[0][3] ^= RoundKey[round * 4 * 4 + 2 + 3 * 4];

}

/******************************************************************************/
//	名称：SubBytes
//	功能：将传入的加密矩阵，通过Sbox替换为新的加密矩阵
//  参数：状态矩阵(全局变量)
//	返回：无
/******************************************************************************/
void SubBytes() {
	state[0][0] = sbox[state[0][0]];
	state[0][1] = sbox[state[0][1]];
	state[0][2] = sbox[state[0][2]];
	state[0][3] = sbox[state[0][3]];

	state[1][0] = sbox[state[1][0]];
	state[1][1] = sbox[state[1][1]];
	state[1][2] = sbox[state[1][2]];
	state[1][3] = sbox[state[1][3]];

	state[2][0] = sbox[state[2][0]];
	state[2][1] = sbox[state[2][1]];
	state[2][2] = sbox[state[2][2]];
	state[2][3] = sbox[state[2][3]];

	state[3][0] = sbox[state[3][0]];
	state[3][1] = sbox[state[3][1]];
	state[3][2] = sbox[state[3][2]];
	state[3][3] = sbox[state[3][3]];
}

/******************************************************************************/
//	名称：InvSubBytes
//	功能：SubBytes的逆过程
//  参数：结果状态矩阵(全局变量)
//	返回：无
/******************************************************************************/
void InvSubBytes() {
	state[0][0] = rsbox[state[0][0]];
	state[0][1] = rsbox[state[0][1]];
	state[0][2] = rsbox[state[0][2]];
	state[0][3] = rsbox[state[0][3]];

	state[1][0] = rsbox[state[1][0]];
	state[1][1] = rsbox[state[1][1]];
	state[1][2] = rsbox[state[1][2]];
	state[1][3] = rsbox[state[1][3]];

	state[2][0] = rsbox[state[2][0]];
	state[2][1] = rsbox[state[2][1]];
	state[2][2] = rsbox[state[2][2]];
	state[2][3] = rsbox[state[2][3]];

	state[3][0] = rsbox[state[3][0]];
	state[3][1] = rsbox[state[3][1]];
	state[3][2] = rsbox[state[3][2]];
	state[3][3] = rsbox[state[3][3]];
}

/******************************************************************************/
//	名称：ShiftRows
//	功能：ShiftRows变换
//  参数：状态矩阵(全局变量)
//	返回：无
//	备注：加密左移
/******************************************************************************/
void ShiftRows() {
	unsigned char temp;

	//! 第一行循环左移1列
	temp = state[1][0];
	state[1][0] = state[1][1];
	state[1][1] = state[1][2];
	state[1][2] = state[1][3];
	state[1][3] = temp;

	//! 第二行循环左移2列
	temp = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = temp;

	temp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = temp;

	//! 第三行循环左移3列
	temp = state[3][0];
	state[3][0] = state[3][3];
	state[3][3] = state[3][2];
	state[3][2] = state[3][1];
	state[3][1] = temp;
}

/******************************************************************************/
//	名称：InvShiftRows
//	功能：ShiftRows变换逆过程
//  参数：结果状态矩阵(全局变量)
//	返回：无
/******************************************************************************/
void InvShiftRows() {
	unsigned char temp;

	//!  第一行循环右移1列
	temp = state[1][3];
	state[1][3] = state[1][2];
	state[1][2] = state[1][1];
	state[1][1] = state[1][0];
	state[1][0] = temp;

	//!  第二行循环右移2列
	temp = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = temp;

	temp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = temp;

	//!  第三行循环右移3列
	temp = state[3][0];
	state[3][0] = state[3][1];
	state[3][1] = state[3][2];
	state[3][2] = state[3][3];
	state[3][3] = temp;
}

/******************************************************************************/
//	名称：MixColumns
//	功能：将传入加密矩阵与特定矩阵A进行GF(256)上的乘法
//  参数：状态矩阵(全局变量)
//	返回：无
/******************************************************************************/
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))
void MixColumns() {
	int i;
	unsigned char Tmp, Tm, t;
	for (i = 0; i < 4; i++) {
		t = state[0][i];
		Tmp = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
		Tm = state[0][i] ^ state[1][i];
		Tm = xtime(Tm);
		state[0][i] ^= Tm ^ Tmp;
		Tm = state[1][i] ^ state[2][i];
		Tm = xtime(Tm);
		state[1][i] ^= Tm ^ Tmp;
		Tm = state[2][i] ^ state[3][i];
		Tm = xtime(Tm);
		state[2][i] ^= Tm ^ Tmp;
		Tm = state[3][i] ^ t;
		Tm = xtime(Tm);
		state[3][i] ^= Tm ^ Tmp;
	}
}

/******************************************************************************/
//	名称：InvMixColumns
//	功能：MixColumns逆过程
//  参数：结果状态矩阵(全局变量)
//	返回：无
//	备注：
/******************************************************************************/
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))
void InvMixColumns() {
	int i;
	unsigned char a, b, c, d;
	for (i = 0; i < 4; i++) {
		a = state[0][i];
		b = state[1][i];
		c = state[2][i];
		d = state[3][i];

		state[0][i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d)
				^ Multiply(d, 0x09);
		state[1][i] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b)
				^ Multiply(d, 0x0d);
		state[2][i] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e)
				^ Multiply(d, 0x0b);
		state[3][i] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09)
				^ Multiply(d, 0x0e);
	}
}

/******************************************************************************/
//	名称：Cipher
//	功能：AES加密主算法，对加密明文进行10轮迭代计算
//  参数：无(内部使用全局变量)
//	返回：无
/******************************************************************************/
void Cipher() {
	int i, j, round = 0;

	//! 拷贝输入明文到4×4状态矩阵
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
			state[j][i] = in[i * 4 + j];
	}

	//! 首先将第一轮子密钥加入到状态矩阵中
	AddRoundKey(0);

	//! 9轮迭代
	for (round = 1; round < Nr; round++) {
		SubBytes();
		ShiftRows();
		MixColumns();
		AddRoundKey(round);
	}

	//! 最后一轮迭代
	{
		SubBytes();
		ShiftRows();
		AddRoundKey(Nr);
	}

	//! 加密结束，将结果导出到out数组
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
			out[i * 4 + j] = state[j][i];
	}
}

/******************************************************************************/
//	名称：InvCipher
//	功能：AES解密主算法，对加密密文进行10轮迭代计算
//  参数：无(内部使用全局变量)
//	返回：无
/******************************************************************************/
void InvCipher() {
	int i, j, round = 0;

	//! 拷贝输入密文到4×4状态矩阵
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			state[j][i] = in[i * 4 + j];
		}
	}

	//! 首先将第一轮子密钥加入到状态矩阵中
	AddRoundKey(Nr);

	//! 从最后一轮开始，逆向迭代计算
	for (round = Nr - 1; round > 0; round--) {
		InvShiftRows();
		InvSubBytes();
		AddRoundKey(round);
		InvMixColumns();
	}

	//! 最后逆向变换
	InvShiftRows();
	InvSubBytes();
	AddRoundKey(0);

	//! 加密结束，将结果导出到out数组
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			out[i * 4 + j] = state[j][i];
		}
	}
}

/******************************************************************************/
//	名称：aes_encrypt
//	功能：AES加密函数
//  参数：key: 加密密钥；mw: 加密明文
//	返回：无
/******************************************************************************/
void AES_Encrypt(char *comdata, char key[], char *miWen, int *miWenLen) {
	Nr = 128; // 128位密钥
	Nk = Nr / 32; // 密钥大小(32位字)
	Nr = Nk + 6; // 迭代轮次

//	memset( in, 0, sizeof(in) );  //将unsigned char in[16]全部设定为0
	memcpy(Key, key, 16); //将key中的16个字节全部复制到Key中去

	KeyExpansion(); //密钥扩展

	int aa = 0; //传进char miWen[160] 的次数
	int ii = 0;
	int jj = 0; //comdata
	while (1) {
		in[jj] = comdata[ii];
		ii++;
		jj++;
		if (jj == 16) {
			Cipher();
			jj = 0;

			memcpy(miWen + 16 * aa, out, 16);
			aa++;
			*miWenLen = *miWenLen + 16;
		}
		if (jj < 16 && comdata[ii] == '\0') {
			memset(in + ii % 16, '#', 15 - ii % 16);
			in[15] = 16 - ii % 16;
			Cipher();
			memcpy(miWen + 16 * aa, out, 16);
			aa++;
			*miWenLen = *miWenLen + 16;

			break;
		}

	}

}

void AES_Decrypt(char key[], char miWen[], int miWenLen) {
	int count1 = 0, times = 0;

	Nr = 128; // 128位密钥
	Nk = Nr / 32; // 密钥大小(32位字)
	Nr = Nk + 6; // 迭代轮次

//	memset( in, 0, sizeof(in) );  //将in中的前sizeof(in)大小的字节全部设定为0
	memcpy(Key, key, 16); //从key从拷贝16个char字节到Key中

	KeyExpansion(); // 密钥扩展
///////////////////////////////////////////////////////////////////////////////////////////////////
	int ii = 0;
	int jj = 0;
	int aa = 0;
	while (1) {
		in[jj] = miWen[ii];
		ii++;
		jj++;
		if (jj == 16) {
			jj = 0;
			InvCipher();
			times += 16;
			if (times < miWenLen) {
				memcpy(jieMi + aa * 16, out, 16);
				aa++;
				jieMiLen += 16;
			} else
				break;
		}
	}

	//判断末尾是否被填充   在加密时尾部已经设置了标志
	if (out[15] < 16) {
		for (count1 = 16 - out[15]; count1 < 15; count1++)
			if (out[count1] != '#')
				break;
	}
	if (count1 == 15) { //有填充
		memcpy(jieMi + aa * 16, out, 16 - out[15]);
		jieMiLen = jieMiLen + 16 - out[15];
	} else { //无填充
		memcpy(jieMi + aa * 16, out, 16);
		jieMiLen = jieMiLen + 16;
	}
}

/**
 * 加密处理
 */
JNIEXPORT jbyteArray JNICALL Java_com_zsy_frame_sample_jni_control_android_aes_AesJni_AES_1Encrypt(
		JNIEnv *env, jobject jo, jbyteArray key, jbyteArray mingWen) {

	char miWen[16]; //用来存储加密了的密文
	int miWenLen = 0; //用来存储加密了的密文长度

	char k[16] = { '0' };
//	char k[32];
	jbyte* bytekey = (*env)->GetByteArrayElements(env, key, 0); //取到加密密钥
	int bytekeylen = (*env)->GetArrayLength(env, key); //取到加密密钥长度
	int i = 0;
	for (i = 0; i < bytekeylen; i++) {
		k[i] = *(bytekey + i);
	}

	char mw[16] = { '0' }; //必须要赋值啊
//	char mw[32];
	jbyte* bytemingwen = (*env)->GetByteArrayElements(env, mingWen, 0); //取到需要加密的明文
	int bytemingwenlen = (*env)->GetArrayLength(env, mingWen); //得到明文的长度
	for (i = 0; i < bytemingwenlen; i++) {
		mw[i] = *(bytemingwen + i);
	}

	AES_Encrypt(mw, k, miWen, &miWenLen);

	jbyte *miwenstr = (jbyte*) malloc(miWenLen);
	memset(miwenstr, 0, miWenLen);
	memcpy(miwenstr, miWen, miWenLen);

	jbyteArray jarrRV = (*env)->NewByteArray(env, miWenLen);
	(*env)->SetByteArrayRegion(env, jarrRV, 0, miWenLen, miWen);

	return jarrRV;

}
/**
 * 解密处理
 */
JNIEXPORT jbyteArray JNICALL Java_com_zsy_frame_sample_jni_control_android_aes_AesJni_AES_1Decrypt(
		JNIEnv * env, jobject obj, jbyteArray key, jbyteArray miwen) {

	char k[16] = { '0' }; //取得解密密钥
	jbyte* bytekey = (*env)->GetByteArrayElements(env, key, 0);
	int bytekeylen = (*env)->GetArrayLength(env, key);
	int i = 0;
	for (i = 0; i < bytekeylen; i++) {
		k[i] = *(bytekey + i);
	}

	char mw[16] = { '0' };
	jbyte* bytemiwen = (*env)->GetByteArrayElements(env, miwen, 0);
	int bytemiwenlen = (*env)->GetArrayLength(env, miwen);
	for (i = 0; i < bytemiwenlen; i++) {
		mw[i] = *(bytemiwen + i);
	}

	AES_Decrypt(k, mw, bytemiwenlen);

	char mingWen[jieMiLen];
	int j = 0;
	for (j = 0; j < jieMiLen; j++) {
		mingWen[j] = jieMi[j];
	}

	char *mingwenstr = (char*) malloc(jieMiLen);
	memset(mingwenstr, 0, jieMiLen);
	memcpy(mingwenstr, mingWen, jieMiLen);
	jbyteArray jarrRV = (*env)->NewByteArray(env, jieMiLen);
	(*env)->SetByteArrayRegion(env, jarrRV, 0, jieMiLen, mingwenstr);

	jieMiLen = 0;

	return jarrRV;
}

