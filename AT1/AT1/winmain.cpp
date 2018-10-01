#include <windows.h>
#include "DXApp.h"
#include "Constants.h"
#include "winmain.h"

TestApp::TestApp(HINSTANCE hInstance) : DXApp(hInstance)
{
}

TestApp::~TestApp()
{
}

bool TestApp::Init()
{
	if (!DXApp::Init())
	{
		return false;
	}
	return true;
}

void TestApp::Update(float dt)
{
}

void TestApp::Render(float dt)
{
	renderer->GetDeviceContext()->ClearRenderTargetView(renderer->GetRenderTargetView(), DirectX::Colors::PaleVioletRed);
	renderer->GetSwapChain()->Present(0, 0);
}


int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	TestApp tApp(hInstance);
	if (!tApp.Init())
	{
		return 1;
	}
	return tApp.Run();
}