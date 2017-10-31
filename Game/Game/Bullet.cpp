#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(ID3D11Device* device)
	: m_sprite()
{
	m_sprite.SetTexture(device,L"Resources/Bullet.png");

	m_Collision.m_pos = m_sprite.GetPos();
	m_Collision.m_Radius = m_sprite.GetTextureSize().x / 2;
}

void Bullet::Update()
{
	m_sprite.Translate(m_spd);

	m_Collision.m_pos = m_sprite.GetPos();
}

void Bullet::Render(DirectX::SpriteBatch * spriteBatch)
{
	m_sprite.Render(spriteBatch);
}

