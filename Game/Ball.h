//ボールのヘッダーファイル
#pragma once

#include "DxLib.h"
#include "../geometory.h"

constexpr int BALL_SIZE = 10;    //ボールのサイズ

//ボールのクラス
class Ball
{
public:

    Ball();     //コンストラクタ
    ~Ball();    //デストラクタ

    void Ball_Init();    //ボールの初期化
    void Ball_Cal();     //ボールの計算
    void Ball_Draw();    //ボールの描画

    CIRCLE GetCircle(){return Circle;}  //ボールの円を取得
    POINT GetSpeed(){return Speed;}     //ボールのスピードを取得

    void SetCircle(CIRCLE circle){this->Circle = circle;}   //ボールの円を設定
    void SetSpeed(POINT speed){Speed = speed;}              //ボールのスピードを設定
    void SetSpeed(int x,int y){Speed = {x,y};}            //ボールのスピードを設定

private:
    CIRCLE Circle;  //ボールの円
    POINT Speed;    //ボールのスピード
    
};

//外部のグローバル変数
extern Ball ball;



