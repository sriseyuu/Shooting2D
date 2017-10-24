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
class Sprite2D
{
public:
	// �e�N�X�`���̐ݒ�
	void SetTexture(ID3D11Device* device, const wchar_t* filename);

	void Update();

	void Render(DirectX::SpriteBatch* spriteBatch);

	// �摜�̍��W�̎擾�Ɛݒ�
	void SetPos(DirectX::SimpleMath::Vector2 pos) { m_screenPos = pos; }
	DirectX::SimpleMath::Vector3 GetPos() { return m_screenPos; }

	void Translate(DirectX::SimpleMath::Vector2 vec) { m_screenPos += vec; }
private:
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// ���W
	DirectX::SimpleMath::Vector2 m_screenPos;
	// 
	DirectX::SimpleMath::Vector2 m_origin;
};