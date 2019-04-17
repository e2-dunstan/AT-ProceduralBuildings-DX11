#include "DXApp.h"
#include "Constants.h"
#include <dwrite.h>
#include "BuildingGenerator.h"

// -- TO DO -- //
// [x] Height of door and make the generation of it more consistent
// [ ] Normal maps? Would require lighting too
// [ ] Export multiple textures
// -- -- -- -- //

std::unique_ptr<BuildingGenerator> generator = std::unique_ptr<BuildingGenerator>(new BuildingGenerator);

namespace
{
	//used to forward messages to user defined procedure function
	DXApp* globalApp = nullptr;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (globalApp)
	{
		return globalApp->MsgProc(hwnd, msg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	generator->TerminateTweakBar();
}

DXApp::DXApp(HINSTANCE hInstance)
{
	appInstance = hInstance;
	appWindow = NULL;
	windowStyle = WS_OVERLAPPEDWINDOW;
	globalApp = this;

	textureFiles[0] = "chiseled_red_sandstone.tga";
	textureFiles[1] = "coal_block.tga";
	textureFiles[2] = "daylight_detector_top.tga";
	textureFiles[3] = "lapis_ore.tga";
	textureFiles[4] = "light_gray_terracotta.tga";
	textureFiles[5] = "lime_terracotta.tga";
	textureFiles[6] = "mycelium_top.tga";
	textureFiles[7] = "nether_wart_block.tga";
	textureFiles[8] = "purpur_pillar.tga";
	textureFiles[9] = "red_nether_bricks.tga";
	textureFiles[10] = "red_sandstone.tga";
	textureFiles[11] = "George_Foreman.tga";
}

DXApp::~DXApp()
{
}

int DXApp::Run()
{
	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			frameCount++;
			if (GetTime() > 1.0f)
			{
				fps = frameCount;
				frameCount = 0;
				StartTimer();
			}

			frameTime = GetFrameTime();

			Update(frameTime);
			Render(frameTime);
		}
	}
	return static_cast<int>(msg.wParam);
}

bool DXApp::Init()
{
	if (!InitWindow())
	{
		return false;
	}	
	
	renderer = std::unique_ptr<Renderer>(new Renderer);
	if (!renderer->InitDirect3D(appWindow))
	{
		MessageBox(0, (LPCSTR)L"Direct3D Initialization - Failed",
			(LPCSTR)L"Error", MB_OK);
		return false;
	}
	renderer->InitView();

	camera = std::unique_ptr<Camera>(new Camera);
	if (!camera->InitDirectInput(appInstance, appWindow))
	{
		MessageBox(0, (LPCSTR)L"Direct Input Initialization - Failed",
			(LPCSTR)L"Error", MB_OK);
		return false;
	}

	// -- CREATE MODELS -- //
	GenerateNewBuilding();

	exporter = std::unique_ptr<OBJExporter>(new OBJExporter);

	InitTextureTweakBar();

	return true;
}

void TW_CALL ReloadTextures(void *clientData)
{
	DXApp* app = static_cast<DXApp*>(clientData);

	app->ResetTextures();
}

void DXApp::InitTextureTweakBar()
{
	textureTweakBar = TwNewBar("Textures");
	TwWindowSize(1280, 720);
	int tweakBarSize[2] = { 200, 400 };
	TwSetParam(textureTweakBar, NULL, "size", TW_PARAM_INT32, 2, tweakBarSize);

	TwAddVarRW(textureTweakBar, "Floors", TW_TYPE_INT32, &floorTex, "min=0 max=10 step=1");
	TwAddVarRW(textureTweakBar, "Corners", TW_TYPE_INT32, &cornerTex, "min=0 max=10 step=1");
	TwAddVarRW(textureTweakBar, "Walls", TW_TYPE_INT32, &wallTex, "min=0 max=10 step=1");
	TwAddVarRW(textureTweakBar, "Windows", TW_TYPE_INT32, &windowTex, "min=0 max=10 step=1");
	TwAddVarRW(textureTweakBar, "Door", TW_TYPE_INT32, &doorTex, "min=0 max=10 step=1");
	TwAddVarRW(textureTweakBar, "Roof", TW_TYPE_INT32, &roofTex, "min=0 max=10 step=1");

	TwAddButton(textureTweakBar, "Reload textures", ReloadTextures, this, " label='Reload textures'");
}

void DXApp::GenerateNewBuilding()
{
	generator->Init();
	if (!tweakBarInitialised)
	{
		generator->InitTweakBar(*renderer);
		tweakBarInitialised = true;
	}

	allModels = generator->GetModels();

	ResetTextures();
}

void DXApp::SetTransforms(int i)
{
	//Initialise and reset
	if (allModelTransforms.size() != allModels.size())
		allModelTransforms.push_back(XMMatrixIdentity());
	else
		allModelTransforms[i] = XMMatrixIdentity();

	XMVECTOR rotAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	Rotation = XMMatrixRotationAxis(rotAxis, allModels[i]->GetRotation());
	Translation = XMMatrixTranslation(allModels[i]->GetPosition().x,
		allModels[i]->GetPosition().y,
		allModels[i]->GetPosition().z);
	Scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	allModelTransforms[i] = Scale * Rotation * Translation;
}

