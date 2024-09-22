//キーボード処理のヘッダーファイル
#pragma once

#include  "DxLib.h"

//マクロ定義
constexpr int KEY_KIND_MAX = 256;	//キーの種類の最大数

extern void KeyInit();  	        //キー初期化
extern void KeyUpdate();            //キー更新
extern bool KeyDown(int Key);	    //キーが押されたか
extern bool KeyClick(int Key);      //キーがクリックされたか
extern int  KeyPressFrame(int Key);	//キーを押したフレーム数
