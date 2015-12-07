#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Enemy Class									
//-----------------------------------------------------
class Enemy
{	

public:
	Enemy(DOUBLE2 position, int path);				// Constructor
	virtual ~Enemy();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	
	virtual void Paint(MATRIX3X2 matView) = 0; 
	virtual void Tick(double deltaTime, HitRegion* verticalCollision, HitRegion* horizontalCollision) = 0;

	virtual DOUBLE2 GetPosition() = 0;

	virtual bool Bounce() = 0;
	virtual bool EnemyHit() = 0;
	virtual bool EnemyDead() = 0;

protected:

	DOUBLE2 m_Position;
	DOUBLE2 m_StartPosition;

	HitRegion* m_HitCharlieHorizontalPtr;
	HitRegion* m_HitCharlieVerticalPtr;
	
	int m_Path;
	int m_TickCount;

	bool m_IsEnemyDead;
	bool m_EnemyGoingRight;

	bool m_IsFacingLeft;
	
private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Enemy(const Enemy& yRef);									
	Enemy& operator=(const Enemy& yRef);	
};

 

