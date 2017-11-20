#pragma once
#include "BaseScene.h"
#include "Sprite2D.h"

class LogoScene : public BaseScene
{
public:
	LogoScene() {}
	LogoScene(ID3D11Device* device, ID3D11DeviceContext* context);
	~LogoScene();

	void Update();
	void Render(DirectX::SpriteBatch* spriteBatch);

private:
	int cnt;
	Sprite2D m_Logo;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};
