#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Enemy.h"
//-----------------------------------------------------
// Frog Class									
//-----------------------------------------------------
class Frog: public Enemy
{
public:
	Frog(DOUBLE2 position, int path);				// Constructor
	virtual ~Frog();		// Destructor

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

	static Bitmap* m_BmpFrogPtr;

	static int m_Width;
	static int m_Height;

	HitRegion* m_HitRegionFrogVerticalPtr;
	HitRegion* m_HitRegionFrogHorizontalPtr;

	int m_JumpHeight;
	int m_EnemyGoingUp;

	static const int NR_OF_ANIMATIONS = 2;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Frog(const Frog& yRef);									
	Frog& operator=(const Frog& yRef);	
};

 
