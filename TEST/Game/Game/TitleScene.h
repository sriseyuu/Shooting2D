//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：GameScene.h							
//													
// 概　　要：ゲームシーンのヘッダファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 25						
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include "BaseScene.h"
#include "Sprite2D.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class TitleScene : public BaseScene
{
public:
	TitleScene() : BaseScene() {}
	TitleScene(ID3D11Device* device, ID3D11DeviceContext* context);
	~TitleScene() {}
	void Update();
	void Render(DirectX::SpriteBatch* spriteBatch);

private:

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

};