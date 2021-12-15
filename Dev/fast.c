
#include "portdef.h"
#include "iodefine.h"
#include "parameters.h"
#include "mytypedef.h"
#include "glob_var.h"
#include "run.h"
#include "interface.h"
#include "sci.h"

extern int get_nextdir(int x, int y, int mask, t_direction *dir);
void straight_with_var_acc(int count);
void fast_run(int x, int y)
{
//�����̍��Wx,y�Ɍ������čŒZ���s����

	t_direction glob_nextdir;
	int straight_count=0;

	//���݂̌�������A���ɍs���ׂ������֌���
	switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//���ɍs��������߂�l�Ƃ���֐����Ă�
	{
		case front:
			straight_count++;			//�O�����������ꍇ�͒����𑖂鋗����L�΂�
			break;
		
		case right:					//�E�Ɍ���
			turn(90,TURN_ACCEL,TURN_SPEED,RIGHT);				//�E�ɋȂ�����
			straight_count = 1;
			break;
		
		case left:					//���Ɍ���
			turn(90,TURN_ACCEL,TURN_SPEED,LEFT);				//���ɋȂ�����
			straight_count = 1;
			break;
		
		case rear:					//���Ɍ���
			turn(180,TURN_ACCEL,TURN_SPEED,LEFT);				//���ɋȂ�����
			straight_count = 1;
			break;
	}

	mypos.dir = glob_nextdir;	//�����̌������X�V


	//�����������ɂ���Ď����̍��W���X�V����
	switch(mypos.dir)
	{
		case north:
			mypos.y++;	//�k������������Y���W�𑝂₷
			break;
			
		case east:
			mypos.x++;	//��������������X���W�𑝂₷
			break;
			
		case south:
			mypos.y--;	//�������������Y���W�����炷
			break;
		
		case west:
			mypos.x--;	//�����������Ƃ���X���W�����炷
			break;

	}


	
	while((mypos.x != x) || (mypos.y != y)){			//�S�[������܂ŌJ��Ԃ�

		float straight_acc_arg, straight_spd_arg;
		switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//���ɍs��������߂�l�Ƃ���֐����Ă�
		{
			case front:					//�������܂Ƃ߂đ���悤�ɂ���
				straight_count++;
				break;
			
			case right:
				straight_with_var_acc(straight_count);
				turn(90,TURN_ACCEL,TURN_SPEED,RIGHT);				//�E�ɋȂ�����
				straight_count = 1;			//���钼���̋��������Z�b�g
				break;
			
			case left:
				straight_with_var_acc(straight_count);
				turn(90,TURN_ACCEL,TURN_SPEED,LEFT);				//���ɋȂ�����
				straight_count = 1;			//���钼���̋��������Z�b�g
				break;
			
			case rear:
				straight_with_var_acc(straight_count);
				turn(180,TURN_ACCEL,TURN_SPEED,LEFT);				//���ɋȂ�����
				straight_count = 1;			//���钼���̋��������Z�b�g
				break;
		}
	
		mypos.dir = glob_nextdir;	//�����̌������C��
		
		//�����������ɂ���Ď����̍��W���X�V����
		switch(mypos.dir)
		{
			case north:
				mypos.y++;	//�k������������Y���W�𑝂₷
				break;
				
			case east:
				mypos.x++;	//��������������X���W�𑝂₷
				break;
				
			case south:
				mypos.y--;	//�������������Y���W�����炷
				break;
			
			case west:
				mypos.x--;	//�����������Ƃ���X���W�����炷
				break;

		}
	}
	straight(SECTION*straight_count,FAST_ACCEL,FAST_SPEED,0.0);
}

void straight_with_var_acc(int count)
{
	float straight_acc_arg = FAST_ACCEL, straight_spd_arg = FAST_SPEED;
	if (count < 2){
		straight_acc_arg = FAST_ACCEL - 1.5;
	}
	else if(count < 4){
		straight_acc_arg = FAST_ACCEL - 1.0;
	}
	straight(SECTION*count, straight_acc_arg, straight_spd_arg, 0.0);
}