#include "TitleScene.h"
#include <WICTextureLoader.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

TitleScene::TitleScene(ID3D11Device * device, ID3D11DeviceContext * context)
	:BaseScene()
{
	CreateWICTextureFromFile(device,L"Resources/TitleBackground.png",nullptr,m_texture.ReleaseAndGetAddressOf());
}

void TitleScene::Update()
{
	auto KeyState = keyboard->GetState();
	if (KeyState.IsKeyDown(Keyboard::Keys::Enter))
	{
		
	}
}

void TitleScene::Render(DirectX::SpriteBatch * spriteBatch)
{
	spriteBatch->Draw(m_texture.Get(), Vector2(0, 0), Colors::White);
}
