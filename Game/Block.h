//ブロック崩し用のクラス
#pragma once
#include "DxLib.h"

//マクロ定義
constexpr int BLOCK_NUM_X = 13;	//ブロックの横の数
constexpr int BLOCK_NUM_Y = 3;	//ブロックの縦の数

//ブロックの構造体
typedef struct ST_Ract
{
    int  x;		//X座標
    int  y;		//Y座標
    int  w;		//幅
    int  h;		//高さ
    bool isAlive;	//生存フラグ

    RECT GetRect() const
    {
        RECT rc;
        rc.left = x;
        rc.top = y;
        rc.right = x + w;
        rc.bottom = y + h;

        return rc;
    }
}Ract;

class Block
{
    
public:
    Block();
    ~Block();

    //メンバ関数
    void Block_Init();  //ブロックに関する情報を初期化
    void Block_Cal();   //ブロックの計算
    void Block_Draw();  //ブロックの描画

    Ract GetBlock(int x, int y){return BlockArray[x][y];}	//ブロックの情報を取得
    Ract GetBar(){return bar;}	//バーの情報を取得

    void SetBarMove(bool isMove){isBarMove = isMove;}	//バーの操作可能フラグを設定
    
private:
    void HitBlockToBall(); //ボールとブロックの当たり判定
    void HitBarToBall();   //ボールとバーの当たり判定
    
    //ブロックの配列
    Ract BlockArray[BLOCK_NUM_X][BLOCK_NUM_Y];
    //バーの定義
    Ract bar;

    //バーの操作可能フラグ
    bool isBarMove = true;
    
};

//外部グローバル変数
extern Block block;