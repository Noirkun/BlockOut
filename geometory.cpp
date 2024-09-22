//幾何学（図形）処理のソースファイル

#include "geometory.h"
#include <cmath>

/// xとyの地点からPOINTを取得
/// @param x x座標
/// @param y y座標
POINT GetPoint(int x, int y)
{
    POINT pt;
    pt.x = x;
    pt.y = y;
    
    return pt;
}

/// POINTとPOINTの当たり判定
/// @param p1 1つ目のPOINT
/// @param p2 2つ目のPOINT
bool CollPointToPoint(POINT p1, POINT p2)
{
    //2つの点が同じ座標か
    if(p1.x == p2.x && p1.y == p2.y)
    {
        //当たっている
        return true;
    }

    //当たっていない
    return false;
}

/// 左上と右下の座標からRECTを取得
/// @param left 左上のx座標
/// @param top 左上のy座標
/// @param right 右下のx座標
/// @param bottom 右下のy座標
RECT GetRect(int left, int top, int right, int bottom)
{
    RECT rc;
    rc.left = left;
    rc.top = top;
    rc.right = right;
    rc.bottom = bottom;

    return rc;
}

/// RECTとRECTの当たり判定
/// @param r1 1つ目のRECT
/// @param r2 2つ目のRECT
bool CollRectToRect(RECT r1, RECT r2)
{
    if(r1.left<=r2.right
        && r1.right>=r2.left
        && r1.top<=r2.bottom
        && r1.bottom>=r2.top)
    {
        //当たっている
        return true;
    }
    //当たっていない
    return false;
    
}

/// RECTとPOINTの当たり判定
/// @param r RECTの情報
/// @param p POINTの情報
bool CollRectToPoint(RECT r, POINT p)
{
    if(r.left<=p.x
        && r.right>=p.x
        && r.top<=p.y
        && r.bottom>=p.y)
    {
        //当たっている
        return true;
    }
    
    //当たっていない
    return false;
}

/// xとyの地点からCIRCLEを取得
/// @param pt 中心座標
/// @param rad 半径
CIRCLE GetCircle(POINT pt, float rad)
{
    CIRCLE c;
    c.pt = pt;
    c.radius = rad;
    
    return c;
}

/// CIRCLEとCIRCLEの当たり判定
/// @param c1 1つ目のCIRCLE
/// @param c2 2つ目のCIRCLE
bool CollCircleToCircle(CIRCLE c1, CIRCLE c2)
{
    //三角形を作る
    float a=0;
    float b=0;
    float c=0;

    //2つの円の中心座標の差分
    a= c1.pt.x - c2.pt.x;
    b= c1.pt.y - c2.pt.y;
    //2つの円の中心座標の差分の長さ
    c= sqrt(a*a + b*b);

    //半径の和が中心座標の差分より小さいか
    if (c<=c1.radius + c2.radius)
    {
        //当たっている
        return true;
    }
    
    //当たっていない
    return false;
    
}

/// CIRCLEとPOINTの当たり判定
/// @param circle CIRCLEの情報
/// @param p POINTの情報
bool CollCircleToPoint(CIRCLE circle, POINT p)
{
    //三角形を作る
    float a=0;
    float b=0;
    float c=0;

    //2つの円の中心座標の差分
    a= circle.pt.x - p.x;
    b= circle.pt.y - p.y;
    c= sqrt(a*a + b*b);

    //半径の和が中心座標の差分より小さいか
    if (c<=circle.radius)
    {
        //当たっている
        return true;
    }
    
    //当たっていない
    return false;
}

/// 円の描画
/// @param circle 描画する円の情報
/// @param color 色
/// @param fill 塗りつぶし
void DrawEllipse(CIRCLE circle, unsigned int color, bool fill)
{
    DrawCircle(circle.pt.x, circle.pt.y, circle.radius, color, fill);
}

/// RECTとCIRCLEの当たり判定
/// @param r RECTの情報
/// @param c CIRCLEの情報
/// @return 当たっているかどうか
bool CollRectToCircle(RECT r, CIRCLE c)
{
    //円の中心が矩形の中にあるか
    if(r.left<=c.pt.x
        && r.right>=c.pt.x
        && r.top<=c.pt.y
        && r.bottom>=c.pt.y)
    {
        //当たっている
        return true;
    }

    //当たっていない
    return false;
    
}



