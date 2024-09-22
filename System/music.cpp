#include "music.h"
#include "fps.h"

//グローバル変数
Music titleBGM;	//タイトルBGM
Music playBGM;	//プレイBGM
Music resultBGM;	//リザルトBGM
//SE
Music buttonSE;	//ボタンSE
Music hitSE_01;	//ヒット時のSE
Music hitSE_02;	//ヒット時のSE

//音楽の初期化(読み込み・ハンドル生成)
bool MusicInit()
{
    //BGM
    titleBGM = MusicLoad(MUSIC_PATH_TITLE_BGM, MUSIC_VOLUME_BGM, DX_PLAYTYPE_LOOP);
    if (titleBGM.Handle == -1)
    {
        return false;
    }

    playBGM = MusicLoad(MUSIC_PATH_PLAY_BGM, MUSIC_VOLUME_BGM, DX_PLAYTYPE_LOOP);
    if (playBGM.Handle == -1)
    {
        return false;
    }

    resultBGM = MusicLoad(MUSIC_PATH_RESULT_BGM, MUSIC_VOLUME_BGM, DX_PLAYTYPE_LOOP);
    if (resultBGM.Handle == -1)
    {
        return false;
    }

    //SE
    buttonSE = MusicLoad(MUSIC_PATH_BUTTON_SE, MUSIC_VOLUME_SE, DX_PLAYTYPE_BACK);
    if (buttonSE.Handle == -1)
    {
        return false;
    }
    hitSE_01 = MusicLoad(MUSIC_PATH_Hit_SE_01, MUSIC_VOLUME_SE, DX_PLAYTYPE_BACK);
    if (hitSE_01.Handle == -1)
    {
        return false;
    }
    hitSE_02 = MusicLoad(MUSIC_PATH_Hit_SE_02, MUSIC_VOLUME_SE, DX_PLAYTYPE_BACK);
    if (hitSE_02.Handle == -1)
    {
        return false;
    }
    
    return true;
}

//音楽の終了
void MusicEnd()
{
    MusicDelete(titleBGM);
    MusicDelete(playBGM);
    MusicDelete(resultBGM);
    MusicDelete(buttonSE);
    MusicDelete(hitSE_01);
    MusicDelete(hitSE_02);
}

/// 音楽の読み込みエラーメッセージ
/// @param path ファイルのパス
void MusicLoadErrMessage(const char* path)
{
    //エラーメッセージ用文字列
    char ErrStr[MUSIC_ERR_STR_MAX];

    //エラーメッセージ用文字列の内容を空にする
    for (int i = 0; i < MUSIC_ERR_STR_MAX; i++)
    {
        ErrStr[i] = '\0';
    }

    //エラーメッセージ内容を連結して生成
    sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, MUSIC_LOAD_ERR_CAP);

    //エラーメッセージ表示
    MessageBox(
        GetMainWindowHandle(),    //ウィンドウのハンドル
        ErrStr,                   //エラーメッセージ
        MUSIC_LOAD_ERR_TITLE,     //エラータイトル
        MB_OK);              //OKボタンのみ
    
}

/// 音楽の読み込み
/// @param path ファイルのパス
/// @param volume 音量
/// @param playType 再生タイプ
Music MusicLoad(const char* path, int volume, int playType)
{
    Music music;
    //ファイルの場所をコピー
    strcpy_s(music.Path, sizeof(music.Path), path);

    //音楽をメモリに読み込む
    music.Handle = LoadSoundMem(music.Path);

    //読み込めなかった場合
    if (music.Handle == -1)
    {
        MusicLoadErrMessage(music.Path);
    }else
    {
        //読み込めた場合
        music.Volume=volume;    //最大音量を設定
        ChangeMusicVolume(&music, music.Volume);//再生音量を設定
        music.PlayType = playType;    //再生タイプを設定
        music.IsPlayStart = true;    //停止後は最初から再生
    }
    
    return music;
}

/// 音楽の再生
/// @param music 音楽データ
void MusicPlay(Music music)
{
    switch (music.PlayType)
    {
    case DX_PLAYTYPE_BACK:
        //バックグラウンド再生
        PlaySoundMem(music.Handle, DX_PLAYTYPE_BACK, music.IsPlayStart);
        break;
    case DX_PLAYTYPE_LOOP:
        //ループ再生
        //再生されていないなら
        if(CheckSoundMem(music.Handle) == 0)
        {
            //ループ再生する
            PlaySoundMem(music.Handle, DX_PLAYTYPE_LOOP, music.IsPlayStart);
        }
        break;
        default:
            break;
    }
}

