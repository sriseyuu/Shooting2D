#include "Sprite2D.h"
#include <WICTextureLoader.h>

using namespace DirectX;

void Sprite2D::SetTexture(ID3D11Device* device, const wchar_t* filename)
{
	CreateWICTextureFromFile(device, filename, nullptr,
		m_texture.ReleaseAndGetAddressOf());
}

void Sprite2D::Update()
{

}

void Sprite2D::Render(DirectX::SpriteBatch* spriteBatch)
{
	spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White,
		0.f, m_origin);
}
