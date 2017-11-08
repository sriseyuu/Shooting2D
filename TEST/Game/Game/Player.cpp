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
	: m_Bullets()
{
	m_Player.SetTexture(device,L"Resources/Player.png");
	m_Player.SetPos(Vector2(300	,500));

	m_Bullets.resize(0);

	m_CollisionSprite.SetTexture(device,L"Resources/PlayerCollision.png");
	m_CollisionSprite.SetPos(m_Player.GetPos());
	m_Collision.m_pos = m_CollisionSprite.GetPos();
	m_Collision.m_Radius = m_CollisionSprite.GetTextureSize().x / 2;

	m_bulletSprite.SetTexture(device, L"Resources/Bullet.png");

	//m_Player_HitPoint_UI.SetTexture(device,L"Resources/Player_HitPoint_UI.png");
	//m_Player_HitPoint_UI.SetPos(Vector2(200,500));

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
	if (m_Player.GetPos().x + spd.x < 800 &&
		m_Player.GetPos().x + spd.x > 0 &&
		m_Player.GetPos().y + spd.y < 600 &&
		m_Player.GetPos().y + spd.y > 0) {
		m_Player.Translate(spd);
	}

	if (state.Z) {

		if (cnt < 0)
		{
			cnt = 6;
			
			m_isAttack = true;
		}
		else {
			m_isAttack = false;
		}
	}
	else {
		m_isAttack = false;
	}


	m_Player.Update();

	m_CollisionSprite.SetPos(m_Player.GetPos());
	m_CollisionSprite.Update();

	m_Collision.m_pos = m_CollisionSprite.GetPos();
}

void Player::Render(DirectX::SpriteBatch * spriteBatch)
{
	m_Player.Render(spriteBatch);
	m_CollisionSprite.Render(spriteBatch);

//	m_Player_HitPoint_UI.Render(spriteBatch);
}


std::vector<Bullet*>& Player::CreateBullets()
{
	// TODO: return ステートメントをここに挿入します
	switch (0)
	{
	case 0:
		return CreateBullets3Way();
	default:
		return CreateBullets3Way();
	}
}

std::vector<Bullet*>& Player::CreateBullets3Way()
{
	m_Bullets.clear();
	// TODO: return ステートメントをここに挿入します
	for (int i = 0; i < 3; i++)
	{
		Bullet* bullet = new Bullet();
		bullet->SetSprite(m_bulletSprite);
		bullet->SetPos(m_Player.GetPos());
		bullet->SetRotation(XMConvertToRadians((i - 1) * 10.0f));
		bullet->SetSpd(BULLET_SPD);

		m_Bullets.push_back(bullet);
	}

	return m_Bullets;
}

