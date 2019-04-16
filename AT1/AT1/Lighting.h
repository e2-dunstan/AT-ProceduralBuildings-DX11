#pragma once
#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_

#include "DXUtil.h"

using namespace DirectX;

class Lighting
{
public:
	Lighting() = default;
	Lighting(const Lighting&) = default;
	~Lighting() = default;

	void SetDiffuseColor(float r, float g, float b, float a);
	void SetDirection(float x, float y, float z);

	XMVECTOR GetDiffuseColor();
	XMVECTOR GetDirection();

private:
	XMVECTOR diffuseColor;
	XMVECTOR direction;
};

#endif