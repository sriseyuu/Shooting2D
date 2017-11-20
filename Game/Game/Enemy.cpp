//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：Enemy.cpp							
//													
// 概　　要：敵ソースファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 26							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void Enemy::CreateBulletAround()
{
	for (int i = 0; i < 18; i++) {
		Bullet* bullet = new Bullet();
		bullet->SetSprite(m_BulletSprite);
		bullet->SetPos(m_sprite.GetPos());
		bullet->SetRotation(XMConvertToRadians(i * 20.0f));
		bullet->SetSpd(Vector2(0, BULLET_SPD / 4.0f));
		m_Bullets.push_back(bullet);
	}
}

void Enemy::CreateBullet3Way()
{
	for (int i = 0; i < 3; i++) {
		Bullet* bullet = new Bullet();
		bullet->SetSprite(m_BulletSprite);
		bullet->SetPos(m_sprite.GetPos());
		bullet->SetRotation(XMConvertToRadians((i - 1) * 15.0f));
		bullet->SetSpd(Vector2(0, BULLET_SPD / 4.0f));
		m_Bullets.push_back(bullet);
	}
}

void Enemy::CreateBulletRandom()
{
	int random = rand() % 36;
	for (int i = 0; i < random; i++) {
		Bullet* bullet = new Bullet();
		bullet->SetSprite(m_BulletSprite);
		bullet->SetPos(m_sprite.GetPos());
		bullet->SetRotation(XMConvertToRadians(rand() % 3600 / 10.0f));
		bullet->SetSpd(Vector2(0, BULLET_SPD / (rand() % 20 / 10 + 2)));
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
	if (m_MoveStartCnt < 0) {
		cnt++;

		m_sprite.Translate(ENEMY_SPD);

		m_Collision.m_pos = m_sprite.GetPos();

		if (cnt % m_Interval == 1)
		{
				m_isAttack = true;
			}
		else {
			m_isAttack = false;
		}
	}
	else 
	{
		m_MoveStartCnt--;
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
	switch (BulletType)
	{
	case TYPE_AROUND:
		CreateBulletAround();
		break;
	case TYPE_3WAY:
		CreateBullet3Way();
		break;
	case TYPE_RANDOM:
		CreateBulletRandom();
		break;
	}
	return m_Bullets;
}
