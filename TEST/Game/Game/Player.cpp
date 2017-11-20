//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：Player.cpp							
//													
// 概　　要：プレイヤのソースファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 11 / 16							
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
	m_Player.SetTexture(device,L"Resources/PlayerT.png");
	m_Player.SetPos(Vector2(300	,500));

	m_Bullets.resize(0);

	m_CollisionSprite.SetTexture(device,L"Resources/PlayerCollision.png");
	m_CollisionSprite.SetPos(m_Player.GetPos());
	m_Collision.m_pos = m_CollisionSprite.GetPos();
	m_Collision.m_Radius = m_CollisionSprite.GetTextureSize().x / 2;

	m_bulletSprite.SetTexture(device, L"Resources/Bullet.png");

	for (int i = 0; i < 10; i++)
	{
		m_Smog[i].SetTexture(device, L"Resources/PlayerSmog.png");
		m_Smog[i].SetPos(m_Player.GetPos());
	}
	//m_Player_HitPoint_UI.SetTexture(device,L"Resources/Player_HitPoint_UI.png");
	//m_Player_HitPoint_UI.SetPos(Vector2(200,500));

}


void Player::Update(DirectX::Keyboard::State Kstate, DirectX::GamePad::State Gstate)
{
	cnt--;
	m_SmogCnt++;

	Vector2 spd = Vector2::Zero;

	if (Kstate.Up || Gstate.dpad.up) {
		spd.y -= MOVE_SPD;
	}
	if (Kstate.Down || Gstate.dpad.down) {
		spd.y += MOVE_SPD;
	}
	if (Kstate.Left || Gstate.dpad.left) {
		spd.x -= MOVE_SPD;
	}
	if (Kstate.Right || Gstate.dpad.right) {
		spd.x += MOVE_SPD;
	}

	if (Gstate.thumbSticks.leftX != 0 || Gstate.thumbSticks.leftY != 0) {
		spd.x = Gstate.thumbSticks.leftX * MOVE_SPD;
		spd.y = -Gstate.thumbSticks.leftY * MOVE_SPD;
	}

	// 移動後に画面外に出る場合～Xver.～
	if (m_Player.GetPos().x + spd.x >= 800 ||
		m_Player.GetPos().x + spd.x < 0) {
		spd.x = 0;
	}

	// 移動後に画面外に出る場合～Yver.～
	if (m_Player.GetPos().y + spd.y >= 600 ||
		m_Player.GetPos().y + spd.y < 0) {
		spd.y = 0;
	}
		m_Player.Translate(spd);

	if (Kstate.Z || Gstate.buttons.b) {

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


	m_Smog[m_SmogCnt % 10].SetPos(m_Player.GetPos());
}

void Player::Render(DirectX::SpriteBatch * spriteBatch)
{
	m_Player.Render(spriteBatch);
	m_CollisionSprite.Render(spriteBatch);

	for (int i = 0; i < 10; i++)
	{
		m_Smog[i].Render(spriteBatch);
	}

//	m_Player_HitPoint_UI.Render(spriteBatch);
}


std::vector<Bullet*>& Player::CreateBullets()
{
	// TODO: return ステートメントをここに挿入します
	switch (m_Power / 10)
	{
	case 0:
		return CreateBulletTwin();
	default:
		return CreateBulletTwin3Way();
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

std::vector<Bullet*>& Player::CreateBulletTwin()
{
	// TODO: return ステートメントをここに挿入します
	m_Bullets.clear();
	for (int i = 0; i < 2; i++)
	{

		Bullet* bullet = new Bullet();
		bullet->SetSprite(m_bulletSprite);
		bullet->SetPos(Vector2(m_Player.GetPos().x - ((m_Player.GetTextureSize().x / 1.5f) * i - m_Player.GetTextureSize().x / 3), m_Player.GetPos().y - m_Player.GetTextureSize().x / 4));

		bullet->SetRotation(XMConvertToRadians(0));
		bullet->SetSpd(BULLET_SPD);

		m_Bullets.push_back(bullet);
	}

	return m_Bullets;
}

std::vector<Bullet*>& Player::CreateBulletTwin3Way()
{
	// TODO: return ステートメントをここに挿入します
	m_Bullets.clear();
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Bullet* bullet = new Bullet();
			bullet->SetSprite(m_bulletSprite);
			bullet->SetPos(Vector2(m_Player.GetPos().x - ((m_Player.GetTextureSize().x / 1.5f) * i - m_Player.GetTextureSize().x / 3), m_Player.GetPos().y - m_Player.GetTextureSize().x / 4));
			bullet->SetRotation(XMConvertToRadians((j - 1) * 10.0f));

			bullet->SetSpd(BULLET_SPD);

			m_Bullets.push_back(bullet);
		}
	}

	return m_Bullets;
}

