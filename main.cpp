#include "DxLib.h"
#include "System/fps.h"
#include "game.h"
#include "System/key.h"
#include "System/mouse.h"
#include "System/font.h"
#include "System/music.h"
#include "vcruntime.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{

	SetOutApplicationLogValidFlag(FALSE);			//Log,txtを出力しない
	ChangeWindowMode(TRUE);							//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH,GAME_HEIGHT,GAME_COLOR);	//解像度を設定
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);			//ウィンドウの大きさを設定
	SetMainWindowText(GAME_TITLE);					//ウィンドウのタイトル
	SetBackgroundColor(0, 0, 0);					//ウィンドウの背景色を設定
	SetWaitVSyncFlag(GAME_VSYNC);					//垂直同期の設定
	SetAlwaysRunFlag(TRUE);							//非アクティブでも実行する。
	SetWindowIconID(GAME_ICON);						//アイコンの設定
	
	
	//DxLibを初期化
	if(DxLib_Init()==-1)
	{
		//DxLib初期化失敗ならソフト終了をする
		return -1;
	}

	//裏画面に描画（ダブルバッファリング）
	SetDrawScreen(DX_SCREEN_BACK);

	//フォントの初期化
	if(FontInit()==false)
	{
		GameAndDxLibAllEnd();
		return -1;
	}

	//音楽の初期化
	if(MusicInit()==false)
	{
		GameAndDxLibAllEnd();
		return -1;
	}

	//ゲーム初期化
	InitGame();

	//FPS初期化
	FPSInit();

	//キー初期化
	KeyInit();
	
	//マウス初期化
	MouseInit();

	//タイトルシーンの初期化
	InitScene(NowGameScene);

	while(TRUE)
	{
		//メッセージ処理を行う。（マウスやキーボードの操作を受け続ける）
		if(ProcessMessage() !=0)
		{
			break;
		}

		//画面を消去（1ループずつ書き換える）
		if(ClearDrawScreen() !=0)
		{
			break;
		}
		//FPS計測
		FPSCheck();

		//キー更新
		KeyUpdate();

		//マウス更新
		MouseUpdate();

		//シーン切り替え(シーンごとの処理)
		SwitchScene();

		//FPS描画
		FPSDraw();

		//FPS待機
		FPSWait();
		

		//裏画面を画面に描画
		ScreenFlip();
	}

	//ゲームとDxLibの終了処理
	GameAndDxLibAllEnd();

	return 0;

}
