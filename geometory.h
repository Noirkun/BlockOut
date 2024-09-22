//幾何学（図形）処理のヘッダーファイル
#pragma once

#include  "DxLib.h"


//構造体
typedef struct ST_CIRCLE
{
    POINT pt;              //中心座標
    float radius = 0.0f;   //円の半径
}CIRCLE;

//外部プロントタイプ宣言

//点関係
extern POINT GetPoint(int x, int y);	//xとyの地点からPOINTを取得
extern bool CollPointToPoint(POINT p1, POINT p2);	//POINTとPOINTの当たり判定

//矩形関係
extern RECT GetRect(int left, int top, int right, int bottom);	//左上と右下の座標からRECTを取得
extern bool CollRectToRect(RECT r1, RECT r2); 	//RECTとRECTの当たり判定
extern bool CollRectToPoint(RECT r, POINT p);	//RECTとPOINTの当たり判定

//円関係
extern CIRCLE GetCircle(POINT pt, float rad);	//CIRCLE型を取得
extern bool CollCircleToCircle(CIRCLE c1, CIRCLE c2);	//円と円が当たっているか
extern bool CollCircleToPoint(CIRCLE c, POINT p);	//円と点が当たっているか
extern void DrawEllipse(CIRCLE circle, unsigned int color, bool fill);	//円を描画
extern bool CollRectToCircle(RECT r, CIRCLE c);	//RECTとCIRCLEが当たっているか

