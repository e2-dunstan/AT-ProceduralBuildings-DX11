#pragma once
#include "DXUtil.h"

using namespace DirectX;

struct Light
{
	Light()
	{
		ZeroMemory(this, sizeof(Light));
	}
	XMFLOAT3 direction;
	float padding;
	XMFLOAT4 ambientColour;
	XMFLOAT4 diffuseColour;
};

class LightClass
{
public:
	LightClass();
	~LightClass() = default;

	Light GetLight();

private:

	Light light;

};