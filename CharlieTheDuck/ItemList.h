#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

#include "GameEngine.h"

#include "Item.h"
//-----------------------------------------------------
// ItemList Class									
//-----------------------------------------------------
class ItemList
{
public:
	ItemList();				// Constructor
	virtual ~ItemList();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	void Tick(HitRegion* verticalCollision, HitRegion* horizontalCollision);
	void Paint(MATRIX3X2 matView);
	void SetItemDisplayed(int ItemId);

	bool ItemExists(int ItemId);
	bool IsItemInBox(int ItemId);

	static const int MAX_ITEMS = 45;

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	Bitmap *m_BmpCollectingStarsPtr;

	Item* m_ArrayOfItemsPtr[MAX_ITEMS];

	DOUBLE2 m_PositionStars;
	
	int m_TickCounter;
	int m_CurrentAnimationStep;

	HitRegion *m_HitCharlieVerticalPtr;
	HitRegion *m_HitCharlieHorizontalPtr;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	ItemList(const ItemList& yRef);									
	ItemList& operator=(const ItemList& yRef);	
};

 
