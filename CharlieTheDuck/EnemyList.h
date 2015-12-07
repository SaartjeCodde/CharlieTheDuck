#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Enemy.h"

//-----------------------------------------------------
// EnemyList Class									
//-----------------------------------------------------
class EnemyList
{
public:
	EnemyList();				// Constructor
	virtual ~EnemyList();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	void Tick(double deltaTime, HitRegion* verticalCollision, HitRegion* horizontalCollision);
	void Paint(MATRIX3X2 matView);
	void MakeEnemies();

	Enemy* GetArrayOfEnemies(int index);
	
	static const int MAX_ENEMIES = 16;

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
		
	Enemy* m_ArrayOfEnemiesPtr[MAX_ENEMIES];

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	EnemyList(const EnemyList& yRef);									
	EnemyList& operator=(const EnemyList& yRef);	
};

 
