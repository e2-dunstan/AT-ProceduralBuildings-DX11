#pragma once
#include "Renderer.h"

class Texture
{
public:
	Texture();
	~Texture();

	ID3D11ShaderResourceView* t;
	ID3D11SamplerState* tSamplerState;


};