void DXApp::ResetTextures()
{
	for (int i = 0; i < allModels.size(); i++)
	{
		SetModelTexture(i);

		std::string str = "Resources/" + allModels[i]->GetTextureString();
		char *cstr = &str[0u];

		if (!allModels[i]->InitModel(*renderer, cstr,
			appWindow))
		{
			MessageBox(0, (LPCSTR)L"Model Initialization - Failed",
				(LPCSTR)L"Error", MB_OK);
		}
		SetTransforms(i);
	}
}

void DXApp::SetModelTexture(int i)
{
	if (i == 0)
	{
		allModels[i]->SetTextureString(std::string(textureFiles[6]));
	}
	else
	{
		switch (allModels[i]->GetType())
		{
		case Type::FLOOR:
			allModels[i]->SetTextureString(std::string(textureFiles[floorTex]));
			break;
		case Type::CORNER:
			allModels[i]->SetTextureString(std::string(textureFiles[cornerTex]));
			break;
		case Type::WALL:
			allModels[i]->SetTextureString(std::string(textureFiles[wallTex]));
			break;
		case Type::INTERIOR_WALL:
			allModels[i]->SetTextureString(std::string(textureFiles[wallTex]));
			break;
		case Type::WINDOW:
			allModels[i]->SetTextureString(std::string(textureFiles[windowTex]));
			break;
		case Type::DOOR:
			allModels[i]->SetTextureString(std::string(textureFiles[doorTex]));
			break;
		case Type::ROOF_FLAT:
			allModels[i]->SetTextureString(std::string(textureFiles[roofTex]));
			break;
		case Type::ROOF_PYRAMID:
			allModels[i]->SetTextureString(std::string(textureFiles[roofTex]));
			break;
		case Type::ROOF_SHED:
			allModels[i]->SetTextureString(std::string(textureFiles[roofTex]));
			break;
		case Type::OBJECT:
			break;
		default:
			allModels[i]->SetTextureString(std::string(textureFiles[11]));
			break;
		}
	}
}

void DXApp::Update(double dt)
{
	camera->DetectInput(dt, appWindow);

	//Stops it from updating every frame
	if (generator->ValuesChanged())
	{
		allModels.clear();
		allModelTransforms.clear();

		GenerateNewBuilding();
		renderer->SetModelTransforms(allModelTransforms);

		generator->SetValuesChanged(false);
	}
	if (generator->CreateNewObj())
	{
		//--CREATE OBJ--//
		exporter->SetModels(allModels);
		exporter->SetTransforms(allModelTransforms);
		exporter->Create();
		generator->SetCreateNewObj(false);
	}
}

void DXApp::Render(double dt)
{
	renderer->DrawBackground();
	for (int i = 0; i < allModels.size(); i++)
	{
		allModels[i]->UpdateBuffers(*renderer);

		if (allModels[i]->GetType() == Type::FLOOR
			|| allModels[i]->GetType() == Type::ROOF_PYRAMID
			|| allModels[i]->GetType() == Type::ROOF_SHED)
		{
			renderer->SetRasterizerState(1);
			renderer->SetBlendState(1);
		}
		else if (allModels[i]->GetType() == Type::WINDOW)
		{
			renderer->SetRasterizerState(0);
			renderer->SetBlendState(1);
		}
		else
		{
			renderer->SetRasterizerState(0);
			renderer->SetBlendState(1);
		}

		renderer->DrawModel(allModels[i]->GetTexture(), allModels[i]->GetTexturePointer()->GetSamplerState(),
			camera->GetCamView(), camera->GetCamProjection(), i, allModels[i]->GetIndices().size());
	}

	// -- DRAW THE TWEAK BAR -- //
	generator->DrawTweakBar();
	renderer->EndFrame();
}

bool DXApp::InitWindow()
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = appInstance;
	wcex.lpfnWndProc = MainWndProc;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "DXAPPWNDCLASS";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		OutputDebugString("FAILED TO CREATE WINDOW CLASS \nDXApp.cpp InitWindow()");
		return false;
	}

	RECT r = { 0,0, windowWidth, windowHeight };
	AdjustWindowRect(&r, windowStyle, false);
	UINT width = r.right - r.left;
	UINT height = r.bottom - r.top;

	UINT x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
	UINT y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

	appWindow = CreateWindow("DXAPPWNDCLASS", appTitle.c_str(), windowStyle,
		x, y, width, height, NULL, NULL, appInstance, NULL);

	if (!appWindow)
	{
		OutputDebugString("FAILED TO CREATE WINDOW \nDXApp.cpp InitWindow()");
		return false;
	}

	ShowWindow(appWindow, SW_SHOW);
	UpdateWindow(appWindow);

	return true;
}

LRESULT DXApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (generator->TweakBarEventWin(hwnd, msg, wParam, lParam))
	{
		return 0;
	}

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return LRESULT();
}

void DXApp::StartTimer()
{
	LARGE_INTEGER frequencyCount;
	QueryPerformanceFrequency(&frequencyCount);

	countsPerSecond = double(frequencyCount.QuadPart);

	QueryPerformanceCounter(&frequencyCount);
	CounterStart = frequencyCount.QuadPart;
}

double DXApp::GetTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return double(currentTime.QuadPart - CounterStart) / countsPerSecond;
}

double DXApp::GetFrameTime()
{
	LARGE_INTEGER currentTime;
	__int64 tickCount;
	QueryPerformanceCounter(&currentTime);

	tickCount = currentTime.QuadPart - frameTimeOld;
	frameTimeOld = currentTime.QuadPart;

	if (tickCount < 0.0f)
		tickCount = 0.0f;

	return float(tickCount) / countsPerSecond;
}

