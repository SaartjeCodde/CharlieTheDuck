#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Enemy.h"
//-----------------------------------------------------
// FlatThingy Class									
//-----------------------------------------------------
class FlatThingy: public Enemy
{
public:
	FlatThingy(DOUBLE2 position, int path);				// Constructor
	virtual ~FlatThingy();		// Destructor

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

	static Bitmap* m_BmpFlatThingyPtr;

	static int m_Width;
	static int m_Height;

	HitRegion* m_HitRegionFlatThingyVerticalPtr;
	HitRegion* m_HitRegionFlatThingyHorizontalPtr;	

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	FlatThingy(const FlatThingy& yRef);									
	FlatThingy& operator=(const FlatThingy& yRef);	
};

 
