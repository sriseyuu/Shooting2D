//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FCollision2D.h							
//													
// �T�@�@�v�F2D�����蔻��̃w�b�_�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 25							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include<d3d11.h>
#include<SimpleMath.h>

class Circle2D
{
public:
	// �~�̓����蔻��̌��ݍ��W
	DirectX::SimpleMath::Vector2 m_pos;

	// �~�̔��a
	float m_Radius = 1.0f;
};

bool OnCollision2DCircle_Circle(Circle2D _circle1, Circle2D _circle2);