//マウス処理のヘッダーファイル
#pragma once

#include  "DxLib.h"
#include "../geometory.h"

//マクロ定義
constexpr int MOUSE_KIND_MAX = 8;	//マウスのボタン種類
constexpr int MOUSE_CODE_ERR_INDEX = 999;	//マウスコードを変換した要素数のエラー値

//外部のプロトコル宣言
extern void MouseNowIntoOld();	                //Now???系の変数の値をOld???系の変数に入れる
extern int MouseCodeToIndex(int Code);	        //マウスのボタンコードを配列の要素に変換

extern void MouseInit();  	                    //マウス初期化
extern void MouseUpdate();                      //マウス更新
extern bool MouseDown(int Mouse_Input);	        //マウスが押されたか
extern bool MouseClick(int Mouse_Input);        //マウスがクリックされたか
extern int  MousePressFrame(int Mouse_Input);	//マウスを押したフレーム数

extern POINT GetPointMouse();              //マウスの現在の座標を取得
extern POINT GetOldPointMouse();           //マウスの以前の座標を取得
extern POINT GetDiffPointMouse();          //マウスの以前と現在の差分座標を取得
extern int GetMouseWheel();                     //マウスホイールの回転量を取得

//RECT関係
extern bool CollRectToMouseDown(RECT r, int Mouse_Input);	//RECTの何処かでマウスのボタンが押されたか
extern bool CollRectToMouseClick(RECT r, int Mouse_Input);	//RECTの何処かでマウスのボタンがクリックされたか

//画面関係
extern bool CollWindowToMousePoint();	                    //画面とマウスの座標の当たり判定
extern bool CollWindowToMouseDown(int Mouse_Input);         //画面の何処かでマウスのボタンが押されたか
extern bool CollWindowToMouseClick(int Mouse_Input);        //画面の何処かでマウスのボタンがクリックされたか

// 円関係
extern bool CollCircleToMousePoint(CIRCLE c);	            //円とマウスの点が当たっているか
extern bool CollCircleToMouseDown(CIRCLE c, int Mouse_Input);	//円の何処かでマウスのボタンが押されたか
extern bool CollCircleToMouseClick(CIRCLE c, int Mouse_Input);	//円の何処かでマウスのボタンがクリックされたか
