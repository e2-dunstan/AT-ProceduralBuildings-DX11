#pragma once
#include "DXUtil.h"
#include "Renderer.h"
#include "Model.h"
#include "Camera.h"
#include "OBJExporter.h"

class DXApp
{
public:
	DXApp(HINSTANCE hInstance);
	virtual ~DXApp();

	//Loop
	int Run();

	//Framework
	virtual bool Init();
	void GenerateNewBuilding();

	void SetTransforms(int i);
	void SetModelTexture(int i);

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
	std::unique_ptr<Camera> camera;
	std::unique_ptr<OBJExporter> exporter;

	//Initialise Win32 window
	bool InitWindow();

private:

	char* textureFiles[12];

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
};

