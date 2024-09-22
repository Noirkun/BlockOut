//マウス処理のソースファイル

#include "mouse.h"
#include "../game.h"
#include "../geometory.h"

//グローバル変数
POINT NowPoint;	//現在のマウス座標
POINT OldPoint;	//以前のマウス座標

int NowMousePressFrame[MOUSE_KIND_MAX];	//マウスを押したフレーム数
int OldMousePressFrame[MOUSE_KIND_MAX];	//一つ前のマウスを押したフレーム数

int NowMouseWheel;	//現在のマウスホイールの回転量
int OldMouseWheel;	//以前のマウスホイールの回転量

//マウスのボタンコードとフレーム数を管理している配列の要素数を紐づける
int MouseCodeIndex[MOUSE_KIND_MAX] =
{
    MOUSE_INPUT_LEFT,   //配列の要素数0にはマウスのボタン情報の0x0001を入れる
    MOUSE_INPUT_RIGHT,  //配列の要素数1にはマウスのボタン情報の0x0002を入れる
    MOUSE_INPUT_MIDDLE, //配列の要素数2にはマウスのボタン情報の0x0004を入れる
    MOUSE_INPUT_4,      //配列の要素数3にはマウスのボタン情報の0x0008を入れる
    MOUSE_INPUT_5,      //配列の要素数4にはマウスのボタン情報の0x0010を入れる
    MOUSE_INPUT_6,      //配列の要素数5にはマウスのボタン情報の0x0020を入れる
    MOUSE_INPUT_7,      //配列の要素数6にはマウスのボタン情報の0x0040を入れる
    MOUSE_INPUT_8       //配列の要素数7にはマウスのボタン情報の0x0080を入れる
};


//Now系の変数の値をOld系の変数に入れる
void MouseNowIntoOld()
{
    //現在のマウス座標を以前のマウス座標に入れる
    OldPoint = NowPoint;

    //現在のフレーム数を一つ前のフレーム数に入れる
    for (int i = 0; i < MOUSE_KIND_MAX; i++)
    {
        OldMousePressFrame[i] = NowMousePressFrame[i];
    }

    //現在のホイールの回転量を以前のホイールの回転量に入れる
    OldMouseWheel = NowMouseWheel;
}

///マウスのボタンコードを配列の要素に変換
/// @param Code DXライブラリのマウスコード
int MouseCodeToIndex(int Code)
{
    //マウスのボタンコードを配列の要素に変換
    for (int i = 0; i < MOUSE_KIND_MAX; i++)
    {
        //マウスコードが紐づけされているなら
        if (Code == MouseCodeIndex[i])
        {
            //配列の要素数を返す
            return i;
        }
    }

    //マウスコードがないならエラー値を返す
    return MOUSE_CODE_ERR_INDEX;
}

// マウスの初期化
void MouseInit()
{
    //マウス位置の初期化
    NowPoint.x = 0;
    NowPoint.y = 0;

    //マウスボタンの初期化
    for ( int i = 0; i < MOUSE_KIND_MAX; i++)
    {
        NowMousePressFrame[i] = 0;
    }

    //マウスホイールの初期化
    NowMouseWheel = 0;

    //Old系も初期化する
    MouseNowIntoOld();
    
}

//マウス更新
void MouseUpdate()
{
    //マウスの情報をすべて取得
    int Input;

    //現在の情報を以前の情報として保存
    MouseNowIntoOld();
    
    
     int GetX,GetY;  //取得用のXY座標
    
    //現在のマウスのクライアント座標の位置を取得
    GetMousePoint(&GetX, &GetY);

    //マウスの座標に入れる
    NowPoint = GetPoint(GetX,GetY);
    
    //もしマウスの座標がゲーム画面外にあるなら、ゲーム内に収める。
    if(NowPoint.x < 0){NowPoint.x = 0;} //左
    if(NowPoint.y < 0){NowPoint.y = 0;} //上
    if(NowPoint.x > GAME_WIDTH){NowPoint.x = GAME_WIDTH;}   //右
    if(NowPoint.y > GAME_HEIGHT){NowPoint.y = GAME_HEIGHT;} //下

    //マウスのボタン情報を一気に取得
    Input = GetMouseInput();

    for (int i=0;i<MOUSE_KIND_MAX;i++)
    {
        //マウスのボタンが押されていたら
        if ((Input & MouseCodeIndex[i]) == MouseCodeIndex[i])
        {
            //現在押されているボタンのフレーム数をカウントアップ
            NowMousePressFrame[i]++;
        }
        else if ((Input & MouseCodeIndex[i]) != MouseCodeIndex[i])
        {
            //押されていないならフレーム数をリセット
            NowMousePressFrame[i] = 0;
        }
    }

    //マウスホイールの回転量を取得
    NowMouseWheel = GetMouseWheelRotVol();
    
    return;
    
}


/// マウスが押されたか
/// @param Mouse_Input DXライブラリのマウスコード
/// @return 押されたならtrue
bool MouseDown(int Mouse_Input)
{
    //マウスのボタンコードを配列の要素に変換
    int index=MouseCodeToIndex(Mouse_Input);
    
    //実在するマウスコードなら
    if (index != MOUSE_CODE_ERR_INDEX)
    {
        if(NowMousePressFrame[index] > 0)
        {
            //押されているなら
            return true;
        }
    }
    
    //押されていないなら
    return false; 
}

