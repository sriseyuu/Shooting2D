//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：Player.cpp							
//													
// 概　　要：プレイヤのソースファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 24							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "Player.h"
#include <WICTextureLoader.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float Player::MOVE_SPD = 2.5f;
const Vector2 Player::BULLET_SPD = DirectX::SimpleMath::Vector2(0, -16.0f);

Player::Player(ID3D11Device* device)
	: m_NormalBullet(device)
	, m_Bullets()
{
	m_Player.SetTexture(device,L"Resources/Player.png");
	m_Player.SetPos(Vector2(600,300));

	m_Bullets.resize(0);

	m_Collision.m_pos = m_Player.GetPos();
	m_Collision.m_Radius = m_Player.GetTextureSize().x / 2;
}

void Player::Update(DirectX::Keyboard::State state)
{
	cnt--;
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

	m_Player.Translate(spd);

	if (state.Z) {

		if (cnt < 0)
		{
			cnt = 6;
			for (int i = 0; i < 3; i++)
			{
				Bullet bullet = m_NormalBullet;
				bullet.SetPos(m_Player.GetPos());
				bullet.SetRotation(XMConvertToRadians((i - 1) * 10.0f));

				m_Bullets.push_back(bullet);
			}
		}
	}


	m_Player.Update();
	std::vector<Bullet>::iterator it = m_Bullets.begin();
	while ( it != m_Bullets.end())
	{
		
		it->SetSpd(BULLET_SPD);

		it->Update();

		if (it->GetPos().y < -32) {
			it = m_Bullets.erase(it);
		}
		else {
			it++;
		}
	}

	m_Collision.m_pos = m_Player.GetPos();
}

void Player::Render(DirectX::SpriteBatch * spriteBatch)
{
	m_Player.Render(spriteBatch);

	for (std::vector<Bullet>::iterator it = m_Bullets.begin(); it < m_Bullets.end(); it++)
	{
		(*it).Render(spriteBatch);
	}
}

std::vector<Circle2D> Player::GetCollisionBulletCircle()
{
	std::vector<Circle2D> circle;

	circle.resize(0);

	for (std::vector<Bullet>::iterator itr = m_Bullets.begin(); itr != m_Bullets.end(); itr++)
	{
		circle.push_back(itr->GetCollisionCircle());
	}

	return circle;
}

