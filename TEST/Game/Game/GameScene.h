//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FGameScene.h							
//													
// �T�@�@�v�F�Q�[���V�[���̃w�b�_�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 25						
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include "BaseScene.h"
#include "Sprite2D.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class GameScene : public BaseScene
{
private:

	// �G�̃��[�h
	void LoadCSV(ID3D11Device* device);
//__/__/__/__/__/__/__/__/__/�e�֌W__/__/__/__/__/__/__/__/__/

	// ��ʊO�ɍs������e������
	void ScreenOut(std::vector<Bullet*>& bullet);
	// �e�̍X�V����
	void BulletUpdate(std::vector<Bullet*> bullet);
	// �v���C���̒e����
	void SetPlayerBullet();
	// �G�̒e����
	void SetEnemyBullet(std::vector<Enemy*>::iterator itr);
	// �v���C���ƒe�̓����蔻��
	void CollisionBullet_Player(std::vector<Bullet*> & bullet1, Player* & Player);
	// �G�ƒe�̓����蔻��	
	void CollisionBullet_Enemy(std::vector<Bullet*> & bullet, std::vector<Enemy*> & Enemies);
public:
	GameScene()	: BaseScene() {} 
	GameScene(ID3D11Device* device,ID3D11DeviceContext* context);
	~GameScene();
	void Update();
	void Render(DirectX::SpriteBatch* spriteBatch);



//__/__/__/__/__/__/__/__/__/�����o�ϐ�__/__/__/__/__/__/__/__/
private:
	Player* m_Player;
	std::vector<Bullet*> m_PlayerBullets;

	std::vector<Enemy*> m_Enemies;
	std::vector<Bullet*> m_EnemyBullets;
};