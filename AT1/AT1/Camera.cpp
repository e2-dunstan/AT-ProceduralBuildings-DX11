#include "Camera.h"
#include "Constants.h"

Camera::Camera()
{
}

Camera::~Camera()
{
	DIKeyboard->Unacquire();
	DIMouse->Unacquire();
	DirectInput->Release();
}

bool Camera::InitDirectInput(HINSTANCE appInstance, HWND appWindow)
{
	HRESULT hr = DirectInput8Create(appInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&DirectInput,
		NULL);
	hr = DirectInput->CreateDevice(GUID_SysKeyboard,
		&DIKeyboard,
		NULL);
	hr = DirectInput->CreateDevice(GUID_SysMouse,
		&DIMouse,
		NULL);

	hr = DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = DIKeyboard->SetCooperativeLevel(appWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	hr = DIMouse->SetDataFormat(&c_dfDIMouse);
	hr = DIMouse->SetCooperativeLevel(appWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	return true;
}
void Camera::DetectInput(float dt, HWND appWindow)
{
	DIMOUSESTATE mouseCurrState;

	BYTE keyboardState[256];

	DIKeyboard->Acquire();
	DIMouse->Acquire();

	HRESULT result;

	result = DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);
	if (FAILED(result) && (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED))
	{
		DIMouse->Acquire();
	}
	result = DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
	if (FAILED(result) && (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED))
	{
		DIKeyboard->Acquire();
	}

	if ((keyboardState[DIK_ESCAPE] & 0x80) && !keyboardState[DIK_LWIN])
		PostMessage(appWindow, WM_DESTROY, 0, 0);

	float speed = 15.0f * dt;

	if (keyboardState[DIK_A] & 0x80)
	{
		moveLeftRight -= speed;
	}
	if (keyboardState[DIK_D] & 0x80)
	{
		moveLeftRight += speed;
	}
	if (keyboardState[DIK_W] & 0x80)
	{
		moveBackForward += speed;
	}
	if (keyboardState[DIK_S] & 0x80)
	{
		moveBackForward -= speed;
	}

	if (keyboardState[DIK_Q])
	{
		lockCamera = true;
	}
	if (keyboardState[DIK_E])
	{
		lockCamera = false;
	}

	if ((mouseCurrState.lX != mouseLastState.lX) || (mouseCurrState.lY != mouseLastState.lY))
	{
		camYaw += mouseLastState.lX * 0.001f;

		camPitch += mouseCurrState.lY * 0.001f;

		mouseLastState = mouseCurrState;
	}

	if (!lockCamera)
		UpdateCamera();
}

void Camera::UpdateCamera()
{
	camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
	camTarget = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	camTarget = XMVector3Normalize(camTarget);

	camRight = XMVector3TransformCoord(DefaultRight, camRotationMatrix);
	camForward = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	camUp = XMVector3Cross(camForward, camRight);

	camPosition += moveLeftRight * camRight;
	camPosition += moveBackForward * camForward;

	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;

	camTarget = camPosition + camTarget;

	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
	camProjection = XMMatrixPerspectiveFovLH(0.4f*3.14f, (float)windowWidth / windowHeight, 1.0f, 1000.0f);
}

XMMATRIX Camera::GetCamView()
{
	return camView;
}

XMMATRIX Camera::GetCamProjection()
{
	return camProjection;
}
