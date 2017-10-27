//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FSceneManager.cpp						
//													
// �T�@�@�v�F�V�[���Ǘ��̃\�[�X�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 17							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "SceneManager.h"

using namespace DirectX;

SceneManager::SceneManager(ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_device = device;
	m_context = context;

	m_spriteBatch = std::make_unique<SpriteBatch>(m_context);

	m_states = std::make_unique<CommonStates>(m_device);

	m_Scene = nullptr;

	m_NextScene = SCENE_GAME;
	m_NowScene = m_NextScene;

	ChangeScene(m_NowScene);

}

SceneManager::~SceneManager()
{
}

void SceneManager::Update()
{
	m_Scene->Update();

	if (m_NowScene != m_NextScene)
	{
		ChangeScene(m_NextScene);
		m_NowScene = m_NextScene;
	}
}

void SceneManager::Render()
{
	m_spriteBatch->Begin();
	
	m_Scene->Render(m_spriteBatch.get());

	m_spriteBatch->End();
}

void SceneManager::ChangeScene(SCENE scene)
{
	if (m_Scene != nullptr)
	{
		delete m_Scene;
	}

	switch (scene)
	{
	case SCENE_TITLE:

		break;
	case SCENE_GAME:
		m_Scene = new GameScene(m_device, m_context);
		break;
	default:
		break;
	}
}
