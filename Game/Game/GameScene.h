//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：GameScene.h							
//													
// 概　　要：ゲームシーンのヘッダファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 25						
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include "BaseScene.h"
#include "Sprite2D.h"
#include "Obstacle.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class GameScene : public BaseScene
{
private:

	// 敵のロード
	void LoadCSV(ID3D11Device* device);
//__/__/__/__/__/__/__/__/__/ゲーム関係__/__/__/__/__/__/__/__/__/

	// 画面外に行ったら弾を消す
	void ScreenOut(std::vector<Bullet*>& bullet);
	// 画面外に行ったら敵を消す
	void ScreenOut(std::vector<Enemy*>& enemies);
	// 弾の更新処理
	void BulletUpdate(std::vector<Bullet*> bullet);
	// プレイヤの弾生成
	void SetPlayerBullet();
	// 敵の弾生成
	void SetEnemyBullet(std::vector<Enemy*>::iterator itr);
	// プレイヤと弾の当たり判定
	void CollisionBullet_Player(std::vector<Bullet*> & bullet1, Player* & Player);
	// 敵と弾の当たり判定	
	void CollisionBullet_Enemy(std::vector<Bullet*> & bullet, std::vector<Enemy*> & Enemies);

	void CollisionBullet_Obstacle(std::vector<Bullet*> & bullet , Obstacle* & Obstacle);
//__/__/__/__/__/__/__/__/__/関数__/__/__/__/__/__/__/__/__/
public:
	GameScene()	: BaseScene() {} 
	GameScene(ID3D11Device* device,ID3D11DeviceContext* context);
	~GameScene();
	void Update();
	void Render(DirectX::SpriteBatch* spriteBatch);



//__/__/__/__/__/__/__/__/__/メンバ変数__/__/__/__/__/__/__/__/
private:
	Player* m_Player;
	std::vector<Bullet*> m_PlayerBullets;

	std::vector<Enemy*> m_Enemies;
	std::vector<Bullet*> m_EnemyBullets;

	Obstacle* m_Obstacle;
	DirectX::SimpleMath::Vector2 m_ObstacleSpd;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Background;
	float BackgroundY;
};