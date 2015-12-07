#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// EndLevel Class									
//-----------------------------------------------------
class EndLevel
{
public:
	EndLevel(DOUBLE2 position);				// Constructor
	virtual ~EndLevel();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	void Tick(double positionCharlie);
	void Paint(MATRIX3X2 matView);
	bool IsLevelDone();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	Bitmap *m_BmpEndLevelSignPtr;
	bool m_IsLevelDone;
	DOUBLE2 m_Position;
	int m_CurrentAnimationStep;
	int m_TickCount;
	int m_CurrentState;

	static const int NOT_TURNING = 0;
	static const int TURNING = 1;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	EndLevel(const EndLevel& yRef);									
	EndLevel& operator=(const EndLevel& yRef);	
};

 
