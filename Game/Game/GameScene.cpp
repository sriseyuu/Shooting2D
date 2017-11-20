//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：GameScene.cpp							
//													
// 概　　要：ゲームシーンのソースファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 26							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "GameScene.h"

#include <WICTextureLoader.h>

#include <fstream>
#include <sstream>
#include <algorithm>

using namespace DirectX;
using namespace DirectX::SimpleMath;

GameScene::GameScene(ID3D11Device * device, ID3D11DeviceContext * context)
	:BaseScene()
{
	m_Player = new Player(device);
	
	LoadCSV(device);

	CreateWICTextureFromFile(device, L"Resources/Background.png", nullptr, m_Background.ReleaseAndGetAddressOf());
	BackgroundY = 0;
	m_Obstacle = new Obstacle();
	m_Obstacle->SetTexture(device, L"Resources/Obstacle.png");
	m_Obstacle->SetPos((rand() % 8000) / 10.0f, 0);
	m_Obstacle->SetCollisionTex();
	m_ObstacleSpd = Vector2(0, 1);
}

GameScene::~GameScene()
{
	delete m_Player;
	m_Player = nullptr;

}

void GameScene::Update()
{
	// キーの判定
	auto KeyState = m_Keyboard->GetState();
	auto Padstate = m_GamePad->GetState(0);

	//__/__/__/__/__/更新処理系/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
	
	m_Obstacle->Translate(m_ObstacleSpd);
	m_Obstacle->Update();

	// 敵が出ている数だけ更新処理行う
	for (std::vector<Enemy*>::iterator itr = m_Enemies.begin(); itr != m_Enemies.end(); itr++)
	{
		(*itr)->Update();
		// 攻撃可能なら弾を発射する
		if ((*itr)->isAttackEnemy())
		{
			SetEnemyBullet(itr);
		}
	}

	// プレイヤが出ている場合プレイヤの更新処理を行う
	if (m_Player != nullptr) {
		m_Player->Update(KeyState, Padstate);
		// 攻撃可能なら弾を発射する
		if (m_Player->isAttackPlayer())
		{
			SetPlayerBullet();
		}
	}
	BulletUpdate(m_PlayerBullets);
	BulletUpdate(m_EnemyBullets);

	ScreenOut(m_Enemies);
	ScreenOut(m_PlayerBullets);
	ScreenOut(m_EnemyBullets);

//__/__/__/__/__/当たり判定処理/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

	CollisionBullet_Player(m_EnemyBullets,m_Player);
	CollisionBullet_Enemy(m_PlayerBullets,m_Enemies);
	CollisionBullet_Obstacle(m_EnemyBullets,m_Obstacle);
	CollisionBullet_Obstacle(m_PlayerBullets, m_Obstacle);

	BackgroundY += 0.5f;
	if (BackgroundY > 600) 
	{
		BackgroundY = 0;
	}

	// 仮で敵と敵の弾が全て消えたらゲームを終了する
	if (m_Enemies.empty() && m_EnemyBullets.empty())
	{
		Scene = 1;
	}
}

void GameScene::Render(SpriteBatch* spriteBatch)
{
	// 背景描画
	spriteBatch->Draw(m_Background.Get(), Vector2(0, BackgroundY), Colors::White);
	spriteBatch->Draw(m_Background.Get(), Vector2(0, BackgroundY - 600), Colors::White);
	// 障害物描画
	m_Obstacle->Render(spriteBatch);
	// プレイヤ関係の描画
	if (m_Player != nullptr)
	{
		m_Player->Render(spriteBatch);
	}
	for (std::vector<Bullet*>::iterator itr = m_PlayerBullets.begin(); itr != m_PlayerBullets.end(); itr++)
	{
		(*itr)->Render(spriteBatch);
	}
	// 敵関係の描画
	for (std::vector<Enemy*>::iterator itr = m_Enemies.begin(); itr != m_Enemies.end(); itr++)
	{
		(*itr)->Render(spriteBatch);
	}
	for (std::vector<Bullet*>::iterator itr = m_EnemyBullets.begin(); itr != m_EnemyBullets.end(); itr++)
	{
		(*itr)->Render(spriteBatch);
	}
}

void GameScene::ScreenOut(std::vector<Bullet*>& bullet)
{
	
	std::vector<Bullet*>::iterator it = bullet.begin();
	while (it != bullet.end())
	{

		if ((*it)->GetPos().y < 0 ||
			(*it)->GetPos().y > 600 ||
			(*it)->GetPos().x < -0 ||
			(*it)->GetPos().x > 800)
		{
			it = bullet.erase(it);
		}
		else {
			it++;
		}
	}
}

void GameScene::ScreenOut(std::vector<Enemy*>& enemies)
{
	std::vector<Enemy*>::iterator it = enemies.begin();
	while (it != enemies.end())
	{
		// 移動方向が消える方向かつ画面外へ出たときに敵を削除する
		if (((*it)->GetPos().y < -32 && (*it)->ENEMY_SPD.y < 0.0f) ||
			((*it)->GetPos().y > 632 && (*it)->ENEMY_SPD.y > 0.0f) ||
			((*it)->GetPos().x < -32 && (*it)->ENEMY_SPD.x < 0.0f) ||
			((*it)->GetPos().x > 832 && (*it)->ENEMY_SPD.x > 0.0f))
		{
			it = enemies.erase(it);
		}
		else {
			it++;
		}
	}
}

void GameScene::BulletUpdate(std::vector<Bullet*> bullet)
{
	if (!bullet.empty()) {
		std::vector<Bullet*>::iterator itr = bullet.begin();

		while (itr != bullet.end())
		{
			(*itr)->Update();
			itr++;
		}
	}
}

