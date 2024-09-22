//ゲーム処理のソースファイル

#include "game.h"
#include "System/font.h"
#include "geometory.h"
#include "Game/Ball.h"
#include "System/key.h"
#include "System/mouse.h"
#include "System/music.h"
#include "Game/Block.h"
#include "System/Button.h"
#include "System/fps.h"

//ゲームシーン
enum E_GameScene NowGameScene;	//現在のゲームシーン

RECT GameWindow;            //ゲームウィンドウの矩形
HWND GameHandle;	            //ゲームのウィンドウハンドル

bool Isfade;    //フェード中かどうか
int ScreenFadeInMillTime;       //フェードインの時間
int ScreenFadeInMillTimeMax;    //フェードインの最大時間
int ScreenFadeOutMillTime;      //フェードアウトの時間
int ScreenFadeOutMillTimeMax;   //フェードアウトの最大時間


//ゲームシーンの名前
const char GameSceneName[GAME_SCENE_COUNT][GAME_SCENE_TEXT_MAX] =
{
    "タイトル画面",
    "プレイ画面",
    "リザルト画面"
};
//スタートボタンの作成
Button startButton= {RECT{(GAME_WIDTH/2)-100, (GAME_HEIGHT/2)+150,
    (GAME_WIDTH/2)+100,(GAME_HEIGHT/2)+200},
    Color{255,0,0},"Start",fontDotSmall};

//リスタートボタンの作成
Button restartButton= {RECT{(GAME_WIDTH/2)-250, (GAME_HEIGHT/2)+150,
    (GAME_WIDTH/2)-50,(GAME_HEIGHT/2)+200},
    Color{255,0,0},"Restart",fontDotSmall};

//タイトルボタンの作成
Button titleButton= {RECT{(GAME_WIDTH/2)+50, (GAME_HEIGHT/2)+150,
    (GAME_WIDTH/2)+250,(GAME_HEIGHT/2)+200},
    Color{255,0,0},"Title",fontDotSmall};

//終了ボタンの作成
Button endButton= {RECT{(GAME_WIDTH/2)-100, (GAME_HEIGHT/2)+250,
    (GAME_WIDTH/2)+100,(GAME_HEIGHT/2)+300},
    Color{255,0,0},"Quit",fontDotSmall};


// ゲーム初期化関数
void InitGame()
{
    //ゲーム画面ハンドルを取得
    GameHandle = GetMainWindowHandle();

    //ゲームウィンドウの矩形を取得
    GameWindow = GetRect(0,0,GAME_WIDTH,GAME_HEIGHT);
    
    //最初のシーンを設定
    NowGameScene = E_GameScene::TitleScene;

    //ボールとブロックの初期化
    ball.Ball_Init();
    block.Block_Init();
    
}

//ゲームとDxLibの終了処理
void GameAndDxLibAllEnd()
{
    //フォントの終了処理
    FontEnd();

    //Musicの終了処理
    MusicEnd();
	
    //DxLib終了する
    DxLib_End();
}

// ゲームハンドル取得
HWND GetGameHandle()
{
    return GameHandle;
}

// ゲームウィンドウ取得
RECT GetGameWindow()
{
    return GameWindow;
}

/// 初期化関数
/// @param scene シーンの種類
void InitScene(E_GameScene scene)
{
    //ブレンドモードの設定
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
    //デバッグモードが有効なら
    if (GAME_DEBUG_MODE == TRUE)
    {
        //初期化中のシーン名を表示
        DrawFormatString(GAME_WIDTH - 200, 0, GetColor(255, 255, 255),
            "%s%s", GameSceneName[static_cast<int>(scene)], "初期化");
    }

    //該当シーンになったときの初期化処理
    switch (scene)
    {
        
    case E_GameScene::PlayScene:
        // プレイシーンでブロックの初期化
        break;
    }
}

/// 制御関数
/// @param scene シーンの種類
void CtrlScene(E_GameScene scene)
{
    ProcScene(scene);
    DrawScene(scene);
}

