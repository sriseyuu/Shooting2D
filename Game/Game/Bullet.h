#pragma once

#include <SimpleMath.h>
#include "Sprite2D.h"
#include "Collision2D.h"

class Bullet
{
public:
	Bullet() {}
	// コンストラクタ
	Bullet(ID3D11Device * device);

	// デストラクタ
	~Bullet() {}

	// 更新処理
	void Update();
	// 描画処理
	void Render(DirectX::SpriteBatch* spriteBatch);

	// 弾の速さを設定
	void SetSpd(DirectX::SimpleMath::Vector2 spd) { m_spd = spd; }
	// 弾の座標の取得と設定
	DirectX::SimpleMath::Vector2 GetPos() { return m_sprite.GetPos(); }
	void SetPos(DirectX::SimpleMath::Vector2 pos) { m_sprite.SetPos(pos); }

	// 弾の回転角を設定
	void SetRotation(float rot) { m_sprite.SetRotation(rot); }

	// 当たり判定の取得
	Circle2D GetCollisionCircle() { return m_Collision; }

	// スプライトの取得と設定
	Sprite2D GetSprite() { return m_sprite; }
	void SetSprite(Sprite2D sprite) { m_sprite = sprite; }
private:

	// 弾の2Dスプライト
	Sprite2D m_sprite;
	// 弾の速さ
	DirectX::SimpleMath::Vector2 m_spd;

	// 円の当たり判定
	Circle2D m_Collision;
};