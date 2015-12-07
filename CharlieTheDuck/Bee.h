#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Enemy.h"

//-----------------------------------------------------
// Bee Class									
//-----------------------------------------------------
class Bee: public Enemy
{
public:
	Bee(DOUBLE2 position, int path);				// Constructor
	virtual ~Bee();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	virtual void Paint(MATRIX3X2 matView); 
	virtual void Tick(double deltaTime, HitRegion* verticalCollision, HitRegion* horizontalCollision);

	virtual DOUBLE2 GetPosition();

	virtual bool Bounce();
	virtual bool EnemyHit();
	virtual bool EnemyDead();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	static Bitmap* m_BmpBeePtr;

	static int m_Width, m_Height;

	HitRegion* m_HitRegionBeePtr;
	HitRegion* m_HitRegionBeeVerticalPtr;
	HitRegion* m_HitRegionBeeHorizontalPtr;
	static const int NR_OF_ANIMATIONS = 3;

	int m_CurrentAnimationStep;
	int m_Random;

	bool m_EnemyGoingUp;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Bee(const Bee& yRef);									
	Bee& operator=(const Bee& yRef);	
};

 
