//---------------------------
// Includes
//---------------------------
#include "EnemyList.h"

#include "FlatThingy.h"
#include "Frog.h"
#include "Bee.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
EnemyList::EnemyList()
{

		MakeEnemies();

}

EnemyList::~EnemyList()
{

}

//---------------------------
// Own methods
//---------------------------

void EnemyList::Tick(double deltaTime, HitRegion* verticalCollision, HitRegion* horizontalCollision)
{

	//for (int index = 0 ; index < MAX_ENEMIES ; index++)
	//{
	//		if (m_ArrayOfEnemiesPtr[index] != nullptr)
	//		m_ArrayOfEnemiesPtr[index]->Tick(deltaTime,verticalCollision,horizontalCollision);
	//}	

}
void EnemyList::Paint(MATRIX3X2 matView)
{
	
	// for (int index = 0 ; index < MAX_ENEMIES ; index++)
	// {
	//		if (m_ArrayOfEnemiesPtr[index] != nullptr)
	//		m_ArrayOfEnemiesPtr[index]->Paint(matView);
	// }

}

Enemy* EnemyList::GetArrayOfEnemies(int index)
{
	
	return m_ArrayOfEnemiesPtr[index]; 

}

void EnemyList::MakeEnemies()
{
	
	for (int index = 0; index < MAX_ENEMIES; index++)
	{
		m_ArrayOfEnemiesPtr[index] = nullptr;
	}

		// Flat thingy's
		m_ArrayOfEnemiesPtr[0] = new FlatThingy(DOUBLE2(610,478),200);
		m_ArrayOfEnemiesPtr[1] = new FlatThingy(DOUBLE2(1000,320),116);
		m_ArrayOfEnemiesPtr[2] = new FlatThingy(DOUBLE2(1400,478),240);
		m_ArrayOfEnemiesPtr[3] = new FlatThingy(DOUBLE2(3654,381),210);
		// Frogs
		m_ArrayOfEnemiesPtr[4] = new Frog(DOUBLE2(3070,502),410);
		m_ArrayOfEnemiesPtr[5] = new Frog(DOUBLE2(4435,470),300);
		
		// Bees
		m_ArrayOfEnemiesPtr[6] = new Bee(DOUBLE2(605,309),350);
		m_ArrayOfEnemiesPtr[7] = new Bee(DOUBLE2(1170,275),320);
		m_ArrayOfEnemiesPtr[8] = new Bee(DOUBLE2(1500,250),300);
		m_ArrayOfEnemiesPtr[9] = new Bee(DOUBLE2(2070,335),250);
		m_ArrayOfEnemiesPtr[10] = new Bee(DOUBLE2(2472,257),400);
		m_ArrayOfEnemiesPtr[11] = new Bee(DOUBLE2(3080,250),300);
		m_ArrayOfEnemiesPtr[12] = new Bee(DOUBLE2(3525,299),300);
		m_ArrayOfEnemiesPtr[13] = new Bee(DOUBLE2(3926,354),300);
		m_ArrayOfEnemiesPtr[14] = new Bee(DOUBLE2(4913,341),240);
		m_ArrayOfEnemiesPtr[15] = new Bee(DOUBLE2(5195,257),230);

}