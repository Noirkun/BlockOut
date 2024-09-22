#pragma once

#include "DxLib.h"
#include "font.h"
#include "../geometory.h"
#include "mouse.h"

//色の構造体
typedef struct ST_Color
{
    int r;
    int g;
    int b;    
}Color;

//ボタンのクラス
class Button
{
public:
    //コンストラクタ
    Button(RECT rect,Color buttonColor,const TCHAR* text,Font font=fontDotSmall);

    void SetText(const TCHAR* text,Font font=fontDotSmall);    //テキストの設定
    void SetPosition(RECT rect){button=rect;}    //ボタンの位置の設定
    void Button_Draw();     //ボタンの描画
    bool CollButtonToMouseClick(int Mouse_Input);    //ボタンのクリックの処理
    bool IsOnceClick(){return isOnceClick;}  //一度クリックされたか
    void ResetOnceClick(){isOnceClick=false;}  //一度クリックされたかのリセット
    void SetActive(bool isActive){this->isActive=isActive;}  //ボタンのアクティブ設定

private:
    RECT button;        //ボタンの位置
    Color buttonColor;  //ボタンの色
    const TCHAR* text;  //ボタンのテキスト
    Font font;          //フォント

    bool isActive;      //アクティブか
    bool isOnceClick;       //一度クリックされたか
    
};
