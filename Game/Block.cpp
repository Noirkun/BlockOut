//ブロック崩しのブロック部分の処理
#include "Block.h"

#include "Ball.h"
#include "../System/key.h"
#include "../System/music.h"
#include "../geometory.h"
#include "../game.h"

Block block;

Block::Block()
{
    Block_Init();
}

Block::~Block()
{
}

//ブロックに関する情報を初期化
void Block::Block_Init()
{
    //ブロックの初期化
    for(int y=0;y<BLOCK_NUM_Y;y++)
    {
        for(int x=0;x<BLOCK_NUM_X;x++)
        {
            BlockArray[x][y]={ x * 100, 100 + y * 50, 100, 50, true };
        }
    }

    //バーの初期化
    bar = { (GAME_WIDTH-200) / 2, 700, 200, 30};

    //バーの操作可能フラグ
    isBarMove = true;
    
}

//ブロックの計算
void Block::Block_Cal()
{
    //isBarMoveがtrueの時バーの移動を行う
    if(isBarMove)
    {
        //KeyDown()でのバーの移動
        if(KeyDown(KEY_INPUT_LEFT)&&bar.x>0)
        {
            bar.x -= 10;
        }
        if(KeyDown(KEY_INPUT_RIGHT)&&bar.x<GAME_WIDTH-bar.w)
        {
            bar.x += 10;
        }
    }
    
    //ボールとブロックの当たり判定
    HitBlockToBall();
    //ボールとバーの当たり判定
    HitBarToBall();
    
}

//ブロックの描画関数
void Block::Block_Draw()
{
    //ブロックの描画
    for (int y = 0; y < BLOCK_NUM_Y; y++)
    {
        for (int x = 0; x < BLOCK_NUM_X; x++)
        {
            if (BlockArray[x][y].isAlive == true)
            {
                //格段のブロック
                switch (y)
                {
                case 0: //１段目
                    //色のついたブロックの描画
                    DrawBox(BlockArray[x][y].x, BlockArray[x][y].y,
                    BlockArray[x][y].x + BlockArray[x][y].w, BlockArray[x][y].y + BlockArray[x][y].h,
                    GetColor(255, 0, 0), TRUE);
                    break;
                case 1: //２段目
                    //色のついたブロックの描画
                    DrawBox(BlockArray[x][y].x, BlockArray[x][y].y,
                    BlockArray[x][y].x + BlockArray[x][y].w, BlockArray[x][y].y + BlockArray[x][y].h,
                    GetColor(0, 255, 0), TRUE);
                    break;
                case 2: //３段目
                    //色のついたブロックの描画
                    DrawBox(BlockArray[x][y].x, BlockArray[x][y].y,
                    BlockArray[x][y].x + BlockArray[x][y].w, BlockArray[x][y].y + BlockArray[x][y].h,
                    GetColor(0, 0, 255), TRUE);
                    break;
                default:
                    break;
                }

                //ブロックの網目
                DrawBox(BlockArray[x][y].x, BlockArray[x][y].y,
                    BlockArray[x][y].x + BlockArray[x][y].w, BlockArray[x][y].y + BlockArray[x][y].h,
                    GetColor(255, 255, 255), FALSE);

                if(GAME_DEBUG_MODE)
                {
                    //座標（デバック用）
                    DrawFormatString(BlockArray[x][y].x, BlockArray[x][y].y,
                        GetColor(255, 255, 255), "(%d,%d)", BlockArray[x][y].x, BlockArray[x][y].y);
                }
            }

        }
    }

    //バーの描画
    DrawBox(bar.x, bar.y, bar.x + bar.w, bar.y + bar.h, GetColor(255, 255, 255), TRUE);

    if(GAME_DEBUG_MODE)
    {
        //バー座標（デバック用）
        DrawFormatString(bar.x, bar.y, GetColor(0, 0, 0), "(%d,%d)", bar.x, bar.y);
    }
}

//ボールとブロックの当たり判定
void Block::HitBlockToBall()
{
    //ボールとブロックの当たり判定
    for (int y = 0; y < BLOCK_NUM_Y; y++)
    {
        for (int x = 0; x < BLOCK_NUM_X; x++)
        {
            if (BlockArray[x][y].isAlive == true)
            {
                if (CollRectToCircle(BlockArray[x][y].GetRect(),ball.GetCircle()) == true)
                {
                    //ボールのスピードを反転
                    ball.SetSpeed(ball.GetSpeed().x,ball.GetSpeed().y * -1);
                    //ブロックを消す
                    BlockArray[x][y].isAlive = false;
                    //ブロックの破壊音
                    MusicPlay(hitSE_01);
                    break;
                }
            }
        }
    }
}

//ボールとバーの当たり判定
void Block::HitBarToBall()
{
    if(CollRectToCircle(bar.GetRect(),ball.GetCircle())==true)
    {
        //SEの再生
        MusicPlay(hitSE_01);
        
        //バーの中心からの距離によってボールのスピードを変更
        int x = (ball.GetCircle().pt.x - (bar.x + bar.w / 2)) / 10;
        ball.SetSpeed(x, ball.GetSpeed().y*(-1));
        
    }
}

