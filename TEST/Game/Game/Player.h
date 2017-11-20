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
#include <GamePad.h>
#include <vector>

class Player
{
public:
	static const float MOVE_SPD;
	static const DirectX::SimpleMath::Vector2 BULLET_SPD;

	// �R���X�g���N�^
	Player(ID3D11Device * device);

	// �X�V����
	void Update(DirectX::Keyboard::State Kstate,DirectX::GamePad::State Gstate);

	void Render(DirectX::SpriteBatch* spriteBatch);

	Circle2D GetCollisionCircle() { return m_Collision; }

	std::vector<Bullet*>& CreateBullets();
	std::vector<Bullet*>& CreateBullets3Way();
	std::vector<Bullet*>& CreateBulletTwin();
	std::vector<Bullet*>& CreateBulletTwin3Way();

	bool isAttackPlayer() { return m_isAttack; }

	void Damage(int damage) { m_HitPoint -= damage; }

	bool isAlive() { if (m_HitPoint <= 0) { return false; } else { return true; } }

	void PlusPow(int pow) { m_Power += pow; }
private:
	Sprite2D m_Player;
	Sprite2D m_CollisionSprite;
	
	Sprite2D m_Smog[10];
	int m_SmogCnt = 0;

	Circle2D m_Collision;

	Sprite2D m_bulletSprite;
	std::vector<Bullet*> m_Bullets;

	int m_HitPoint = 10;

	int cnt = 0;
	bool m_isAttack = false;
	int m_Power = 0;
};
