#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Item.h"
//-----------------------------------------------------
// Diamond Class									
//-----------------------------------------------------
class Diamond: public Item
{
public:
	Diamond(DOUBLE2 position, bool inBox);				// Constructor
	virtual ~Diamond();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	virtual void Paint(MATRIX3X2 matView);
	virtual void Tick(HitRegion* verticalCollision, HitRegion* horizontalCollision);
	virtual void Collision();
	virtual void SetIsInBox(bool inBox);
	virtual bool ReturnIsInBox();

	virtual DOUBLE2 GetPosition();

	virtual bool IsPickedUp();	

	static int GetAmountPickedUp();

	static int m_AmountPickedUp;

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	static Bitmap* m_BmpDiamondPtr;
	
	static int m_Width;
	static int m_Height;

	HitRegion* m_HitRegionDiamondPtr;

	int m_CurrentAnimationStep;
	int m_TickCounter;
	
	static const int NR_OF_ANIMATIONS = 2;

		bool m_IsInBox;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Diamond(const Diamond& yRef);									
	Diamond& operator=(const Diamond& yRef);	
};

 
