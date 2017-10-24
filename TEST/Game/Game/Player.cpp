//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FPlayer.cpp							
//													
// �T�@�@�v�F�v���C���̃\�[�X�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 24							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player(ID3D11Device * device)
{
	m_Player.SetTexture(device,L"Resources/Player.png");
}

void Player::Update(DirectX::Keyboard::State state)
{

	Vector2 spd = Vector2::Zero;

	if (state.Up) {
		spd.y -= MOVE_SPD;
	}
	if (state.Down) {
		spd.y += MOVE_SPD;
	}
	if (state.Left) {
		spd.x -= MOVE_SPD;
	}
	if (state.Right) {
		spd.x += MOVE_SPD;
	}
	if (state.Enter) {

	}
	m_Player.Translate(spd);

	m_Player.Update();
}

void Player::Render(DirectX::SpriteBatch * spriteBatch)
{
	m_Player.Render(spriteBatch);
}