/// マウスがクリックされたか
/// @param Mouse_Input DXライブラリのマウスコード
/// @return クリックされたならtrue
bool MouseClick(int Mouse_Input)
{
    //マウスのボタンコードを配列の要素に変換
    int index=MouseCodeToIndex(Mouse_Input);
    
    //実在するマウスコードなら
    if (index != MOUSE_CODE_ERR_INDEX)
    {
        //現在押されておらず かつ 一つ前のフレームで押されていたら
        if(NowMousePressFrame[index] == 0
            && OldMousePressFrame[index] > 0)
        {
            //クリックされたなら
            return true;
        }
    }
    
    //押されていないなら
    return false; 
}


/// マウスを押したフレーム数
/// @param Mouse_Input DXライブラリのマウスコード
/// @return マウスを押したフレーム数
int MousePressFrame(int Mouse_Input)
{
    //マウスのボタンコードを配列の要素に変換
    int index=MouseCodeToIndex(Mouse_Input);
    
    //実在するマウスコードなら
    if (index != MOUSE_CODE_ERR_INDEX)
    {
        // 押されているフレーム数を返す
        return NowMousePressFrame[index];
    }
    
    return 0;
}

//マウスの現在の座標を取得
POINT GetPointMouse()
{
    return NowPoint;
}

//マウスの以前の座標を取得
POINT GetOldPointMouse()
{
    return OldPoint;
}

//マウスの以前と現在の差分座標を取得
POINT GetDiffPointMouse()
{
    POINT diff;
    diff.x = OldPoint.x-NowPoint.x;
    diff.y = OldPoint.y-NowPoint.y;
    return diff;
}

//マウスホイールの回転量を取得
int GetMouseWheel()
{
    return NowMouseWheel;
}

/// RECTとマウスの座標の当たり判定
/// @param r 判定元のRECT
bool CollRectToMousePoint(RECT r)
{
    // マウスとRECTの当たり判定の結果を返す
    return CollRectToPoint(r,NowPoint);
    
}

//画面とマウスの座標の当たり判定
bool CollWindowToMousePoint()
{
    return  CollRectToMousePoint(GetGameWindow());
}

///RECTの何処かでマウスのボタンが押されたか
/// @param r 判定元のRECT
/// @param Mouse_Input DXライブラリのマウスコード
bool CollRectToMouseDown(RECT r, int Mouse_Input)
{
    // マウスが押されているかつ、RECTとマウスの座標の当たり判定がtureなら
    if(CollRectToMousePoint(r) && MouseDown(Mouse_Input))
    {
        // 矩形内で押している
        return true;
    }

    // 矩形内で押していない
    return false;
}

/// RECTの何処かでマウスのボタンがクリックされたか
/// @param r 判定元のRECT
/// @param Mouse_Input DXライブラリのマウスコード
bool CollRectToMouseClick(RECT r, int Mouse_Input)
{
    // マウスが押されているかつ、RECTとマウスの座標の当たり判定がtureなら
    if(CollRectToMousePoint(r) && MouseClick(Mouse_Input))
    {
        // 矩形内でクリックしている
        return true;
    }

    // 矩形内でクリックしていない
    return false;
}

/// 画面の何処かでマウスのボタンが押されたか
/// @param Mouse_Input DXライブラリのマウスコード
bool CollWindowToMouseDown(int Mouse_Input)
{
    // マウスが押されているかつ、画面とマウスの座標の当たり判定がtureなら
    if(CollWindowToMousePoint()&& MouseDown(Mouse_Input))
    {
        // 画面内で押している
        return true;
    }

    // 画面内で押していない
    return false;
}

/// 画面の何処かでマウスのボタンがクリックされたか
/// @param Mouse_Input DXライブラリのマウスコード
bool CollWindowToMouseClick(int Mouse_Input)
{
    // マウスが押されているかつ、RECTとマウスの座標の当たり判定がtureなら
    if(CollWindowToMousePoint() && MouseClick(Mouse_Input))
    {
        // 画面内でクリックしている
        return true;
    }

    // 画面内でクリックしていない
    return false;
}

///円とマウスの点が当たっているか
/// @param c 判定元の円
bool CollCircleToMousePoint(CIRCLE c)
{
    //円と点の当たり判定の結果を返す
    return CollCircleToPoint(c,NowPoint);
}

/// 円の何処かでマウスのボタンが押されたか
/// @param c 判定元の円
/// @param Mouse_Input DXライブラリのマウスコード
bool CollCircleToMouseDown(CIRCLE c, int Mouse_Input)
{
    // マウスが押されているかつ、画面とマウスの座標の当たり判定がtureなら
    if(CollCircleToPoint(c,NowPoint)&& MouseDown(Mouse_Input))
    {
        // 画面内で押している
        return true;
    }

    // 画面内で押していない
    return false;
}

/// 円の何処かでマウスのボタンがクリックされたか
/// @param c 判定元の円
/// @param Mouse_Input DXライブラリのマウスコード
bool CollCircleToMouseClick(CIRCLE c, int Mouse_Input)
{
    // マウスが押されているかつ、画面とマウスの座標の当たり判定がtureなら
    if(CollCircleToPoint(c,GetPoint(NowPoint.x,NowPoint.y))&& MouseClick(Mouse_Input))
    {
        // 画面内で押している
        return true;
    }

    // 画面内で押していない
    return false;
}