void GameScene::SetPlayerBullet()
{
	std::vector<Bullet*> pBullet = m_Player->CreateBullets();
	for (std::vector<Bullet*>::iterator itr = pBullet.begin();
		itr != pBullet.end();
		itr++)
	{
		m_PlayerBullets.push_back(*itr);
	}
}

void GameScene::SetEnemyBullet(std::vector<Enemy*>::iterator itr)
{
	std::vector<Bullet*> EnemyBullet =  (*itr)->CreateBullets();
	for (std::vector<Bullet*>::iterator it = EnemyBullet.begin();
		it != EnemyBullet.end();
		it++)
	{
		m_EnemyBullets.push_back(*it);
	}
}

void GameScene::CollisionBullet_Player(std::vector<Bullet*>& bullet1, Player* & Player)
{
	if (!bullet1.empty()) {
		std::vector<Bullet*>::iterator itr = bullet1.begin();
		while (itr != bullet1.end())
		{
			if (m_Player == nullptr)
			{
				break;
			}
			if (Collision2D::OnCircle2(Player->GetCollisionCircle(), (*itr)->GetCollisionCircle()))
			{
				itr = bullet1.erase(itr);

				m_Player->Damage(2);

				if(!m_Player->isAlive())
				{
					delete m_Player;
					m_Player = nullptr;
				}
			}
			else
			{
				if (bullet1.empty())
				{
					break;
				}
				itr++;
			}

			if (m_Player == nullptr)
			{
				break;
			}
		}
	}
}

void GameScene::CollisionBullet_Enemy(std::vector<Bullet*>& bullet, std::vector<Enemy*>& Enemies)
{
	if (!Enemies.empty()) {
		std::vector<Enemy*>::iterator itr = Enemies.begin();
		while (itr != Enemies.end())
		{
			if (!bullet.empty()) {
				std::vector<Bullet*>::iterator itrB = bullet.begin();
				while (itrB != bullet.end()) 
				{
					if (Collision2D::OnCircle2((*itr)->GetCollisionCircle(), (*itrB)->GetCollisionCircle()))
					{
						itrB = bullet.erase(itrB);
						if ((*itr)->Damage(1))
						{
							itr = Enemies.erase(itr);
						}
						if (itr != Enemies.begin()) {
							itr--;
						}
					}
					else
					{
						itrB++;
					}
					if (Enemies.empty()) {
						break;
					}
				}
			}
			if (Enemies.empty()) {
				break;
			}
			itr++;
		}
	}
}

void GameScene::CollisionBullet_Obstacle(std::vector<Bullet*>& bullet, Obstacle *& Obstacle)
{
	if (!bullet.empty()) {
		std::vector<Bullet*>::iterator itr = bullet.begin();
		while (itr != bullet.end())
		{
			if (Obstacle == nullptr)
			{
				break;
			}
			if (Collision2D::OnCircle2(Obstacle->GetCollisionCircle(), (*itr)->GetCollisionCircle()))
			{
				itr = bullet.erase(itr);
			}
			else
			{
				if (bullet.empty())
				{
					break;
				}
				itr++;
			}

			if (Obstacle == nullptr)
			{
				break;
			}
		}
	}
}

void GameScene::LoadCSV(ID3D11Device* device)
{
	// csvフォルダを呼ぶ
	std::wifstream ifs("CSV/EnemyTest.csv");

	std::wstring line;

	// 1行目をスキップ
	getline(ifs, line);

	// 名簿からデータを解析
	while (getline(ifs, line))
	{
		std::wstring filepath;
		std::wstring filename;

		wchar_t del = L',';
		// カンマを空白に置き換え
		std::replace(line.begin(), line.end(), L',', L' ');

		// 1行分を文字列ストリームに変換
		std::wistringstream stream(line);

//__/__/__/__/__/__/１グループに必要なものの読み込み/__/__/__/__/__/__/__/__//

		// １グループ数の敵の数を読み込み
		int EnemyGroup;
		stream >> EnemyGroup;

		// ファイル名の文字列を読み込み
		stream >> filename;

		// 敵座標の読み込み
		Vector2 pos;
		stream >> pos.x;
		stream >> pos.y;

		// 敵最終座標の読み込み
		Vector2 endPos;
		stream >> endPos.x;
		stream >> endPos.y;


		// 敵の移動速度の読み込み
		float SpdTime;
		stream >> SpdTime;

		// グループの最初の敵が動き始める時間と次の敵との移動時間差を読み込み
		int movetime;
		int GroupTime;
		stream >> movetime;
		stream >> GroupTime;

		// 敵体力の読み込み
		int HitPoint;
		stream >> HitPoint;

		int Interval;
		stream >> Interval;

		int BulletType;
		stream >> BulletType;

//__/__/__/__/__/__/１グループに必要なものを反映させる/__/__/__/__/__/__/__/__//
		for(int i = 0; i < EnemyGroup; i++)
		{
			// プロジェクトの基点からの相対パスでファイル名を補う
			filepath = L"Resources/" + filename + L".png";

			Enemy* enemy = new Enemy(device, filepath.c_str());
	
			enemy->SetPos(pos);

			// 敵が移動する距離を求める
			Vector2 move = endPos - pos;

			enemy->ENEMY_SPD = Vector2(move / SpdTime);

			enemy->SetMoveCnt(movetime + (i * GroupTime));

			enemy->SetHitPoint(HitPoint);

			enemy->SetInterval(Interval);

			enemy->BulletType = BulletType;

			m_Enemies.push_back(enemy);
		}
	}
}
