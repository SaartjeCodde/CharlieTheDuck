//---------------------------
// Includes
//---------------------------
#include "Heart.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

Bitmap* Heart::m_BmpHeartPtr = nullptr;
int Heart::m_Width = 0, Heart::m_Height = 0;
int Heart::m_AmountPickedUp = 2;
//---------------------------
// Constructor & Destructor
//---------------------------
Heart::Heart(DOUBLE2 position, bool inBox): Item(position, inBox),
	
		m_HitRegionHeartPtr(nullptr),
		
		m_TickCounter(0),
		m_CurrentAnimationStep(0),

			m_IsInBox(inBox)

{
	
	if (m_BmpHeartPtr == nullptr)
	{
		m_BmpHeartPtr = new Bitmap("./resources/Heart.bmp");
		m_BmpHeartPtr->SetTransparencyColor(255,0,255);
		m_Width = m_BmpHeartPtr->GetWidth() / NR_OF_ANIMATIONS;
		m_Height = m_BmpHeartPtr->GetHeight();
	}

	m_HitRegionHeartPtr = new HitRegion();
	m_HitRegionHeartPtr->CreateFromRect(0, 50, m_BmpHeartPtr->GetWidth(), m_BmpHeartPtr->GetHeight());

	m_HitRegionHeartPtr->SetPos(position);

	m_AmountPickedUp--;

}

Heart::~Heart()
{
	
	delete m_HitRegionHeartPtr;
	m_AmountPickedUp++;

}

//---------------------------
// Own methods
//---------------------------

void Heart::Paint(MATRIX3X2 matView)
{
	
	RECT clip;
	clip.left = m_Width * m_CurrentAnimationStep;
	clip.right = clip.left + m_Width;
	clip.top = 0;
	clip.bottom = m_Height;

	if (!m_IsPickedUp) // If item is not picked up, paint it
	{
		GAME_ENGINE->DrawBitmap(m_BmpHeartPtr,m_Position.x,m_Position.y,clip);
		GAME_ENGINE->SetColor(COLOR(255,0,0,170));
		// GAME_ENGINE->FillHitRegion(m_HitRegionHeartPtr);
		GAME_ENGINE->SetColor(COLOR(0,0,0));
	}

}

void Heart::Tick(HitRegion* verticalCollision, HitRegion* horizontalCollision)
{
	
	m_TickCounter++;

	m_HitCharlieHorizontalPtr = horizontalCollision;
	m_HitCharlieVerticalPtr = verticalCollision;

	if (m_TickCounter % 15 == 0)
	{
		m_CurrentAnimationStep = ++m_CurrentAnimationStep % NR_OF_ANIMATIONS; // Vertragen van animatie
	}

	Collision();
	
}

void Heart::Collision()
{

	// Vertical collision
	RECT2 verticalTest = m_HitCharlieVerticalPtr->CollisionTest(m_HitRegionHeartPtr);

	if (verticalTest.top > 0)
	{
		m_IsPickedUp = true;
	}
		
	if (abs(m_HitCharlieVerticalPtr->GetBounds().top - verticalTest.top) < 0.1 && m_HitCharlieVerticalPtr->GetBounds().top != 0)
	{
		m_IsPickedUp = true;
	}
	
	// Horizontal collision
	RECT2 horizontalTest = m_HitCharlieHorizontalPtr->CollisionTest(m_HitRegionHeartPtr);

	if (abs(m_HitCharlieHorizontalPtr->GetBounds().right - horizontalTest.right) < 0.1)
	{
		m_IsPickedUp = true;
	}

	if (abs(m_HitCharlieHorizontalPtr->GetBounds().left - horizontalTest.left) < 0.1  && m_HitCharlieHorizontalPtr->GetBounds().left != 0)
	{
		m_IsPickedUp = true;
	}	

}

int Heart::GetAmountPickedUp()
{
	
	return m_AmountPickedUp; // Word opgevraagd in de HUD klasse

}

bool Heart::IsPickedUp()
{
	
	return m_IsPickedUp; // Word opgeroepen in de ItemList

}

void Heart::SetIsInBox(bool inBox)
{
	m_IsInBox = inBox;
}

bool Heart::ReturnIsInBox()
{
	return m_IsInBox;
}

DOUBLE2 Heart::GetPosition()
{
	return m_Position;
}