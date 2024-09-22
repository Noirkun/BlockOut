//フォント関連のソースファイル
#include "font.h"

//グローバル変数
AddFont addDot;    //ドットフォントを追加
Font fontDefault;	//デフォルトのフォント
Font fontDot;	    //ドットフォント
Font fontDotLarge;	//大きいドットフォント
Font fontDotSmall;	//小さいドットフォント

//フォントのインストール&作成
bool FontInit()
{
    //外部フォントのインストール
    addDot= FontInstall(FONT_PATH_DOT, FONT_NAME_DOT);
    if (!addDot.CanInstall)
    {
        return false;
    }

    //フォントデータを生成してハンドルで管理
        //デフォルトのフォント
    fontDefault = FontCreate(FONT_NAME_DEFAULT, FONT_SIZE_DEFAULT, FONT_THINCK_DEFAULT, FONT_TYPE_DEFAULT);
    if (fontDefault.Handle == -1)
    {
        return false;
    }

    //ドットフォント
    fontDot = FontCreate(addDot.FontName,24,1,FONT_TYPE_DEFAULT);
    if(fontDot.Handle == -1)
    {
        return false;
    }
    //大きいドットフォント
    fontDotLarge = FontCreate(addDot.FontName,64,1,FONT_TYPE_DEFAULT);
    if(fontDot.Handle == -1)
    {
        return false;
    }
    //小さいドットフォント
    fontDotSmall = FontCreate(addDot.FontName,18,1,FONT_TYPE_DEFAULT);
    if(fontDot.Handle == -1)
    {
        return false;
    }


}

///フォントのインストール
/// @param path フォントのパス
/// @param name フォントの名前
AddFont FontInstall(const char* path, const char* name)
{
    AddFont add;
    //フォントのパスと名前を設定
    strcpy_s(add.FontPath,sizeof(add.FontPath), path);
    strcpy_s(add.FontName,sizeof(add.FontName), name);

    //このソフト内で使うフォントをインストール
    if(!AddFontResourceEx(add.FontPath, FR_PRIVATE, NULL))
    {
        //インストール失敗の場合エラーメッセージを表示
        FontInstallErrMessage(add.FontPath);
        add.CanInstall = false;
    }
    else
    {
        //インストール成功
        add.CanInstall = true;
    }
    //フォントのインストール
    return add;
}

/// フォントのインストールエラーメッセージ
/// @param path フォントのパス
void FontInstallErrMessage(const char* path)
{
    //エラー用文字列
    char ErrStr[FONT_ERR_STR_MAX];

    //エラー用文字列の内容を空にする
    for (int i = 0; i < FONT_ERR_STR_MAX; i++)
    {
        ErrStr[i] = '\0';
    }

    //エラー内容を連結して生成
    sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, FONT_INSTALL_ERRCAP);

    MessageBox(GetMainWindowHandle(),    //ウィンドウのハンドル
        ErrStr,                          //エラーメッセージ
        FONT_INSTALL_ERRTITLE,           //エラータイトル
        MB_OK);                     //OKボタンのみ

    return;
}

/// フォントの作成
/// @param FontName フォントの名前
/// @param Size フォントのサイズ
/// @param Thick フォントの太さ
/// @param Type フォントの種類
Font FontCreate(const char* FontName, int Size, int Thick, int Type)
{
    Font font;
    strcpy_s(font.Name,sizeof(font.Name), FontName);
    font.Size = Size;
    font.Thick = Thick;
    font.Type = Type;

    //フォントの名前が違っているなどでフォントが作れない場合エラー
    if (!CheckFontName(font.Name))
    {
        FontCreateErrMessage(font); 
        font.Handle = -1;   //エラーの場合-1を返す
    }
    else
    {
        //フォントの作成
        font.Handle = CreateFontToHandle(font.Name, font.Size, font.Thick, font.Type);
    }
    return font;
}

/// フォントの作成エラーメッセージ
/// @param font フォントのインストール情報
void FontCreateErrMessage(Font font)
{
    //エラー用文字列
    char ErrStr[FONT_ERR_STR_MAX];

    //エラー用文字列の内容を空にする
    for (int i = 0; i < FONT_ERR_STR_MAX; i++)
    {
        ErrStr[i] = '\0';
    }

    //エラー内容を連結して生成
    sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", font.Name, FONT_CREATED_ERRCAP);

    MessageBox(GetMainWindowHandle(),    //ウィンドウのハンドル
        ErrStr,                          //エラーメッセージ
        FONT_CREATED_ERRTITLE,           //エラータイトル
        MB_OK);                     //OKボタンのみ

    return;
}

///フォントハンドルの削除
/// @param font フォントのインストール情報
void FontDelete(Font font)
{
    //フォントハンドルが有効なら
    if(font.Handle != -1)
    {
        //フォントデータの削除
        DeleteFontToHandle(font.Handle);
    }
    return;
}

///フォントのアンインストール
/// @param add フォントのインストール情報
void FontUnInstall(AddFont add)
{
    //フォントをインストールしたなら
    if (add.CanInstall)
    {
        //フォントのアンインストール
        RemoveFontResourceEx(add.FontPath, FR_PRIVATE, NULL);
    }
    return;
}

//フォントの削除&アンイストール
void FontEnd()
{
    //フォントの削除
    FontDelete(fontDefault);
    FontDelete(fontDot);
    FontUnInstall(addDot);

    return;
}




