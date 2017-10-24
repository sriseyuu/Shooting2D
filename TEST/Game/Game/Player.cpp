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
{
	m_Player.SetTexture(device,L"Resources/Player.png");
	CreateWICTextureFromFile(device, L"Resources/Bullet.png", nullptr,
		m_PlayerBulletTexture.ReleaseAndGetAddressOf());

	m_Bullets.resize(0);
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
	m_Player.Translate(spd);

	if (state.Z) {
		cnt--;
		if (cnt < 0)
		{
			cnt = 6;
			for (int i = 0; i < 3; i++)
			{
				Sprite2D bullet;
				bullet.SetTexture(m_PlayerBulletTexture);
				bullet.SetPos(m_Player.GetPos());
				bullet.SetRotation(XMConvertToRadians((i - 1) * 15.0f));

				m_Bullets.push_back(bullet);
			}
		}
	}


	m_Player.Update();
	std::vector<Sprite2D>::iterator it = m_Bullets.begin();
	while ( it != m_Bullets.end())
	{
		
		it->Translate(BULLET_SPD);

		it->Update();

		if (it->GetPos().y < -32) {
			it = m_Bullets.erase(it);
		}
		else {
			it++;
		}


	}
}

void Player::Render(DirectX::SpriteBatch * spriteBatch)
{
	m_Player.Render(spriteBatch);

	for (std::vector<Sprite2D>::iterator it = m_Bullets.begin(); it < m_Bullets.end(); it++)
	{
		(*it).Render(spriteBatch);
	}
}

