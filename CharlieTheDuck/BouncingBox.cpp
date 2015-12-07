//---------------------------
// Includes
//---------------------------
#include "BouncingBox.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
BouncingBox::BouncingBox(DOUBLE2 position):

		m_BmpBouncingBoxPtr(nullptr),
		
		m_HitRegionBouncingBoxPtr(nullptr),
		m_HitCharlieVerticalPtr(nullptr),
		
		m_Position(position),

		m_IsBouncing(false)

{
	
	if (m_BmpBouncingBoxPtr == nullptr)
	{
		m_BmpBouncingBoxPtr = new Bitmap("./resources/Bouncing box.png");
		m_BmpBouncingBoxPtr->SetTransparencyColor(255,0,255);
	}

	m_HitRegionBouncingBoxPtr = new HitRegion();
	m_HitRegionBouncingBoxPtr->CreateFromRect(0, 0,m_BmpBouncingBoxPtr->GetWidth(),m_BmpBouncingBoxPtr->GetHeight());

	m_HitRegionBouncingBoxPtr->SetPos(position);

}

BouncingBox::~BouncingBox()
{
	
	delete m_BmpBouncingBoxPtr;

}

//---------------------------
// Own methods
//---------------------------

void BouncingBox::Paint(MATRIX3X2 matView)
{
	
	GAME_ENGINE->DrawBitmap(m_BmpBouncingBoxPtr,m_Position.x,m_Position.y);
	// GAME_ENGINE->SetColor(COLOR(255,0,0,170));
	// GAME_ENGINE->FillHitRegion(m_HitRegionBouncingBoxPtr);
	// GAME_ENGINE->SetColor(COLOR(0,0,0));	

}

void BouncingBox::Tick(HitRegion* verticalCollision)
{
	
	m_HitCharlieVerticalPtr = verticalCollision;

	Collision();
	
}

void BouncingBox::Collision()
{

	// Vertical collision
	RECT2 verticalTest = m_HitCharlieVerticalPtr->CollisionTest(m_HitRegionBouncingBoxPtr);

	if (verticalTest.top > 0)
	{
		m_IsBouncing = true;
	}
		
	if (abs(m_HitCharlieVerticalPtr->GetBounds().top - verticalTest.top) < 0.1 && m_HitCharlieVerticalPtr->GetBounds().top != 0)
	{
		m_IsBouncing = true;
	}	

}

bool BouncingBox::IsBouncing()
{
	
	return m_IsBouncing;

}

bool BouncingBox::Bounce()
{
	
	RECT2 verticalTest = m_HitCharlieVerticalPtr->CollisionTest(m_HitRegionBouncingBoxPtr);

	if (verticalTest.top > 0 && verticalTest.bottom - verticalTest.top < 10 )
	{
		m_IsBouncing = true;
		return true;
	}
	
	return false;

}