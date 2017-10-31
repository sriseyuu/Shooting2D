//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FEnemy.cpp							
//													
// �T�@�@�v�F�G�\�[�X�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 26							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void Enemy::CreateBulletAround()
{
	for (int i = 0; i < 36; i++) {
		Bullet* bullet = new Bullet();
		bullet->SetSprite(m_BulletSprite);
		bullet->SetPos(m_sprite.GetPos());
		bullet->SetRotation(XMConvertToRadians(i * 10.0f));
		bullet->SetSpd(Vector2(0, BULLET_SPD / 4.0f));
		m_Bullets.push_back(bullet);
	}
}

Enemy::Enemy(ID3D11Device* device)
{
	m_sprite.SetTexture(device,L"Resources/Enemy.png");

	m_Collision.m_pos = m_sprite.GetPos();
	m_Collision.m_Radius = m_sprite.GetTextureSize().x / 2;

	m_BulletSprite.SetTexture(device, L"Resources/EnemyBullet.png");

}
Enemy::Enemy(ID3D11Device* device,const wchar_t* filename)
{
	m_sprite.SetTexture(device, filename);

	m_sprite.SetPos(Vector2(200, 200));

	m_Collision.m_pos = m_sprite.GetPos();
	m_Collision.m_Radius = m_sprite.GetTextureSize().x / 2;

	m_BulletSprite.SetTexture(device, L"Resources/EnemyBullet.png");
}


void Enemy::Update()
{
	m_MoveStartCnt--;
	if (m_MoveStartCnt < 0) {
		cnt++;

		m_sprite.Translate(ENEMY_SPD);

		m_Collision.m_pos = m_sprite.GetPos();

		if (cnt % 45 == 1)
		{
				m_isAttack = true;
			}
		else {
			m_isAttack = false;
		}
	}
	m_Collision.m_pos = m_sprite.GetPos();
}

void Enemy::Render(DirectX::SpriteBatch* spriteBatch)
{
	m_sprite.Render(spriteBatch);
}

std::vector<Bullet*> Enemy::CreateBullets()
{
	m_Bullets.clear();
	switch (0)
	{
	case TYPE_AROUND:
		CreateBulletAround();
		break;
	}
	return m_Bullets;
}
