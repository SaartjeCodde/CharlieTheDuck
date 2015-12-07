#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Box Class									
//-----------------------------------------------------
class Box
{
public:
	Box(DOUBLE2 position, int itemID);				// Constructor
	virtual ~Box();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	void Tick(HitRegion* verticalHitRegion, double deltaTime);
	void Paint(MATRIX3X2 matView);
	void Collision();
	
	int Max(int Number_1, int Number_2);
	int ReturnItemID();
	
	bool IsBoxGone();
	bool IsBoxBroken();

	static const int NUMBER_OF_BLOCKS = 6;

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	DOUBLE2 m_BlockPositions[NUMBER_OF_BLOCKS];
	DOUBLE2 m_VelocityArray[NUMBER_OF_BLOCKS];
	DOUBLE2 m_Gravity;
	DOUBLE2 m_Velocity;
	DOUBLE2 m_Position;

	Bitmap *m_BmpBoxPtr;
	Bitmap *m_BmpAnimationPtr;

	HitRegion *m_HitRegionBoxPtr;
	HitRegion *m_HitCharlieVerticalPtr;

	int m_Width;
	int m_Height;
	int m_CurrentAnimationStep;
	int m_TickCounter;
	int m_ItemID;

	bool m_IsBroken;
	bool m_FirstPoof;
	bool m_IsBoxGone;
	bool m_IsItemDisplayed;

	static const int NR_OF_ANIMATIONS = 2;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Box(const Box& yRef);									
	Box& operator=(const Box& yRef);	
};

 