/// 処理関数
/// @param scene シーンの種類
void ProcScene(E_GameScene scene)
{

    //該当シーンになったときの処理
    switch (scene)
    {
    case E_GameScene::TitleScene:
        // タイトルシーンの処理
            //音楽を再生
                MusicPlay(titleBGM);
        //スタートボタンが押されたら
        startButton.CollButtonToMouseClick(MOUSE_INPUT_LEFT);
            
        //スタートボタンの処理部分
        if(startButton.IsOnceClick())
        {
            //スタートボタンを無効化する
            startButton.SetActive(false);
            //BGMのフェードアウト
            FadeOutPlayMusic(&titleBGM,1000);
            if (FadeInScene(1000)==true)
            {
                //スタートボタンを有効化する
                startButton.ResetOnceClick();
                startButton.SetActive(true);
                //音楽を停止
                MusicStop(&titleBGM);
                NowGameScene = E_GameScene::PlayScene;
                //初期化
                InitScene(NowGameScene);
                //もしPlaySceneがゲーム終了後なら
                if(GameEnd()==true)
                {
                    //ボールとブロックを再設置
                    ball.Ball_Init();
                    block.Block_Init();
                }
            }
        }

        //終了ボタンの処理部分
        endButton.CollButtonToMouseClick(MOUSE_INPUT_LEFT);
        if(endButton.IsOnceClick())
        {
            //終了ボタンを無効化する
            endButton.SetActive(false);
            //BGMのフェードアウト
            FadeOutPlayMusic(&titleBGM,1000);
            if (FadeInScene(1000)==true)
            {
                //終了ボタンを有効化する
                endButton.ResetOnceClick();
                endButton.SetActive(true);
                //音楽を停止
                MusicStop(&titleBGM);
                //ゲームとDxLibの終了処理
                GameAndDxLibAllEnd();
            }
        }
        break;
        
    case E_GameScene::PlayScene:
        // プレイシーンの処理
            //音楽を再生
                MusicPlay(playBGM);

        //タイトルボタンの位置
        titleButton.SetPosition(RECT{(GAME_WIDTH/2)+50, (GAME_HEIGHT/2)+150,
    (GAME_WIDTH/2)+250,(GAME_HEIGHT/2)+200});
        
        //ゲームオーバーになったらブロックとボールを再設置
        if(GameEnd()==true)
        {
            //リスタートボタンをを押したか
            restartButton.CollButtonToMouseClick(MOUSE_INPUT_LEFT);
            //タイトルボタンを押したか
            titleButton.CollButtonToMouseClick(MOUSE_INPUT_LEFT);
            //バーを動かなくする
            block.SetBarMove(false);
            //ボールのスピードを0にする
            ball.SetSpeed(0,0);
            
            //リスタートボタンが一度でも押されたらボールとブロックを再設置
            if(restartButton.IsOnceClick())
            {
                ball.Ball_Init();
                block.Block_Init();
                //リスタートボタンを有効化する
                restartButton.ResetOnceClick();
            }
            //タイトルボタンが一度でも押されたら
            if(titleButton.IsOnceClick())
            {
                //titleButtonを無効化
                titleButton.SetActive(false);
                
                //BGMのフェードアウト
                FadeOutPlayMusic(&playBGM,1000);
                if (FadeInScene(1000)==true)
                {
                    //タイトルボタンを有効化する
                    titleButton.ResetOnceClick();
                    titleButton.SetActive(true);
                    //音楽を停止
                    MusicStop(&playBGM);
                    NowGameScene = E_GameScene::TitleScene;
                    //初期化
                    InitScene(NowGameScene);
                }
            }
        }
        //ブロックの計算
        block.Block_Cal();
        //ボールの計算
        ball.Ball_Cal();

        //ゲームクリアになったら
        if(IsGameClear()==true)
        {
            //BGMのフェードアウト
            FadeOutPlayMusic(&playBGM,1000);
            if (FadeInScene(1000)==true)
            {
                //音楽を停止
                MusicStop(&playBGM);
                NowGameScene = E_GameScene::ResultScene;
                //初期化
                InitScene(NowGameScene);
            }
        }
        //デバッグ用
        if(GAME_DEBUG_MODE)
        {
            //スペースキーを押したらシーンの移動
            if (KeyDown(KEY_INPUT_SPACE))
            {
                //BGMのフェードアウト
                FadeOutPlayMusic(&playBGM,1000);
                if (FadeInScene(1000)==true)
                {
                    //音楽を停止
                    MusicStop(&playBGM);
                    NowGameScene = E_GameScene::ResultScene;
                    //初期化
                    InitScene(NowGameScene);
                }
            }
        }
        
            break;
        case E_GameScene::ResultScene:
            // リザルトシーンの処理
            //音楽を再生
            MusicPlay(resultBGM);

        //タイトルボタンの位置
        titleButton.SetPosition(RECT{(GAME_WIDTH/2)-100, (GAME_HEIGHT/2)+150,
    (GAME_WIDTH/2)+100,(GAME_HEIGHT/2)+200});
        
        //タイトルボタンを押したか
        titleButton.CollButtonToMouseClick(MOUSE_INPUT_LEFT);
        //タイトルボタンが一度でも押されたら
        if(titleButton.IsOnceClick())
        {
            //titleButtonを無効化
            titleButton.SetActive(false);
                
            //BGMのフェードアウト
            FadeOutPlayMusic(&resultBGM,1000);
            if (FadeInScene(1000)==true)
            {
                //タイトルボタンを有効化する
                titleButton.ResetOnceClick();
                titleButton.SetActive(true);
                //音楽を停止
                MusicStop(&resultBGM);
                NowGameScene = E_GameScene::TitleScene;
                //初期化
                InitScene(NowGameScene);
            }
        }

        //終了ボタンの処理部分
        endButton.CollButtonToMouseClick(MOUSE_INPUT_LEFT);
        if(endButton.IsOnceClick())
        {
            //終了ボタンを無効化する
            endButton.SetActive(false);
            //BGMのフェードアウト
            FadeOutPlayMusic(&resultBGM,1000);
            if (FadeInScene(1000)==true)
            {
                //終了ボタンを有効化する
                endButton.ResetOnceClick();
                endButton.SetActive(true);
                //音楽を停止
                MusicStop(&resultBGM);
                //ゲームとDxLibの終了処理
                GameAndDxLibAllEnd();
            }
        }
            break;
    }
   
}

