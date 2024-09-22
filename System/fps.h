//FPS�����̃w�b�_�[�t�@�C��
#pragma once

#include  "DxLib.h"

//�}�N����`
constexpr int GAME_FPS			= 60;			//60FPS�ŌŒ肷��
constexpr float MICRO_SECOND	= 1000000.0f;	//1�}�C�N���b
constexpr float MILL_SECOND		= 1000.0f;		//1�~���b
constexpr int WAIT_TIME_MILL	= 3000;			//�ő�ő҂Ă�~����

typedef struct ST_FPS
{
	LONGLONG FirstTakeTime	 = 0;			//1�t���[���ڂ̌v������
	LONGLONG NowTakeTime	 = 0;			//���݂̌v������
	LONGLONG OldTakeTime	 = 0;			//�ȑO�̌v������
	
	float DeltaTime		= 0.000001f;		//�f���^�^�C���i�o�ߎ��ԁj
	int FrameCount		= 1;				//���݂̃t���[����
	float Average		= 0.0f;				//����FPS�l

};

//�O���O���[�o���ϐ�
extern ST_FPS fps;

//�O���v���g�^�C�v�錾
extern void FPSInit();	//FPS������
extern void FPSCheck();	//FPS�v��
extern void FPSDraw();	//FPS�`��
extern void FPSWait();	//FPS�ҋ@
