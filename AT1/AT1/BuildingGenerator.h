#pragma once
#include "DXApp.h"
#include "Interiors.h"

class BuildingGenerator
{
public:
	BuildingGenerator() = default;
	~BuildingGenerator();

	void InitTweakBar(Renderer & renderer);
	void Init();
	void InitWalls();
	void InitInteriorWalls();
	void InitWindowsAndDoor(float height);
	void InitCorners();
	void InitFloors();
	void InitRoof();
	void ClearVectors();

	void DrawTweakBar();
	bool TweakBarEventWin(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void TerminateTweakBar();

	std::vector<Model*> GetModels();

	void SetValuesChanged(bool changed);
	bool ValuesChanged();
	void SetCreateNewObj(bool create);
	bool CreateNewObj();

private:
	TwBar * tweakBar;

	std::vector<Interiors*> interiorFloors;

	std::vector<Model*> models;

	std::vector<Model*> walls;
	std::vector<Model*> windows;
	std::vector<Model*> corners;
	std::vector<Model*> floors;
	Model* door;

	bool valuesChanged = true;
	bool createNewObj = false;

	//these will be user defined
	int buildingWidth = 5;
	int buildingHeight = 2;
	int buildingDepth = 6;
	float wallWidth = 6;
	float wallHeight = 8;
	float wallDepth = 1;

	int numWindowsOnWidth = 5;
	int numWindowsOnDepth = 2;
	float windowWidth = 3;
	float windowHeight = 4;
	float windowDepth = 2;

	float doorWidth = 2;
	float doorHeight = 5;
	float doorDepth = 2;

	typedef enum { PYRAMID, FLAT, SHED } Roof;
	Roof roof = FLAT;

	float roofOverhang = 4;
	float roofHeight = 2;
};