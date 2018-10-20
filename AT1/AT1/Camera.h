#pragma once
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#include <dinput.h>
#include "Renderer.h"

class Camera
{
public:
	Camera();
	~Camera();

	bool InitDirectInput(HINSTANCE appInstance, HWND appWindow);
	void DetectInput(float dt, HWND appWindow);
	void UpdateCamera();

	XMMATRIX GetCamView();

private:
	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;

	DIMOUSESTATE mouseLastState;
	LPDIRECTINPUT8 DirectInput;

	XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camUp;
	XMVECTOR camTarget;
	XMVECTOR camPosition = XMVectorSet(0.0f, 8.0f, -20.0f, 0.0f);

	XMMATRIX camView;
	XMMATRIX camRotationMatrix;
	XMMATRIX groundWorld;

	float moveLeftRight = 0.0f;
	float moveBackForward = 0.0f;

	float camYaw = 0.0f;
	float camPitch = 0.0f;

};