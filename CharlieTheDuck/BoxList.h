#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Box.h"

//-----------------------------------------------------
// BoxList Class									
//-----------------------------------------------------
class BoxList
{
public:
	BoxList();				// Constructor
	virtual ~BoxList();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	void Tick();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	/*Box* m_ArrayOfItemsPtr[MAX_BOXES];

	HitRegion *m_HitCharlieVerticalPtr;
	HitRegion *m_HitCharlieHorizontalPtr;*/

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	BoxList(const BoxList& yRef);									
	BoxList& operator=(const BoxList& yRef);	
};

 
