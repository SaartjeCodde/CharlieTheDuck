//---------------------------
// Includes
//---------------------------
#include "Item.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Item::Item(DOUBLE2 position, bool inBox):

		m_Position(position),
		
		m_IsPickedUp(false),
		
		m_HitCharlieHorizontalPtr(nullptr),
		m_HitCharlieVerticalPtr(nullptr)

{
	
}

Item::~Item()
{
	
}

//---------------------------
// Own methods
//---------------------------




