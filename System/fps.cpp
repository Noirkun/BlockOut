//FPS�����̃\�[�X�t�@�C��

#include "fps.h"

#include "font.h"

//�O���[�o���ϐ�
ST_FPS fps;

//FPS������
void FPSInit()
{
	//Windows���N�����Ă��猻�݂܂ł̎��Ԃ��擾����B
	fps.FirstTakeTime = GetNowHiPerformanceCount();

	//���̒l������������
	fps.NowTakeTime = fps.FirstTakeTime;
	fps.OldTakeTime = fps.FirstTakeTime;
	fps.DeltaTime =  0.000001f;
	fps.FrameCount = 1;
	fps.Average = 0.0f;

	return; 
}

//�v��
void FPSCheck()
{
	//���݂̎������擾
	fps.NowTakeTime = GetNowHiPerformanceCount();

	//�f���^�^�C���̌v�Z
	fps.DeltaTime = (fps.NowTakeTime - fps.OldTakeTime) / MICRO_SECOND;

	//���݂̎�����ۑ�
	fps.OldTakeTime = fps.NowTakeTime;

	//���݂�Max�t���[���ڂȂ�
	if(fps.FrameCount==GAME_FPS)
	{
		//1�t���[������Max�t���[���܂ł̍��v���Ԃ��v�Z����
		float TotalFrameTime = fps.NowTakeTime - fps.FirstTakeTime;

		//���v���Ԃ𗝑z��FPS�l�Ŋ����ĕ��ϒl���v�Z����
		float CalcAverage = TotalFrameTime / GAME_FPS;

		//1�b������̃t���[�����ɕϊ�
		fps.Average = MICRO_SECOND / CalcAverage;

		//1�t���[���ڂ̎������擾
		fps.FirstTakeTime = GetNowHiPerformanceCount();  

		//�t���[������1�ɖ߂�
		fps.FrameCount = 1;
	}
	else
	{
		//�t���[�������J�E���g�A�b�v
		fps.FrameCount++;
	}

	return;
}

//�`��
void FPSDraw()
{
	//�h�b�g�t�H���g��FPS��`��
	DrawFormatStringToHandle(0, 0, GetColor(255, 255, 255),
		fontDotSmall.Handle,
		"FPS:%3.1f", fps.Average);
      
	return; 
}

//�ҋ@
void FPSWait()
{
	//���������Ƃ��ɑҋ@����~���b
	int wait = 0;

	//�҂����Ԃ��v������B
	wait =
		MICRO_SECOND / GAME_FPS * fps.FrameCount		//���z�̎���
		- (fps.NowTakeTime - fps.FirstTakeTime);	//���ۂ̎���

	wait/=MILL_SECOND;	//�~���b�ɕϊ�
	
	//�����ҋ@���Ԃ�����Ȃ�
	if(wait > 0 && wait <= WAIT_TIME_MILL)
	{
		//���b�Z�[�W���������Ȃ���҂�
		WaitTimer(wait);
	}
	return;
}
