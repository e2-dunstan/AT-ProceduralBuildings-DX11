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

	//https://www.braynzarsoft.net/viewtutorial/q16390-9-transformations


void TestApp::Render(float dt)
{
	renderer->DrawScene();
	//model->Draw(*renderer);
	renderer->EndFrame();
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