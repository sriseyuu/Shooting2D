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
}

GameScene::~GameScene()
{
	delete m_Player;
	m_Player = nullptr;

}

void GameScene::Update()
{
	// キーの判定
	auto KeyState = keyboard->GetState();
	// 敵が出ている数だけ更新処理行う
	for (std::vector<Enemy*>::iterator itr = m_Enemies.begin(); itr != m_Enemies.end(); itr++)
	{
		(*itr)->Update();
	}

	// プレイヤが出ている場合プレイヤの更新処理を行う
	if (m_Player != nullptr)
		m_Player->Update(KeyState);

	// 敵がいなければ当てる必要がない
	if (m_Enemies.size() > 0)
	{
		std::vector<Enemy*>::iterator eItr = m_Enemies.begin();
		while (eItr != m_Enemies.end())
		{
			// プレイヤが存在しなければ当たらないのでいたら当たっているかを見る
			if (m_Player != nullptr)
			{
				// プレイヤと敵の判定
				if (OnCollision2DCircle_Circle((*eItr)->GetCollisionCircle(), m_Player->GetCollisionCircle()))
				{
					eItr = m_Enemies.erase(eItr);
					break;
				}
				// プレイヤが弾を発射していなかったら通らない
				else if (m_Player->GetBullet().size() > 0)
				{
					// プレイヤの弾と敵の当たり判定
					std::vector<Bullet>::iterator pBullet = m_Player->GetBullet().begin();
					while (pBullet != m_Player->GetBullet().end())
					{
						if (OnCollision2DCircle_Circle(pBullet->GetCollisionCircle(), (*eItr)->GetCollisionCircle()))
						{
							//delete m_Enemy;
							//m_Enemy = nullptr;

							pBullet = m_Player->GetBullet().erase(pBullet);
							//break;
						}
						else {
							pBullet++;
						}
					}
				}
				if ((*eItr)->GetBullet().size() > 0)
				{
					// 敵が弾を発射していなかったら通らない
					std::vector<Bullet>::iterator eBullet = (*eItr)->GetBullet().begin();
					while (eBullet != (*eItr)->GetBullet().end())
					{

						// 敵の弾とプレイヤの当たり判定
						if (OnCollision2DCircle_Circle(eBullet->GetCollisionCircle(), m_Player->GetCollisionCircle()))
						{
							//delete m_Enemy;
							//m_Enemy = nullptr;

							eBullet = (*eItr)->GetBullet().erase(eBullet);
							//break;
						}
						else {
							eBullet++;
						}
					}

					if ((*eItr)->GetBullet().size() > 0) 
					{
						// 弾を最初から見る
						eBullet = (*eItr)->GetBullet().begin();

						while (eBullet != (*eItr)->GetBullet().end())
						{
							std::vector<Bullet>::iterator pBullet = m_Player->GetBullet().begin();
							if (m_Player->GetBullet().size() > 0)
							{
								while (pBullet != m_Player->GetBullet().end())
								{
									// 敵の弾とプレイヤの弾の当たり判定
									if (OnCollision2DCircle_Circle(eBullet->GetCollisionCircle(), pBullet->GetCollisionCircle()))
									{
										//delete m_Enemy;
										//m_Enemy = nullptr;

										eBullet = (*eItr)->GetBullet().erase(eBullet);
										pBullet = m_Player->GetBullet().erase(pBullet);
										eBullet--;
									}
									else {
										pBullet++;
									}
								}

							}
							eBullet++;
						}
					}
				}
				eItr++;
			}
		}
	}
}

void GameScene::Render(SpriteBatch* spriteBatch)
{
	for (std::vector<Enemy*>::iterator itr = m_Enemies.begin(); itr != m_Enemies.end(); itr++)
	{
		(*itr)->Render(spriteBatch);
	}

	if (m_Player != nullptr)
	m_Player->Render(spriteBatch);
}

void GameScene::LoadCSV(ID3D11Device* device)
{
	// csvフォルダを呼ぶ
	std::wifstream ifs("CSV/Enemy1.csv");

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

		// ファイル名の文字列を読み込み
		stream >> filename;
		// プロジェクトの基点からの相対パスでファイル名を補う
		filepath = L"Resources/" + filename + L".png";

		Enemy* enemy = new Enemy(device, filepath.c_str());
		Vector2 pos;

		stream >> pos.x;
		stream >> pos.y;

		enemy->SetPos(pos);

		Vector2 endPos;
		stream >> endPos.x;
		stream >> endPos.y;

		float SpdTime;
		stream >> SpdTime;

		SpdTime *= 60.0f;

		Vector2 move = endPos - pos;

		enemy->ENEMY_SPD = Vector2(move / SpdTime);

		int movetime;

		stream >> movetime;

		enemy->SetMoveCnt(movetime);

		m_Enemies.push_back(enemy);
	}
}
