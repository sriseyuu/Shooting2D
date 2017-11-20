#include "LogoScene.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

LogoScene::LogoScene(ID3D11Device * device, ID3D11DeviceContext * context)
{
	cnt = 0;
	m_Logo.SetTexture(device, L"Resources/Logo.png");
	m_Logo.SetPos(Vector2(400, 300));

	CreateWICTextureFromFile(device, L"Resources/Dark.png", nullptr,
		m_texture.ReleaseAndGetAddressOf());
}

LogoScene::~LogoScene()
{
}

void LogoScene::Update()
{
	cnt++;
	Color color = Colors::White;

	color.w = sin((float)cnt / 120.0f);

	m_Logo.SetColor(color);

	if (cnt > 480)
	{
		Scene = 1;
	}
}

void LogoScene::Render(DirectX::SpriteBatch * spriteBatch)
{
	spriteBatch->Draw(m_texture.Get(), Vector2(0,0));
	m_Logo.Render(spriteBatch);
}