/// 描画関数
/// @param scene シーンの種類
void DrawScene(E_GameScene scene)
{

    switch (scene)
    {
        // タイトルシーンの場合
        case E_GameScene::TitleScene:
            // 背景色を設定
            DrawBox(0, 0,GAME_WIDTH,GAME_HEIGHT, GetColor(178, 216, 255), TRUE);
            // タイトル文字の描画
            DrawFormatStringToHandle(GAME_WIDTH / 2-170, GAME_HEIGHT/2-200, GetColor(255, 255, 255),
            fontDotLarge.Handle,"ブロック崩し");
            // スタートボタンの描画
            startButton.Button_Draw();
            startButton.SetText("Start",fontDotSmall);
            //終了ボタンの描画
            endButton.Button_Draw();
            endButton.SetText("Quit",fontDotSmall);
            break;
        
        // プレイシーンの場合
        case E_GameScene::PlayScene:
            // 背景色を設定
            DrawBox(0, 0,GAME_WIDTH,GAME_HEIGHT, GetColor(210, 105, 30), TRUE);
            // ブロックの描画
            block.Block_Draw();
            ball.Ball_Draw();
            //ゲームオーバーになったらブロックとボールを再設置
            if(GameEnd()==true)
            {
                //リスタートボタンの描画
                restartButton.Button_Draw();
                restartButton.SetText("Restart",fontDotSmall);

                //タイトルボタンの描画
                titleButton.Button_Draw();
                titleButton.SetText("Title",fontDotSmall);
            }
        break;

        // リザルトシーンの場合
        case E_GameScene::ResultScene:
            // 背景色を設定
            DrawBox(0, 0,GAME_WIDTH,GAME_HEIGHT, GetColor(211, 211, 211), TRUE);
            // クリア文字の描画
            DrawFormatStringToHandle(GAME_WIDTH / 2 - 170, GAME_HEIGHT/2 - 200, GetColor(255, 255, 255),
            fontDotLarge.Handle,"Game Clear!!");
            //タイトルボタンの描画
            titleButton.Button_Draw();
            titleButton.SetText("Title",fontDotSmall);
            //終了ボタンの描画
            endButton.Button_Draw();
            endButton.SetText("Quit",fontDotSmall);
            break;    
        }

        // デバックモードが有効なら
        if(GAME_DEBUG_MODE)
        {
            // シーン名を表示
            DrawFormatStringToHandle(GAME_WIDTH - 200, 0, GetColor(255, 255, 255),
                fontDotSmall.Handle,
                "%s%s", GameSceneName[static_cast<int>(scene)], "描画中");
        }
    
}

