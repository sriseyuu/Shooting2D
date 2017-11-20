//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：SceneManager.h							
//													
// 概　　要：シーン管理のヘッダファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 17							
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

	// コンストラクタ
	SceneManager(ID3D11Device* device, ID3D11DeviceContext* context);
	// デストラクタ
	~SceneManager();

	// 更新処理
	void Update();
	// 描画処理
	void Render();

	// シーン変更処理
	void ChangeScene(int scene);

private:
	// シーン
	BaseScene* m_Scene;

	int m_NowScene;
	int m_NextScene;

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::CommonStates> m_states;

	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;
};
