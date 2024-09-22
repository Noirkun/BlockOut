#include "DxLib.h"
#include "System/fps.h"
#include "game.h"
#include "System/key.h"
#include "System/mouse.h"
#include "System/font.h"
#include "System/music.h"
#include "vcruntime.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{

	SetOutApplicationLogValidFlag(FALSE);			//Log,txt���o�͂��Ȃ�
	ChangeWindowMode(TRUE);							//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH,GAME_HEIGHT,GAME_COLOR);	//�𑜓x��ݒ�
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);			//�E�B���h�E�̑傫����ݒ�
	SetMainWindowText(GAME_TITLE);					//�E�B���h�E�̃^�C�g��
	SetBackgroundColor(0, 0, 0);					//�E�B���h�E�̔w�i�F��ݒ�
	SetWaitVSyncFlag(GAME_VSYNC);					//���������̐ݒ�
	SetAlwaysRunFlag(TRUE);							//��A�N�e�B�u�ł����s����B
	SetWindowIconID(GAME_ICON);						//�A�C�R���̐ݒ�
	
	
	//DxLib��������
	if(DxLib_Init()==-1)
	{
		//DxLib���������s�Ȃ�\�t�g�I��������
		return -1;
	}

	//����ʂɕ`��i�_�u���o�b�t�@�����O�j
	SetDrawScreen(DX_SCREEN_BACK);

	//�t�H���g�̏�����
	if(FontInit()==false)
	{
		GameAndDxLibAllEnd();
		return -1;
	}

	//���y�̏�����
	if(MusicInit()==false)
	{
		GameAndDxLibAllEnd();
		return -1;
	}

	//�Q�[��������
	InitGame();

	//FPS������
	FPSInit();

	//�L�[������
	KeyInit();
	
	//�}�E�X������
	MouseInit();

	//�^�C�g���V�[���̏�����
	InitScene(NowGameScene);

	while(TRUE)
	{
		//���b�Z�[�W�������s���B�i�}�E�X��L�[�{�[�h�̑�����󂯑�����j
		if(ProcessMessage() !=0)
		{
			break;
		}

		//��ʂ������i1���[�v������������j
		if(ClearDrawScreen() !=0)
		{
			break;
		}
		//FPS�v��
		FPSCheck();

		//�L�[�X�V
		KeyUpdate();

		//�}�E�X�X�V
		MouseUpdate();

		//�V�[���؂�ւ�(�V�[�����Ƃ̏���)
		SwitchScene();

		//FPS�`��
		FPSDraw();

		//FPS�ҋ@
		FPSWait();
		

		//����ʂ���ʂɕ`��
		ScreenFlip();
	}

	//�Q�[����DxLib�̏I������
	GameAndDxLibAllEnd();

	return 0;

}
