#include "Light.h"

LightClass::LightClass()
{
	light.direction = XMFLOAT3(0.25f, 0.5f, -1.0f);
	light.ambientColour = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	light.diffuseColour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
}

Light LightClass::GetLight()
{
	return light;
}
