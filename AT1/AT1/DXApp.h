#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include "DXUtil.h"
#include "Renderer.h"
#include "Triangle.h"

class DXApp
{
public:
	DXApp(HINSTANCE hInstance);
	virtual ~DXApp();

	//Loop
	int Run();

	//Framework
	virtual bool Init();
	virtual void Update(float dt) = 0;
	virtual void Render(float dt) = 0;
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	//Win32 Attributes
	HWND		appWindow;
	HINSTANCE	appInstance;
	DWORD		windowStyle;

	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Triangle> triangle;

protected:
	//Initialise Win32 window
	bool InitWindow();
};

