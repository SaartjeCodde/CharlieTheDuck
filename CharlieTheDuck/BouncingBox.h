#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// BouncingBox Class									
//-----------------------------------------------------
class BouncingBox
{
public:
	BouncingBox(DOUBLE2 position);				// Constructor
	virtual ~BouncingBox();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	void Tick(HitRegion* verticalHitRegion);
	void Paint(MATRIX3X2 matView);
	void Collision();

	bool IsBouncing();
	bool Bounce();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	Bitmap *m_BmpBouncingBoxPtr;
	
	HitRegion *m_HitRegionBouncingBoxPtr;
	HitRegion *m_HitCharlieVerticalPtr;

	int m_Width;
	int m_Height;

	DOUBLE2 m_Position;

	bool m_IsBouncing;
	
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	BouncingBox(const BouncingBox& yRef);									
	BouncingBox& operator=(const BouncingBox& yRef);	
};

 
