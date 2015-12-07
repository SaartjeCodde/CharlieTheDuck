//-----------------------------------------------------------------
// Game File
// C++ Source - CharlieTheDuck.h - version v2_12 jan 2013 
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Student data
// Name: Codde Saartje
// Group: 1DAE5
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"	
#include "GameEngine.h"
#include "AbstractGame.h"

#include "Charlie.h"
#include "ItemList.h"
#include "EnemyList.h"
#include "HUD.h"

#include "Box.h"

#include "BouncingBox.h"

#include "EndLevel.h"

//-----------------------------------------------------------------
// CharlieTheDuck Class																
//-----------------------------------------------------------------
class CharlieTheDuck : public AbstractGame, public Callable
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	CharlieTheDuck();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~CharlieTheDuck();

	//---------------------------
	// General Methods
	//---------------------------

	void GameInitialize(HINSTANCE hInstance);
	void GameStart();				
	void GameEnd();
	void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam);
	//void MouseMove(int x, int y, WPARAM wParam);
	//void CheckKeyboard();
	//void KeyPressed(TCHAR cKey);
	void GameTick(double deltaTime);
	void GamePaint(RECT rect);

	void Reset();

	//void CallAction(Caller* callerPtr);

	// -------------------------
	// Member functions
	// -------------------------

	static const int MAX_ENEMIES = 16;
	static const int MAX_ITEMS = 44;
	static const int NUMBER_OF_BOXES = 11;

private:
	// -------------------------
	// Member functions
	// -------------------------

	// -------------------------
	// Datamembers
	// -------------------------

	Audio* m_PewPtr;

	Charlie *m_CharliePtr;
	Enemy* m_EnemyArrayPtr[MAX_ENEMIES];
	EnemyList* m_EnemyListPtr;
	ItemList* m_ArrayOfItemsPtr;
	HUD* m_HUDPtr;
	Box* m_BoxArrayPtr[NUMBER_OF_BOXES]; 
	BouncingBox* m_BouncingBoxPtr;
	BouncingBox* m_BouncingBox2Ptr;

	EndLevel* m_EndLevelSignPtr;
	
	Bitmap *m_BmpLevelPtr;
	Bitmap *m_BmpWaterPtr;
	Bitmap *m_BmpCloudPtr;
	
	HitRegion *m_HitLevelPtr;
	HitRegion *m_HitWaterPtr;

	int m_TickCounter;
	int m_WaterAnimationStep;
	int m_CloudAnimationStep;

	DOUBLE2 m_PositionCamera;
	DOUBLE2 m_CloudPosition;

	bool m_IsCameraEnabled;	

	Bitmap *m_BmpStartSchermPtr;

	bool m_IsGameStarted;

	HitRegion *m_HitRegionStartScherm;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	CharlieTheDuck(const CharlieTheDuck& tRef);
	CharlieTheDuck& operator=(const CharlieTheDuck& tRef);
};
