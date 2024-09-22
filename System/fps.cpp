//FPS処理のソースファイル

#include "fps.h"

#include "font.h"

//グローバル変数
ST_FPS fps;

//FPS初期化
void FPSInit()
{
	//Windowsが起動してから現在までの時間を取得する。
	fps.FirstTakeTime = GetNowHiPerformanceCount();

	//他の値も初期化する
	fps.NowTakeTime = fps.FirstTakeTime;
	fps.OldTakeTime = fps.FirstTakeTime;
	fps.DeltaTime =  0.000001f;
	fps.FrameCount = 1;
	fps.Average = 0.0f;

	return; 
}

//計測
void FPSCheck()
{
	//現在の時刻を取得
	fps.NowTakeTime = GetNowHiPerformanceCount();

	//デルタタイムの計算
	fps.DeltaTime = (fps.NowTakeTime - fps.OldTakeTime) / MICRO_SECOND;

	//現在の時刻を保存
	fps.OldTakeTime = fps.NowTakeTime;

	//現在がMaxフレーム目なら
	if(fps.FrameCount==GAME_FPS)
	{
		//1フレームからMaxフレームまでの合計時間を計算する
		float TotalFrameTime = fps.NowTakeTime - fps.FirstTakeTime;

		//合計時間を理想のFPS値で割って平均値を計算する
		float CalcAverage = TotalFrameTime / GAME_FPS;

		//1秒あたりのフレーム数に変換
		fps.Average = MICRO_SECOND / CalcAverage;

		//1フレーム目の時刻を取得
		fps.FirstTakeTime = GetNowHiPerformanceCount();  

		//フレーム数を1に戻す
		fps.FrameCount = 1;
	}
	else
	{
		//フレーム数をカウントアップ
		fps.FrameCount++;
	}

	return;
}

//描画
void FPSDraw()
{
	//ドットフォントでFPSを描画
	DrawFormatStringToHandle(0, 0, GetColor(255, 255, 255),
		fontDotSmall.Handle,
		"FPS:%3.1f", fps.Average);
      
	return; 
}

//待機
void FPSWait()
{
	//早すぎたときに待機するミリ秒
	int wait = 0;

	//待ち時間を計測する。
	wait =
		MICRO_SECOND / GAME_FPS * fps.FrameCount		//理想の時間
		- (fps.NowTakeTime - fps.FirstTakeTime);	//実際の時間

	wait/=MILL_SECOND;	//ミリ秒に変換
	
	//もし待機時間があるなら
	if(wait > 0 && wait <= WAIT_TIME_MILL)
	{
		//メッセージを処理しながら待つ
		WaitTimer(wait);
	}
	return;
}
