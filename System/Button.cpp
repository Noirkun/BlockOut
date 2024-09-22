#include "Button.h"

#include "music.h"

/// ボタンの初期化
/// @param rect ボタンのサイズ
/// @param buttonColor ボタンの色
/// @param text ボタンに表示する文字
/// @param font 使うフォント
Button::Button(RECT rect,Color buttonColor,const TCHAR* text,Font font):button(rect),buttonColor(buttonColor),text(text),font(font)
{
    isActive=true;
    isOnceClick=false;
}

/// テキストの設定
/// @param text 表示する文字
/// @param font 使うフォント
void Button::SetText(const TCHAR* text, Font font)
{
    if(font.Handle)
    {
        // テキストの幅と高さを取得
        int textWidth = GetDrawStringWidthToHandle(text, _tcslen(text), font.Handle);
        int textHeight = GetFontSizeToHandle(font.Handle);

        // テキストの位置を計算（ボタンの中央に配置）
        int textX = button.left + (button.right - button.left - textWidth) / 2;
        int textY = button.top + (button.bottom - button.top - textHeight) / 2;

        // テキストを描画
        DrawFormatStringToHandle(textX, textY, GetColor(255, 255, 255), font.Handle, "%s", text);
    }
}

//ボタンの描画
void Button::Button_Draw()
{
    //ボタンの位置と色を設定
    DrawBox(button.left, button.top, button.right, button.bottom, GetColor(buttonColor.r,buttonColor.g,buttonColor.b), TRUE);

    //テキストの設定
    SetText(text,font);
}

/// マウスボタンでボタンがクリックされたか
/// @param Mouse_Input 入力されるキー
/// @return Mouse_Inputが押されたかどうか
bool Button::CollButtonToMouseClick(int Mouse_Input)
{
    if(!isActive)
    {
        return false;
    }
    //ボタンがクリックされたか
    if(CollRectToMouseClick(button,Mouse_Input))
    {
        // クリックSEを再生
        MusicPlay(buttonSE);

        isOnceClick = true;
        //クリックされた
        return true;
    }
    //クリックされていない
    return false;
}

