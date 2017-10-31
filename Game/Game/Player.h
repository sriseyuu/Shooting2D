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
#include "Bullet.h"

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

	Circle2D GetCollisionCircle() { return m_Collision; }

	std::vector<Bullet*>& CreateBullets();

	bool isAttackPlayer() { return m_isAttack; }
private:
	Sprite2D m_Player;
	Sprite2D m_CollisionSprite;
	Circle2D m_Collision;

	Sprite2D m_bulletSprite;
	std::vector<Bullet*> m_Bullets;

	int cnt = 0;
	bool m_isAttack = false;
};
