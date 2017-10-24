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
#include <vector>

class Player
{
public:
	static const float MOVE_SPD;
	static const DirectX::SimpleMath::Vector2 BULLET_SPD;

	// �R���X�g���N�^
	Player(ID3D11Device * device);

	// �X�V����
	void Update(DirectX::Keyboard::State state);

	void Render(DirectX::SpriteBatch* spriteBatch);

private:
	Sprite2D m_Player;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_PlayerBulletTexture;
	std::vector<Sprite2D> m_Bullets;

	int cnt = 0;
};
