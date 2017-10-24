//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FPlayer.h							
//													
// �T�@�@�v�F�v���C���̃w�b�_�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 24							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include "Sprite2D.h"

#include <Keyboard.h>

class Player
{
public:
	const float MOVE_SPD = 2.5f;

	// �R���X�g���N�^
	Player(ID3D11Device * device);

	// �X�V����
	void Update(DirectX::Keyboard::State state);

	void Render(DirectX::SpriteBatch* spriteBatch);

private:
	Sprite2D m_Player;
};
