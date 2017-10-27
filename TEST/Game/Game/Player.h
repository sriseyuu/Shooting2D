//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：Player.h							
//													
// 概　　要：プレイヤのヘッダファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 24							
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

	// コンストラクタ
	Player(ID3D11Device * device);

	// 更新処理
	void Update(DirectX::Keyboard::State state);

	void Render(DirectX::SpriteBatch* spriteBatch);

	Circle2D GetCollisionCircle() { return m_Collision; }

	std::vector<Circle2D> GetCollisionBulletCircle();

	std::vector<Bullet>& GetBullet() { return m_Bullets; }
private:
	Sprite2D m_Player;
	Circle2D m_Collision;

	Bullet m_NormalBullet;
	std::vector<Bullet> m_Bullets;

	int cnt = 0;
};
