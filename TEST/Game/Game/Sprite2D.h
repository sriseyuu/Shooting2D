//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FSprite2D.h							
//													
// �T�@�@�v�F2D�X�v���C�g�̃w�b�_�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 24							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include <windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>

#include <SimpleMath.h>
#include <SpriteBatch.h>

#include <CommonStates.h>

#include <WICTextureLoader.h>

class Sprite2D
{
public:
	~Sprite2D();

	// �e�N�X�`���̐ݒ�
	void SetTexture(ID3D11Device* device, const wchar_t* filename);
	void SetTexture(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture);

	virtual void Update();

	virtual void Render(DirectX::SpriteBatch* spriteBatch);

	// �摜�̍��W�̎擾�Ɛݒ�
	void SetPos(DirectX::SimpleMath::Vector2 pos) { m_screenPos = pos; }
	void SetPos(float posx, float posy) { m_screenPos = DirectX::SimpleMath::Vector2(posx, posy); }
	DirectX::SimpleMath::Vector2 GetPos() { return m_screenPos; }

	// ��]�p�̐ݒ�
	void SetRotation(float rot) { m_rot = rot; }

	// �摜�̑傫���̎擾
	DirectX::SimpleMath::Vector2 GetTextureSize() { return m_origin * 2; }

	// �v���C���̃t���[���ړ�(�����F�ړ�����)
	void Translate(DirectX::SimpleMath::Vector2 vec);
	// �v���C���̃t���[����]
	void Rotate(float rot) { m_rot += rot; }
	
	void SetColor(DirectX::SimpleMath::Color color) { col = color; }
private:
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// ���W
	DirectX::SimpleMath::Vector2 m_screenPos;
	// ���S���W
	DirectX::SimpleMath::Vector2 m_origin;
	// ��]�p
	float m_rot = 0.0f;
	// iro
	DirectX::SimpleMath::Color col = DirectX::Colors::White;
};