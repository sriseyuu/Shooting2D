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

Enemy::Enemy(ID3D11Device* device)
{
	m_sprite.SetTexture(device,L"Resources/Enemy.png");

	m_Collision.m_pos = m_sprite.GetPos();
	m_Collision.m_Radius = m_sprite.GetTextureSize().x / 2;

	m_NormalBullet = Bullet(device);
}
Enemy::Enemy(ID3D11Device* device,const wchar_t* filename)
{
	m_sprite.SetTexture(device, filename);

	m_sprite.SetPos(Vector2(200, 200));

	m_Collision.m_pos = m_sprite.GetPos();
	m_Collision.m_Radius = m_sprite.GetTextureSize().x / 2;

	m_NormalBullet = Bullet(device);
}


void Enemy::Update()
{
	m_MoveStartCnt--;
	if (m_MoveStartCnt < 0) {
		cnt++;

		m_sprite.Translate(ENEMY_SPD);

		m_Collision.m_pos = m_sprite.GetPos();

		if (cnt % 20 == 1)
		{
			m_NormalBullet.SetPos(m_sprite.GetPos());
			m_NormalBullet.SetSpd(Vector2(0, BULLET_SPD));

			m_Bullets.push_back(m_NormalBullet);
		}

		for (std::vector<Bullet>::iterator itr = m_Bullets.begin();
			itr != m_Bullets.end();
			itr++)
		{
			itr->Update();
		}
	}
}

void Enemy::Render(DirectX::SpriteBatch* spriteBatch)
{
	m_sprite.Render(spriteBatch);

	for (std::vector<Bullet>::iterator itr = m_Bullets.begin();
		itr != m_Bullets.end();
		itr++)
	{
		itr->Render(spriteBatch);
	}
}
