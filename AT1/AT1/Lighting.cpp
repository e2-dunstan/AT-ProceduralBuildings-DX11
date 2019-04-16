#include "Lighting.h"

void Lighting::SetDiffuseColor(float r, float g, float b, float a)
{
	diffuseColor = { r, g, b, a };
}

void Lighting::SetDirection(float x, float y, float z)
{
	direction = { x, y, z };
}

XMVECTOR Lighting::GetDiffuseColor()
{
	return diffuseColor;
}

XMVECTOR Lighting::GetDirection()
{
	return direction;
}
