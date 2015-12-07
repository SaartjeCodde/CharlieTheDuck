#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Item Class									
//-----------------------------------------------------
class Item
{
public:
	Item(DOUBLE2 position, bool inBox);				// Constructor
	virtual ~Item();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	virtual void Paint(MATRIX3X2 matView) = 0;
	virtual void Tick(HitRegion* verticalCollision, HitRegion* horizontalCollision) = 0;
	virtual void Collision() = 0;
	virtual bool IsPickedUp() = 0;
	virtual void SetIsInBox(bool inBox) = 0;
	virtual bool ReturnIsInBox() = 0;

	virtual DOUBLE2 GetPosition() = 0;
	
protected:

	DOUBLE2 m_Position;
	
	bool m_IsPickedUp;
	
	HitRegion* m_HitCharlieHorizontalPtr;
	HitRegion* m_HitCharlieVerticalPtr;

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------


	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Item(const Item& yRef);									
	Item& operator=(const Item& yRef);	
};

 
