//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FSceneManager.h							
//													
// �T�@�@�v�F�V�[���Ǘ��̃w�b�_�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 17							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

#include <windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>

#include <SimpleMath.h>
#include <SpriteBatch.h>

#include <CommonStates.h>

#include "BaseScene.h"
#include "LogoScene.h"
#include "TitleScene.h"
#include "GameScene.h"

class SceneManager
{
public:
	enum SCENE
	{
		SCENE_LOGO,
		SCENE_TITLE,
		SCENE_GAME,
	};

	// �R���X�g���N�^
	SceneManager(ID3D11Device* device, ID3D11DeviceContext* context);
	// �f�X�g���N�^
	~SceneManager();

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

	// �V�[���ύX����
	void ChangeScene(int scene);

private:
	// �V�[��
	BaseScene* m_Scene;

	int m_NowScene;
	int m_NextScene;

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::CommonStates> m_states;

	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;
};
