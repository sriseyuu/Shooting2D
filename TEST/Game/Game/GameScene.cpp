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
	// �G���o�Ă��鐔�����X�V�����s��
	for (std::vector<Enemy*>::iterator itr = m_Enemies.begin(); itr != m_Enemies.end(); itr++)
	{
		(*itr)->Update();
	}

	// �v���C�����o�Ă���ꍇ�v���C���̍X�V�������s��
	if (m_Player != nullptr)
		m_Player->Update(KeyState);

	// �G�����Ȃ���Γ��Ă�K�v���Ȃ�
	if (m_Enemies.size() > 0)
	{
		std::vector<Enemy*>::iterator eItr = m_Enemies.begin();
		while (eItr != m_Enemies.end())
		{
			// �v���C�������݂��Ȃ���Γ�����Ȃ��̂ł����瓖�����Ă��邩������
			if (m_Player != nullptr)
			{
				// �v���C���ƓG�̔���
				if (OnCollision2DCircle_Circle((*eItr)->GetCollisionCircle(), m_Player->GetCollisionCircle()))
				{
					eItr = m_Enemies.erase(eItr);
					break;
				}
				// �v���C�����e�𔭎˂��Ă��Ȃ�������ʂ�Ȃ�
				else if (m_Player->GetBullet().size() > 0)
				{
					// �v���C���̒e�ƓG�̓����蔻��
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
					// �G���e�𔭎˂��Ă��Ȃ�������ʂ�Ȃ�
					std::vector<Bullet>::iterator eBullet = (*eItr)->GetBullet().begin();
					while (eBullet != (*eItr)->GetBullet().end())
					{

						// �G�̒e�ƃv���C���̓����蔻��
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
						// �e���ŏ����猩��
						eBullet = (*eItr)->GetBullet().begin();

						while (eBullet != (*eItr)->GetBullet().end())
						{
							std::vector<Bullet>::iterator pBullet = m_Player->GetBullet().begin();
							if (m_Player->GetBullet().size() > 0)
							{
								while (pBullet != m_Player->GetBullet().end())
								{
									// �G�̒e�ƃv���C���̒e�̓����蔻��
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
