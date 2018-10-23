#include "DXApp.h"
#include "Constants.h"
#include <dwrite.h>
#include <time.h>
#include "BuildingGenerator.h"

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
	if (TwEventWin(hwnd, msg, wParam, lParam))
	{
		return 0;
	}
	else
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

DXApp::DXApp(HINSTANCE hInstance)
{
	appInstance = hInstance;
	appWindow = NULL;
	windowStyle = WS_OVERLAPPEDWINDOW;
	globalApp = this;

	textureFiles[0] = "Resources/chiseled_red_sandstone.tga";
	textureFiles[1] = "Resources/coal_block.tga";
	textureFiles[2] = "Resources/daylight_detector.tga";
	textureFiles[3] = "Resources/lapis_ore.tga";
	textureFiles[4] = "Resources/light_gray_terracotta.tga";
	textureFiles[5] = "Resources/lime_terracotta.tga";
	textureFiles[6] = "Resources/mycelium_top.tga";
	textureFiles[7] = "Resources/nether_wart_block.tga";
	textureFiles[8] = "Resources/purpur_pillar.tga";
	textureFiles[9] = "Resources/red_nether_bricks.tga";
	textureFiles[10] = "Resources/red_sandstone.tga";
}

DXApp::~DXApp()
{

	//CHANGE 11 TO MAX TEXTURES
	//for (int i = 0; i < 11; i++)
	//{
	//	if (textureFiles[i])
	//	{
	//		delete textureFiles[i];
	//		textureFiles[i] = nullptr;
	//	}
	//}
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

	exporter = std::unique_ptr<OBJExporter>(new OBJExporter);

	InitTweakBar();

	// -- CREATE MODELS -- //

	std::unique_ptr<BuildingGenerator> generator = std::unique_ptr<BuildingGenerator>(new BuildingGenerator);
	generator->Init();

	allModels = generator->GetModels();

	for (int i = 0; i < allModels.size(); i++)
	{
		//srand(time(NULL));
		//int randNum = rand() % 11;

		if (!allModels[i]->InitModel(*renderer, textureFiles[10],
			appWindow))
		{
			MessageBox(0, (LPCSTR)L"Model Initialization - Failed",
				(LPCSTR)L"Error", MB_OK);
			return false;
		}
		SetTransforms(i);
	}
	//--CREATE OBJ--//
	exporter->SetTexture(textureFiles[10]);
	exporter->SetModels(allModels);
	exporter->SetTransforms(allModelTransforms);
	exporter->Create();

	return true;
}

//void DXApp::InitWalls()
//{
//	//for all of the floors
//	//for (int h = 0; h < buildingHeight; h++)
//	//{
//	//	//for each depth in the building
//	//	for (int d = 0; d < buildingDepth; d++)
//	//	{
//	//		//first horizontal wall
//	//		if (d == 0)
//	//		{
//	//			for (int w = 0; w < buildingWidth; w++)
//	//			{
//	//				allModels.push_back(new Model(Type::WALL, wallWidth, wallHeight, wallDepth,
//	//					wallDepth + (wallWidth/2) + (wallWidth * w), 
//	//					wallHeight * h,
//	//					wallDepth / 2, 
//	//					90.0f * 0));
//	//			}
//	//		}
//	//		//final horizontal wall
//	//		else if (d == (buildingDepth - 1))
//	//		{
//	//			for (int w = 0; w < buildingWidth; w++)
//	//			{
//	//				allModels.push_back(new Model(Type::WALL, wallWidth, wallHeight, wallDepth,
//	//					wallDepth + (wallWidth / 2) + (wallWidth * w),
//	//					wallHeight * h,
//	//					(wallDepth * 1.5f) + (wallWidth * d),
//	//					90.0f * 0));
//	//			}
//	//		}
//	//		//vertical walls
//	//		else
//	//		{
//	//			allModels.push_back(new Model(Type::WALL, wallWidth, wallHeight, wallDepth,
//	//				wallDepth / 2, 
//	//				wallHeight * h,
//	//				wallDepth + (wallWidth / 2) + (wallWidth * d), 
//	//				90.0f * 1));
//	//			allModels.push_back(new Model(Type::WALL, wallWidth, wallHeight, wallDepth,
//	//				(wallDepth * 1.5f) + (wallWidth * buildingWidth),
//	//				wallHeight * h,
//	//				wallDepth + (wallWidth / 2) + (wallWidth * d),
//	//				90.0f * 1));
//	//		}
//	//	}
//	//}
//
//
//	buildingDepth += 2;
//	for (int f = 1; f <= buildingHeight; f++)
//	{
//		float height = f * wallHeight;
//		for (int d = 0; d < buildingDepth; d++)
//		{
//			if (d == 0)
//			{
//				float depth = (d + 0.5f) * wallWidth;
//				for (int w = 0; w < buildingWidth; w++)
//				{
//					walls.push_back(new Model(Type::WALL, wallWidth, wallHeight, wallDepth,
//						w * wallWidth, height, depth, 90.0f * 0));
//				}
//			}
//			else if (d == (buildingDepth - 1))
//			{
//				float depth = ((d - 0.5f) * wallWidth) + (wallDepth * 2);
//				for (int w = 0; w < buildingWidth; w++)
//				{
//					walls.push_back(new Model(Type::WALL, wallWidth, wallHeight, wallDepth,
//						w * wallWidth, height, depth, 90.0f * 2));
//				}
//			}
//			else
//			{
//				float depth = (d* wallWidth) + wallDepth;
//				walls.push_back(new Model(Type::WALL, wallWidth, wallHeight, wallDepth,
//					-(wallWidth / 2) - wallDepth, height, depth, 90.0f * 1));
//				walls.push_back(new Model(Type::WALL, wallWidth, wallHeight, wallDepth,
//					(buildingWidth * wallWidth) - (wallWidth / 2) + wallDepth, height, depth, 90.0f * 3));
//			}
//		}
//	}
//
//	for (int w = 0; w < walls.size(); w++)
//	{
//		allModels.push_back(walls[w]);
//	}
//}

