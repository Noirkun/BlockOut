//BGM・SE関連のヘッダーファイル
#pragma once

#include  "DxLib.h"

//エラー
constexpr const char* MUSIC_LOAD_ERR_CAP = "が読み込めません";
constexpr const char* MUSIC_LOAD_ERR_TITLE = "音楽の読み込みエラー";

//インライン関数
inline int GetVolume(int volume){return 255*volume/100;}	//ボリュームをMIN:0-MAX:255に変換

//文字列の長さ
constexpr int MUSIC_PATH_STR_MAX = 256;	//音楽のパスの長さ
constexpr int MUSIC_ERR_STR_MAX = 512;	//エラーメッセージの長さ

//デフォルトの音量
constexpr int MUSIC_VOLUME_BGM = 40;	//BGMの音量
constexpr int MUSIC_VOLUME_SE = 70;	//SEの音量

//音楽ファイルパス
//BGM
constexpr const char* MUSIC_PATH_TITLE_BGM  = "./music/BGM/BGM01.mp3";	//タイトルBGMのパス
constexpr const char* MUSIC_PATH_PLAY_BGM   = "./music/BGM/BGM02.mp3";	//プレイBGMのパス
constexpr const char* MUSIC_PATH_RESULT_BGM = "./music/BGM/BGM03.mp3";	//リザルトBGMのパス
//SE
constexpr const char* MUSIC_PATH_BUTTON_SE = "./music/SE/SE03.mp3";	//ボタンSEのパス
constexpr const char* MUSIC_PATH_Hit_SE_01 = "./music/SE/SE01.mp3";	//ヒット時のSEのパス
constexpr const char* MUSIC_PATH_Hit_SE_02 = "./music/SE/SE02.mp3";	//ヒット時のSEのパス

//構造体
typedef struct ST_MUSIC
{
    int Handle= -1;	                        //音楽のハンドル
    int Volume= -1;	                        //音楽の音量
    char Path[MUSIC_PATH_STR_MAX];  	//音楽のパス
    bool IsPlayStart = true;	        //停止後は最初から再生するか
    int PlayType = DX_PLAYTYPE_BACK;	//再生タイプ

    int FadeInMillTime = 0;	            //フェードイン時間
    int FadeOutMillTime = 0;	        //フェードアウト時間
    int FadeInMillTimeMax = 0;	        //フェードイン時間の最大値
    int FadeOutMillTimeMax = 0;	        //フェードアウト時間の最大値
    bool FadeInStartFlg = false;	    //フェードイン開始フラグ
    bool FadeOutStartFlg = false;	    //フェードアウト開始フラグ
    
} Music;

//外部グローバル変数
//BGM
extern Music titleBGM;	//タイトルBGM
extern Music playBGM;	//プレイBGM
extern Music resultBGM;	//リザルトBGM
//SE
extern Music buttonSE;	//ボタンSE
extern Music hitSE_01;	//ヒット時のSE
extern Music hitSE_02;	//ヒット時のSE

//外部プロトタイプ宣言
extern bool MusicInit();	//音楽の初期化(読み込み・ハンドル生成)
extern void MusicEnd();	    //音楽の終了
extern void MusicLoadErrMessage( const char* path);	//音楽の読み込みエラーメッセージ

extern Music MusicLoad(const char* path, int volume, int playType);	//音楽の読み込み
extern void MusicPlay(Music music);	//音楽の再生
extern void MusicPause(Music* music);	//音楽の一時停止
extern void MusicStop(Music* music);	//音楽の停止
extern void MusicDelete(Music music);	//音楽の削除

extern void ChangeMusicVolume(Music* music, int volume);	//音楽の音量変更

extern bool FadeInPlayMusic(Music* music, int fadeInMillTime);	//フェードイン再生(1000=1秒)
extern bool FadeOutPlayMusic(Music* music, int fadeOutMillTime);	//フェードアウト開始(1000=1秒)