// ゲームオーバーの処理
bool GameEnd()
{
    bool endFlag = false;

    //ボールが落ちてしまった場合
    if (ball.GetCircle().pt.y > GAME_HEIGHT)
    {
        endFlag = true;
    }
    
    return endFlag;
}

// ゲームクリアの処理
bool IsGameClear()
{
    bool endFlag = true;
    // ゲームオーバーの処理
    for (int y=0;y<BLOCK_NUM_Y;y++)
    {
        for (int x=0;x<BLOCK_NUM_X;x++)
        {
            // 一つでもブロックがある場合ゲームを続ける
            if (block.GetBlock(x,y).isAlive == true)
            {
                endFlag = false;
                break;
            }
        }
    }
    
    return endFlag;
}

// シーン切り替え関数
void SwitchScene()
{
    CtrlScene(NowGameScene);
}

/// 
/// @param fadeInFrame フェードに使う時間（1000=1秒）
/// @return true フェードイン終了　false フェードイン中
bool FadeInScene(int fadeInFrame)
{
    //初めてフェードインを行う
    if (!Isfade)
    {
        //フェードイン時間を設定
        ScreenFadeInMillTime = 0;
        ScreenFadeInMillTimeMax = (fadeInFrame/1000.0f) * GAME_FPS;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
        //フェードイン開始
        Isfade = true;
    }

    //フェードイン中
    if(Isfade)
    {
        if(ScreenFadeInMillTime <= ScreenFadeInMillTimeMax)
        {
            //フェードイン時間をカウントアップ
            ScreenFadeInMillTime++;
            
            //ブレンドモードを設定(255 - 経過時間/最大時間 * 最大アルファ値)
            SetDrawBlendMode(DX_BLENDMODE_ALPHA,255 - (float)ScreenFadeInMillTime/ScreenFadeInMillTimeMax * 255 );
            
        }
        else if(ScreenFadeInMillTime >= ScreenFadeInMillTimeMax)
        {
            //フェードイン終了
            Isfade = false;
            return true;
        }
    }
    return false;
}

///
/// @param fadeOutFrame フェードに使う時間（1000=1秒）
/// @return true フェードアウト終了　false フェードアウト中
bool FadeOutScene(int fadeOutFrame)
{
    //初めてフェードインを行う
    if (!Isfade)
    {
        //フェードイン時間を設定
        ScreenFadeInMillTime = 0;
        ScreenFadeInMillTimeMax = (fadeOutFrame/1000.0f) * GAME_FPS;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
        //フェードイン開始
        Isfade = true;
    }

    //フェードイン中
    if(Isfade)
    {
        if(ScreenFadeInMillTime <= ScreenFadeInMillTimeMax)
        {
            //フェードイン時間をカウントアップ
            ScreenFadeInMillTime++;
            
            //ブレンドモードを設定(経過時間/最大時間 * 最大アルファ値)
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, (float)ScreenFadeInMillTime/ScreenFadeInMillTimeMax * 255 );
            
        }
        else if(ScreenFadeInMillTime >= ScreenFadeInMillTimeMax)
        {
            //フェードイン終了
            Isfade = false;
            return true;
        }
    }
    return false;
}
