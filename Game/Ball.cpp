//ボールの処理のソースファイル
#include "Ball.h"
#include "../game.h"
#include "../System/music.h"

//グローバル変数
Ball ball;

//コンストラクタ
Ball::Ball()
{
    Ball_Init();
}

//デストラクタ
Ball::~Ball()
{
}

//ボールの初期化
void Ball::Ball_Init()
{
    //ボールの初期化
    Circle = { GAME_WIDTH / 2, 500, BALL_SIZE };
    //ボールのスピードの初期化
    Speed = { 0, -10 };
}

//ボールの計算
void Ball::Ball_Cal()
{
    // 壁との衝突判定と反転処理
    if (Circle.pt.x <0||Circle.pt.x>GAME_WIDTH-2*Circle.radius) // 左右の壁
    {
        //SEの再生
        MusicPlay(hitSE_02);
        // 反転処理
        Speed.x *= -1;
    }
    if (Circle.pt.y <0) // 上下の壁
    {
        //SEの再生
        MusicPlay(hitSE_02);
        // 反転処理
        Speed.y *= -1;
    }

    //ボールの移動
    Circle.pt.x += Speed.x;
    Circle.pt.y += Speed.y;
}

//ボールの描画
void Ball::Ball_Draw()
{
    //ボールの描画
    DrawCircle(Circle.pt.x, Circle.pt.y, Circle.radius,
        GetColor(255, 0, 0), TRUE);

    //デバックモードの場合
    if(GAME_DEBUG_MODE)
    {
        //ボールの座標の描画
        DrawFormatString(Circle.pt.x, Circle.pt.y, GetColor(255, 255, 255),
            "(%d,%d)", Circle.pt.x,Circle.pt.y);

        //ボールのスピードの描画
        DrawFormatString(Circle.pt.x, Circle.pt.y + 20, GetColor(255, 255, 255),
            "(%d,%d)", Speed.x, Speed.y);
    }
    
}
