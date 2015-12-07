#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

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


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------


	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	BoxList(const BoxList& yRef);									
	BoxList& operator=(const BoxList& yRef);	
};

 
