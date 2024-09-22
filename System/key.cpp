//キーボード処理のソースファイル

#include "key.h"

//グローバル変数
//キーを押したフレーム数
int NowKeyPressFrame[KEY_KIND_MAX];

//一つ前のキーを押しているフレーム数
int OldKeyPressFrame[KEY_KIND_MAX];

//キーの初期化
void KeyInit()
{
    //配列の初期化
    for (int i = 0; i < KEY_KIND_MAX; i++)
    {
        NowKeyPressFrame[i] = 0;
        OldKeyPressFrame[i] = 0;
    }
    return;
}

//キー更新
void KeyUpdate()
{
    //一時的に保持するキー情報
    char KeyState[KEY_KIND_MAX];

    //すべてのキー情報を一度に取得
    GetHitKeyStateAll(&KeyState[0]);

    //キー情報を更新
    for (int i = 0; i < KEY_KIND_MAX; i++)
    {

        //一つ前のキーを入力を保存
        OldKeyPressFrame[i] = NowKeyPressFrame[i];
        
        //キーが押されていたら
        if (KeyState[i] == 1)
        {
            //押されたフレーム数をカウントアップ
            NowKeyPressFrame[i]++;
        }
        else if (KeyState[i] == 0)
        {
            //押されていないならフレーム数をリセット
            NowKeyPressFrame[i] = 0;
        }
    }
    
    return;
    
}

/// キーが押されたか
/// @param Key DXライブラリのキーコード
/// @return bool 押されていたらtrue
bool KeyDown(int Key)
{
    //現在押されているキーのフレーム数が0より上なら
    if (NowKeyPressFrame[Key] > 0)
    {
        //押されているなら
        return true;
    }

    //押されていないなら
    return false; 
}

/// キーがクリックされたか
/// @param Key DXライブラリのキーコード
/// @return bool クリックされたらtrue
bool KeyClick(int Key)
{
    //現在押されておらず かつ 一つ前のフレームで押されていたら
    if (NowKeyPressFrame[Key] == 0 && OldKeyPressFrame[Key] > 0)
    {
        //クリックされたなら
        return true;
    }
    
    //押されていないなら
    return false;
}

/// キーを押したフレーム数
/// @param Key DXライブラリのキーコード
/// @return 押されてるフレーム数
int KeyPressFrame(int Key)
{
    // 押されているフレーム数を返す
    return NowKeyPressFrame[Key];
}


