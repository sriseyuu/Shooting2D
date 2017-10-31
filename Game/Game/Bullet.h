#pragma once

#include <SimpleMath.h>
#include "Sprite2D.h"
#include "Collision2D.h"

class Bullet
{
public:
	Bullet() {}
	// �R���X�g���N�^
	Bullet(ID3D11Device * device);

	// �f�X�g���N�^
	~Bullet() {}

	// �X�V����
	void Update();
	// �`�揈��
	void Render(DirectX::SpriteBatch* spriteBatch);

	// �e�̑�����ݒ�
	void SetSpd(DirectX::SimpleMath::Vector2 spd) { m_spd = spd; }
	// �e�̍��W�̎擾�Ɛݒ�
	DirectX::SimpleMath::Vector2 GetPos() { return m_sprite.GetPos(); }
	void SetPos(DirectX::SimpleMath::Vector2 pos) { m_sprite.SetPos(pos); }

	// �e�̉�]�p��ݒ�
	void SetRotation(float rot) { m_sprite.SetRotation(rot); }

	// �����蔻��̎擾
	Circle2D GetCollisionCircle() { return m_Collision; }

	// �X�v���C�g�̎擾�Ɛݒ�
	Sprite2D GetSprite() { return m_sprite; }
	void SetSprite(Sprite2D sprite) { m_sprite = sprite; }
private:

	// �e��2D�X�v���C�g
	Sprite2D m_sprite;
	// �e�̑���
	DirectX::SimpleMath::Vector2 m_spd;

	// �~�̓����蔻��
	Circle2D m_Collision;
};