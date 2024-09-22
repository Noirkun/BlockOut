//フォント関連のヘッダーファイル
#pragma once

#include  "DxLib.h"

//フォントのパスと名前
constexpr const char* FONT_PATH_DOT = "./font/BestTen-DOT.otf";	//フォントのパス
constexpr const char* FONT_NAME_DOT = "ベストテンDOT";			//フォントの名前

//内部のフォント
constexpr const char* FONT_NAME_MSMINTYO = "ＭＳ 明朝";	        //デフォルトのフォント名

//デフォルトのフォント
constexpr auto FONT_NAME_DEFAULT = FONT_NAME_MSMINTYO;	//デフォルトのフォント
constexpr int FONT_SIZE_DEFAULT = 24;	                        //デフォルトのフォントサイズ
constexpr int FONT_THINCK_DEFAULT = 1;	                        //デフォルトのフォントの太さ
constexpr auto FONT_TYPE_DEFAULT = DX_FONTTYPE_ANTIALIASING;	//デフォルトのフォントの種類

//文字列の長さ
constexpr int FONT_NAME_STR_MIX = 256;	//フォント名の長さ
constexpr int FONT_ERR_STR_MAX = 512;	//エラーメッセージの長さ

//エラー
constexpr auto FONT_INSTALL_ERRCAP = "がインストールできません";
constexpr auto FONT_INSTALL_ERRTITLE = "フォントのインストールエラー";
constexpr auto FONT_CREATED_ERRCAP = "が作成できません";
constexpr auto FONT_CREATED_ERRTITLE = "フォントの作成エラー";

//構造体
typedef struct ST_AddFont
{
    char FontPath[FONT_NAME_STR_MIX];	//フォントのパス
    char FontName[FONT_NAME_STR_MIX];	//フォントの名前
    bool CanInstall = false;	        //インストールできたか
    
} AddFont;

typedef struct ST_FONT
{
    int Handle;                     //フォントのハンドル
    int Size;	                    //フォントのサイズ
    int Thick;	                    //フォントの太さ
    int Type;	                    //フォントの種類
    char Name[FONT_NAME_STR_MIX];	//フォント名 
    
} Font;

//外部グローバル変数
extern AddFont addDot;      //ドットフォントを追加
extern Font fontDefault;	//デフォルトのフォント
extern Font fontDot;	    //ドットフォント
extern Font fontDotLarge;	//大きいドットフォント
extern Font fontDotSmall;	//小さいドットフォント

//外部プロトタイプ宣言
extern bool FontInit();	        //フォントのインストール&作成
extern AddFont FontInstall(const char* path, const char* name);	            //フォントのインストール
extern void FontInstallErrMessage(const char* path);	                    //フォントのインストールエラーメッセージ
extern Font FontCreate(const char* FontName, int Size, int Thick, int Type);	//フォントハンドルの作成
extern void FontCreateErrMessage(Font font);	//フォントの作成エラーメッセージ
extern void FontDelete(Font font);	            //フォントハンドルの削除
extern void FontUnInstall(AddFont add);	        //フォントのアンインストール
extern void FontEnd();	                        //フォントの削除&アンイストール