//ゲーム処理のヘッダーファイル
#pragma once

#include  "DxLib.h"

//マクロ定義
constexpr int GAME_WIDTH	 = 1280;				//画面の幅
constexpr int GAME_HEIGHT = 720;					//画面の高さ
constexpr int GAME_COLOR	 = 32;					//画面の色
constexpr const char* GAME_TITLE = "ブロック崩し";	//画面タイトル
constexpr bool GAME_VSYNC = true;				//V-Syncを使う場合true
constexpr int GAME_ICON = 999;					//ゲームアイコンのID

constexpr bool GAME_DEBUG_MODE = false;			//デバッグモードを使う場合true
constexpr int GAME_SCENE_COUNT = 3;					//ゲームシーンの数
constexpr int GAME_SCENE_TEXT_MAX = 30;			//ゲームシーン名の最大文字数

//ゲームシーン
enum class E_GameScene: int
{
    TitleScene,
    PlayScene,
    ResultScene
};

//ゲームフェーズ
enum class E_GamePhase
{
    Initialization, // 初期化
    Control,        // 制御
    Processing,     // 処理
    Drawing         // 描画
};

//外部グローバル変数
extern enum E_GameScene NowGameScene;	//現在のゲームシーン
extern enum E_GameScene ChangeGameScene;	//切り替わるゲームシーン

// 外部プロトタイプ宣言
void InitGame(); // ゲーム初期化
void GameAndDxLibAllEnd();	//ゲームとDxLibの終了処理
HWND GetGameHandle(); // ゲームハンドル取得
RECT GetGameWindow(); // ゲームウィンドウ取得

void InitScene(E_GameScene scene); // シーン初期化
void CtrlScene(E_GameScene scene); // シーン制御
void ProcScene(E_GameScene scene); // シーン処理
void DrawScene(E_GameScene scene); // シーン描画

bool GameEnd(); // ゲームオーバーの処理
bool IsGameClear(); // ゲームクリアの処理


extern void SwitchScene();  //シーンスイッチ
extern bool FadeInScene(int fadeInFrame); //フェードイン(1000=1秒)
extern bool FadeOutScene(int fadeOutFrame); //フェードアウト(1000=1秒)



