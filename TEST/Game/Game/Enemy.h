//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：Enemy.h							
//													
// 概　　要：敵のヘッダファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 26							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include <vector>

#include "Sprite2D.h"
#include "Collision2D.h"
#include "Bullet.h"

class Enemy
{
private:
	void CreateBulletAround();
	void CreateBullet3Way();
	void CreateBulletRandom();
public:
	enum BULLET_TYPE
	{
		TYPE_AROUND,
		TYPE_3WAY,
		TYPE_RANDOM,
	};

	float BULLET_SPD = 16.0f;
	DirectX::SimpleMath::Vector2 ENEMY_SPD = DirectX::SimpleMath::Vector2(0,0);
	int BulletType;

	Enemy() {}
	Enemy(ID3D11Device* device);
	Enemy(ID3D11Device* device, const wchar_t* filename);

	// 更新処理
	void Update();

	// 描画処理
	void Render(DirectX::SpriteBatch* spriteBatch);

	Circle2D GetCollisionCircle() { return m_Collision; }

	// 座標の設定と取得
	void SetPos(DirectX::SimpleMath::Vector2 pos) { m_sprite.SetPos(pos); }
	DirectX::SimpleMath::Vector2 GetPos() { return m_sprite.GetPos(); }

	void SetMoveCnt(int cnt) { m_MoveStartCnt = cnt; }

	std::vector<Bullet*> CreateBullets();

	bool isAttackEnemy() { return m_isAttack; }

	// ダメージを受ける
	bool Damage(int damagePoint) { m_HitPoint -= damagePoint; if (m_HitPoint <= 0) { return true; } return false; }

	// 体力の取得と設定
	void SetHitPoint(int HitPoint) { m_HitPoint = HitPoint; }
	int GetHitPoint() { return m_HitPoint; }

	// 弾の間隔の取得と設定
	void SetInterval(int Interval) { m_Interval = Interval; }
	int GetInterval() { return m_Interval; }

	void SetBrake(DirectX::SimpleMath::Vector2 brake) { m_Brake = brake; }

private:
	// カウント
	int cnt = 0;

	int m_MoveStartCnt = 0;

	// 敵スプライト
	Sprite2D m_sprite;

	// 敵当たり判定
	Circle2D m_Collision;


	std::vector<Bullet*> m_Bullets;
	Sprite2D m_BulletSprite;

	bool m_isAttack = false;

	int m_HitPoint;

	int m_Interval;

	DirectX::SimpleMath::Vector2 m_Brake;
};