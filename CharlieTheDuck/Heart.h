#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Item.h"
//-----------------------------------------------------
// Heart Class									
//-----------------------------------------------------
class Heart: public Item
{
public:
	Heart(DOUBLE2 position, bool inBox);				// Constructor
	virtual ~Heart();		// Destructor

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

	static Bitmap* m_BmpHeartPtr;
	
	static int m_Width;
	static int m_Height;


	HitRegion* m_HitRegionHeartPtr;

	int m_TickCounter;
	int m_CurrentAnimationStep;
	
	static const int NR_OF_ANIMATIONS = 2;	

	bool m_IsInBox;
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Heart(const Heart& yRef);									
	Heart& operator=(const Heart& yRef);	
};

 
