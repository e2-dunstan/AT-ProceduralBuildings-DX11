#pragma once
#include "DXUtil.h"
#include "Renderer.h"
#include "Model.h"
#include "Camera.h"

class DXApp
{
public:
	DXApp(HINSTANCE hInstance);
	virtual ~DXApp();

	//Loop
	int Run();

	//Framework
	virtual bool Init();
	void InitWalls();
	void InitCorners();
	virtual void Update(double dt);
	virtual void Render(double dt);
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void StartTimer();
	double GetTime();
	double GetFrameTime();

protected:
	//Win32 Attributes
	HWND		appWindow;
	HINSTANCE	appInstance;
	DWORD		windowStyle;

	std::unique_ptr<Renderer> renderer;
	std::vector<Model*> allModels;
	std::vector<Model*> walls;
	std::vector<Model*> corners;
	std::unique_ptr<Camera> camera;

	//Initialise Win32 window
	bool InitWindow();

private:

	char* textureFiles[11];

	std::vector<XMMATRIX> allModelTransforms;

	XMMATRIX Rotation;
	XMMATRIX Scale;
	XMMATRIX Translation;
	float rot = 0.01f;


	double countsPerSecond = 0.0;
	__int64 CounterStart = 0;

	int frameCount = 0;
	int fps = 0;

	__int64 frameTimeOld = 0;
	double frameTime;


	bool valuesChanged = true;

	//these will be user defined
	int buildingWidth = 10;
	int buildingHeight = 3;
	int buildingDepth = 1;
	float wallWidth = 5;
	float wallHeight = 5;
	float wallDepth = 1; //don't allow to be greater than wall width
};

