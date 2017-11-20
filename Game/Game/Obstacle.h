#pragma once
#include "Sprite2D.h"
#include "Collision2D.h"

class Obstacle : public Sprite2D
{
public:
	Obstacle() : Sprite2D() {  }
	void Update() override;

	Circle2D GetCollisionCircle() { return m_Collision; }
	void SetCollisionTex() { m_Collision.m_Radius = GetTextureSize().x / 2; m_Collision.m_pos = GetPos(); }

private:
	Circle2D m_Collision;
};