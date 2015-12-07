//---------------------------
// Includes
//---------------------------
#include "Enemy.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Enemy::Enemy(DOUBLE2 position, int path):

		m_Position(position),
		m_StartPosition(0,0),

		m_TickCount(0),
		m_Path(path),
		m_EnemyGoingRight(true),
		m_IsEnemyDead(false),
		m_IsFacingLeft(false),

		m_HitCharlieHorizontalPtr(nullptr),
		m_HitCharlieVerticalPtr(nullptr)

{

}

Enemy::~Enemy()
{
	// nothing to destroy
}

//---------------------------
// Own methods
//---------------------------

