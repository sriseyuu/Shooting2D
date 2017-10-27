//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FCollision2D.cpp							
//													
// �T�@�@�v�F2D�����蔻��̃\�[�X�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 25							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "Collision2D.h"

bool OnCollision2DCircle_Circle(Circle2D _circle1, Circle2D _circle2)
{
	// 2�̔��a�̘a
	float r = _circle1.m_Radius + _circle2.m_Radius;

	// 2�̉~��x���W�̍��i2�_�Ԃ�x���W�̋����j
	float x = _circle1.m_pos.x - _circle2.m_pos.x;
	// 2�̉~��y���W�̍��i2�_�Ԃ�y���W�̋����j
	float y = _circle1.m_pos.y - _circle2.m_pos.y;

	// 2�̉~���������Ă�����true��Ԃ��A�������Ă��Ȃ����false��Ԃ�
	return (r * r >= x * x + y * y);
}