/// 音楽の一時停止
/// @param music 一時停止する音楽
void MusicPause(Music* music)
{
    //停止後は今の再生位置から再生する
    music->IsPlayStart = false;

    //再生されているかどうか
    if (CheckSoundMem(music->Handle))
    {
        //音楽の一時停止
        StopSoundMem(music->Handle);

        //マスター音量に戻す
        ChangeVolumeSoundMem(GetVolume(music->Volume), music->Handle);

        //フェード初期化
        music->FadeInStartFlg = false;
        music->FadeOutStartFlg = false;
    }

    return;
}

/// 音楽の停止
/// @param music 停止する音楽
void MusicStop(Music* music)
{
    //停止後は最初から再生する
    music->IsPlayStart = true;

    //再生されているかどうか
    if (CheckSoundMem(music->Handle))
    {
        //音楽の一時停止
        StopSoundMem(music->Handle);

        //マスター音量に戻す
        ChangeVolumeSoundMem(GetVolume(music->Volume), music->Handle);

        //フェード初期化
        music->FadeInStartFlg = false;
        music->FadeOutStartFlg = false;
    }
    return;
    
}

/// 音楽の削除
/// @param music 削除する音楽
void MusicDelete(Music music)
{
    //正常に読み込んでた場合
    if (music.Handle != -1)
    {
        //音楽をメモリから削除
        DeleteSoundMem(music.Handle);
    }
}

/// 音楽の音量変更
/// @param music 音楽データ
/// @param volume 音量
void ChangeMusicVolume(Music* music, int volume)
{
    //音量が最大音量を超えていたら
    if(volume <= music->Volume)
    {
        //ボリュームを変更
        ChangeVolumeSoundMem(GetVolume(volume), music->Handle);

    }

    return;
}

/// フェードイン中かどうか
/// @param music 音楽データ
/// @param fadeInMillTime フェードイン時間(1000=1秒)
/// @return true フェードイン終了 false フェードイン中
bool FadeInPlayMusic(Music* music, int fadeInMillTime)
{
    //初めてフェードインを行う
    if (!music->FadeInStartFlg)
    {
        //フェードイン時間を設定
        music->FadeInMillTime = 0;
        music->FadeInMillTimeMax = (fadeInMillTime/1000.0f) * GAME_FPS;
        //音量を０にする
        ChangeMusicVolume(music, 0);
        //音楽の再生
        MusicPlay(*music);
        //フェードイン開始
        music->FadeInStartFlg = true;
    }

    //フェードイン中
    if(music->FadeInStartFlg)
    {
        if(music->FadeInMillTime <= music->FadeInMillTimeMax)
        {
            //フェードイン時間をカウントアップ
            music->FadeInMillTime++;

            //音量を変更(経過時間/最大時間 * 最大音量)
            ChangeMusicVolume(music,
                (float)music->FadeInMillTime/music->FadeInMillTimeMax * music->Volume);
        }
        else if(music->FadeInMillTime >= music->FadeInMillTimeMax)
        {
            //フェードイン終了
            return true;
        }
    }
    return false;
}

/// フェードアウト中かどうか
/// @param music 音楽データ
/// @param fadeOutMillTime フェードアウト時間(1000=1秒)
/// @return true フェードアウト終了 false フェードアウト中
bool FadeOutPlayMusic(Music* music, int fadeOutMillTime)
{
    //初めてフェードアウトを行う
    if (!music->FadeOutStartFlg)
    {
        //フェードアウト時間を設定
        music->FadeOutMillTime = 0;
        music->FadeOutMillTimeMax = (fadeOutMillTime/1000.0f) * GAME_FPS;

        //音量を最大にする
        ChangeMusicVolume(music, music->Volume);
        //音楽を再生
        MusicPlay(*music);
        //フェードアウト開始
        music->FadeOutStartFlg = true;
    }

    if (music->FadeOutStartFlg)
    {
        if (music->FadeOutMillTime <= music->FadeOutMillTimeMax)
        {
            //フェードアウト時間をカウントアップ
            music->FadeOutMillTime++;

            //音量を変更(100%-(経過時間/最大時間 * 最大音量))
            ChangeMusicVolume(music,
                (1 - (float)music->FadeOutMillTime / music->FadeOutMillTimeMax) * music->Volume);
            return false;
        }
        else if (music->FadeOutMillTime >= music->FadeOutMillTimeMax)
        {
            //フェードアウト終了
            return true;
        }
    }
    return false;
}




