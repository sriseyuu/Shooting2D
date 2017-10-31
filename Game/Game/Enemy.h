//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FEnemy.h							
//													
// �T�@�@�v�F�G�̃w�b�_�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 26							
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
public:
	enum BULLET_TYPE
	{
		TYPE_AROUND,
		TYPE_A,
	};

	float BULLET_SPD = 16.0f;
	DirectX::SimpleMath::Vector2 ENEMY_SPD = DirectX::SimpleMath::Vector2(0,0);

	Enemy() {}
	Enemy(ID3D11Device* device);
	Enemy(ID3D11Device* device, const wchar_t* filename);

	// �X�V����
	void Update();

	// �`�揈��
	void Render(DirectX::SpriteBatch* spriteBatch);

	Circle2D GetCollisionCircle() { return m_Collision; }

	// ���W�̐ݒ�Ǝ擾
	void SetPos(DirectX::SimpleMath::Vector2 pos) { m_sprite.SetPos(pos); }
	DirectX::SimpleMath::Vector2 GetPos() { return m_sprite.GetPos(); }

	void SetMoveCnt(int cnt) { m_MoveStartCnt = cnt; }

	std::vector<Bullet*> CreateBullets();

	bool isAttackEnemy() { return m_isAttack; }

private:
	// �J�E���g
	int cnt = 0;

	int m_MoveStartCnt = 0;

	// �G�X�v���C�g
	Sprite2D m_sprite;

	// �G�����蔻��
	Circle2D m_Collision;


	std::vector<Bullet*> m_Bullets;
	Sprite2D m_BulletSprite;

	bool m_isAttack = false;
};