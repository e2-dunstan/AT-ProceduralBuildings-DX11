#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include "DXUtil.h"
#include "Renderer.h"
#include "Model.h"

class DXApp
{
public:
	DXApp(HINSTANCE hInstance);
	virtual ~DXApp();

	//Loop
	int Run();

	//Framework
	virtual bool Init();
	virtual void Update(float dt);
	virtual void Render(float dt);
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	//Win32 Attributes
	HWND		appWindow;
	HINSTANCE	appInstance;
	DWORD		windowStyle;

	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Model> model;

protected:
	//Initialise Win32 window
	bool InitWindow();

private:
	XMMATRIX cube1World;
	XMMATRIX cube2World;

	XMMATRIX Rotation;
	XMMATRIX Scale;
	XMMATRIX Translation;
	float rot = 0.01f;
};

