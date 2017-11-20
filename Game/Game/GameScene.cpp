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
	// �L�[�̔���
	auto KeyState = m_Keyboard->GetState();
	auto Padstate = m_GamePad->GetState(0);

	//__/__/__/__/__/�X�V�����n/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
	
	m_Obstacle->Translate(m_ObstacleSpd);
	m_Obstacle->Update();

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
		m_Player->Update(KeyState, Padstate);
		// �U���\�Ȃ�e�𔭎˂���
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

//__/__/__/__/__/�����蔻�菈��/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

	CollisionBullet_Player(m_EnemyBullets,m_Player);
	CollisionBullet_Enemy(m_PlayerBullets,m_Enemies);
	CollisionBullet_Obstacle(m_EnemyBullets,m_Obstacle);
	CollisionBullet_Obstacle(m_PlayerBullets, m_Obstacle);

	BackgroundY += 0.5f;
	if (BackgroundY > 600) 
	{
		BackgroundY = 0;
	}

	// ���œG�ƓG�̒e���S�ď�������Q�[�����I������
	if (m_Enemies.empty() && m_EnemyBullets.empty())
	{
		Scene = 1;
	}
}

void GameScene::Render(SpriteBatch* spriteBatch)
{
	// �w�i�`��
	spriteBatch->Draw(m_Background.Get(), Vector2(0, BackgroundY), Colors::White);
	spriteBatch->Draw(m_Background.Get(), Vector2(0, BackgroundY - 600), Colors::White);
	// ��Q���`��
	m_Obstacle->Render(spriteBatch);
	// �v���C���֌W�̕`��
	if (m_Player != nullptr)
	{
		m_Player->Render(spriteBatch);
	}
	for (std::vector<Bullet*>::iterator itr = m_PlayerBullets.begin(); itr != m_PlayerBullets.end(); itr++)
	{
		(*itr)->Render(spriteBatch);
	}
	// �G�֌W�̕`��
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
		// �ړ��������������������ʊO�֏o���Ƃ��ɓG���폜����
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
	// csv�t�H���_���Ă�
	std::wifstream ifs("CSV/EnemyTest.csv");

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

//__/__/__/__/__/__/�P�O���[�v�ɕK�v�Ȃ��̂̓ǂݍ���/__/__/__/__/__/__/__/__//

		// �P�O���[�v���̓G�̐���ǂݍ���
		int EnemyGroup;
		stream >> EnemyGroup;

		// �t�@�C�����̕������ǂݍ���
		stream >> filename;

		// �G���W�̓ǂݍ���
		Vector2 pos;
		stream >> pos.x;
		stream >> pos.y;

		// �G�ŏI���W�̓ǂݍ���
		Vector2 endPos;
		stream >> endPos.x;
		stream >> endPos.y;


		// �G�̈ړ����x�̓ǂݍ���
		float SpdTime;
		stream >> SpdTime;

		// �O���[�v�̍ŏ��̓G�������n�߂鎞�ԂƎ��̓G�Ƃ̈ړ����ԍ���ǂݍ���
		int movetime;
		int GroupTime;
		stream >> movetime;
		stream >> GroupTime;

		// �G�̗͂̓ǂݍ���
		int HitPoint;
		stream >> HitPoint;

		int Interval;
		stream >> Interval;

		int BulletType;
		stream >> BulletType;

//__/__/__/__/__/__/�P�O���[�v�ɕK�v�Ȃ��̂𔽉f������/__/__/__/__/__/__/__/__//
		for(int i = 0; i < EnemyGroup; i++)
		{
			// �v���W�F�N�g�̊�_����̑��΃p�X�Ńt�@�C������₤
			filepath = L"Resources/" + filename + L".png";

			Enemy* enemy = new Enemy(device, filepath.c_str());
	
			enemy->SetPos(pos);

			// �G���ړ����鋗�������߂�
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