//void DXApp::InitCorners()
//{
//	//0,0
//	corners.push_back(new Model(Type::CORNER, wallDepth, wallHeight * buildingHeight, wallDepth,
//		-(wallWidth / 2) - wallDepth, 
//		(wallHeight * (buildingHeight + 1)) / 2,
//		0.5f * wallWidth, 0));
//	//1,0
//	corners.push_back(new Model(Type::CORNER, wallDepth, wallHeight * buildingHeight, wallDepth,
//		(wallWidth * buildingWidth) - (wallWidth / 2) + wallDepth, (wallHeight * (buildingHeight + 1)) / 2, 0.5f * wallWidth, 0));
//	//0,1
//	corners.push_back(new Model(Type::CORNER, wallDepth, wallHeight * buildingHeight, wallDepth,
//		-(wallWidth / 2) - wallDepth, (wallHeight * (buildingHeight + 1)) / 2, (wallWidth * (buildingDepth - 1)) - (wallDepth / 2), 0));
//	//1,1
//	corners.push_back(new Model(Type::CORNER, wallDepth, wallHeight * buildingHeight, wallDepth,
//		(wallWidth * buildingWidth) - (wallWidth / 2) + wallDepth, (wallHeight * (buildingHeight + 1)) / 2, (wallWidth * (buildingDepth - 1)) - (wallDepth / 2), 0));
//
//	for (int c = 0; c < corners.size(); c++)
//	{
//		allModels.push_back(corners[c]);
//	}
//}

void DXApp::InitTweakBar()
{
	TwInit(TW_DIRECT3D11, renderer->GetDevice());
	tweakBar = TwNewBar("Customise");
	TwWindowSize(200, 400);
	int tweakBarSize[2] = { 200, 400 };
	TwSetParam(tweakBar, NULL, "size", TW_PARAM_INT32, 2, tweakBarSize);
	bool freezeCamera = false;
	TwAddVarRW(tweakBar, "Freeze Camera", TW_TYPE_BOOLCPP, &freezeCamera, NULL);
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

void DXApp::Update(double dt)
{
	camera->DetectInput(dt, appWindow);

	//Stops it from updating every frame
	if (valuesChanged)
	{
		allModelTransforms.clear();

		for (int i = 0; i < allModels.size(); i++)
		{
			SetTransforms(i);
		}

		renderer->SetModelTransforms(allModelTransforms);


		//exporter->Create();

		valuesChanged = false;
	}
}

void DXApp::Render(double dt)
{
	renderer->DrawBackground();
	for (int i = 0; i < allModels.size(); i++)
	{
		allModels[i]->UpdateBuffers(*renderer);
		renderer->DrawModel(allModels[i]->GetTexture(), allModels[i]->GetTexturePointer()->GetSamplerState(), 
			camera->GetCamView(), camera->GetCamProjection(), i, allModels[i]->GetIndices().size());
	}
	TwDraw();
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

