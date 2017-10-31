//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FGameScene.cpp							
//													
// �T�@�@�v�F�Q�[���V�[���̃\�[�X�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 26							
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
	// �L�[�̔���
	auto KeyState = keyboard->GetState();

	//__/__/__/__/__/�X�V�����n/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

	// �G���o�Ă��鐔�����X�V�����s��
	for (std::vector<Enemy*>::iterator itr = m_Enemies.begin(); itr != m_Enemies.end(); itr++)
	{
		(*itr)->Update();
		// �U���\�Ȃ�e�𔭎˂���
		if ((*itr)->isAttackEnemy())
		{
			SetEnemyBullet(itr);
		}
	}

	// �v���C�����o�Ă���ꍇ�v���C���̍X�V�������s��
	if (m_Player != nullptr) {
		m_Player->Update(KeyState);
		// �U���\�Ȃ�e�𔭎˂���
		if (m_Player->isAttackPlayer())
		{
			SetPlayerBullet();
		}
	}
	BulletUpdate(m_PlayerBullets);
	BulletUpdate(m_EnemyBullets);

	ScreenOut(m_PlayerBullets);
	ScreenOut(m_EnemyBullets);

//__/__/__/__/__/�����蔻�菈��/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

	CollisionBullet_Player(m_EnemyBullets,m_Player);
	CollisionBullet_Enemy(m_PlayerBullets,m_Enemies);

	// ���œG�ƓG�̒e���S�ď�������Q�[�����I������
	if (m_Enemies.empty() && m_EnemyBullets.empty())
	{
		exit(1);
	}
}

void GameScene::Render(SpriteBatch* spriteBatch)
{
	if (m_Player != nullptr)
	{
		m_Player->Render(spriteBatch);
	}
	for (std::vector<Bullet*>::iterator itr = m_PlayerBullets.begin(); itr != m_PlayerBullets.end(); itr++)
	{
		(*itr)->Render(spriteBatch);
	}
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

		if ((*it)->GetPos().y < -32 ||
			(*it)->GetPos().y > 632 ||
			(*it)->GetPos().x < -32 ||
			(*it)->GetPos().x > 832)
		{
			it = bullet.erase(it);
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
				// delete m_Player;
				// m_Player = nullptr;
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
						itr = Enemies.erase(itr);
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

void GameScene::LoadCSV(ID3D11Device* device)
{
	// csv�t�H���_���Ă�
	std::wifstream ifs("CSV/Enemy1.csv");

	std::wstring line;

	// 1�s�ڂ��X�L�b�v
	getline(ifs, line);

	// ���납��f�[�^�����
	while (getline(ifs, line)) 
	{
		std::wstring filepath;
		std::wstring filename;

		wchar_t del = L',';
		// �J���}���󔒂ɒu������
		std::replace(line.begin(), line.end(), L',', L' ');

		// 1�s���𕶎���X�g���[���ɕϊ�
		std::wistringstream stream(line);

		// �t�@�C�����̕������ǂݍ���
		stream >> filename;
		// �v���W�F�N�g�̊�_����̑��΃p�X�Ńt�@�C������₤
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
