#include "Obstacle.h"

void Obstacle::Update()
{
	Sprite2D::Update();

	m_Collision.m_pos = GetPos();
}
