//FPS処理のヘッダーファイル
#pragma once

#include  "DxLib.h"

//マクロ定義
constexpr int GAME_FPS			= 60;			//60FPSで固定する
constexpr float MICRO_SECOND	= 1000000.0f;	//1マイクロ秒
constexpr float MILL_SECOND		= 1000.0f;		//1ミリ秒
constexpr int WAIT_TIME_MILL	= 3000;			//最大で待てるミリ数

typedef struct ST_FPS
{
	LONGLONG FirstTakeTime	 = 0;			//1フレーム目の計測時間
	LONGLONG NowTakeTime	 = 0;			//現在の計測時間
	LONGLONG OldTakeTime	 = 0;			//以前の計測時間
	
	float DeltaTime		= 0.000001f;		//デルタタイム（経過時間）
	int FrameCount		= 1;				//現在のフレーム数
	float Average		= 0.0f;				//平均FPS値

};

//外部グローバル変数
extern ST_FPS fps;

//外部プロトタイプ宣言
extern void FPSInit();	//FPS初期化
extern void FPSCheck();	//FPS計測
extern void FPSDraw();	//FPS描画
extern void FPSWait();	//FPS待機
