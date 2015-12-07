//---------------------------
// Includes
//---------------------------
#include "Diamond.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

Bitmap* Diamond::m_BmpDiamondPtr = nullptr;
int Diamond::m_Width = 0, Diamond::m_Height = 0;
int Diamond::m_AmountPickedUp = 0;
//---------------------------
// Constructor & Destructor
//---------------------------
Diamond::Diamond(DOUBLE2 position, bool inBox): Item(position, inBox),

		m_HitRegionDiamondPtr(nullptr),

		m_CurrentAnimationStep(0),
		m_TickCounter(0),

			m_IsInBox(inBox)

{
	
	if (m_BmpDiamondPtr == nullptr)
	{
		m_BmpDiamondPtr = new Bitmap("./resources/Diamond.png");
		m_BmpDiamondPtr->SetTransparencyColor(255,0,255);
		m_Width = m_BmpDiamondPtr->GetWidth()/NR_OF_ANIMATIONS;
		m_Height = m_BmpDiamondPtr->GetHeight();
	}

	m_HitRegionDiamondPtr = new HitRegion();
	m_HitRegionDiamondPtr->CreateFromRect(0, 25, m_BmpDiamondPtr->GetWidth(), m_BmpDiamondPtr->GetHeight());

	m_HitRegionDiamondPtr->SetPos(position);
		
	m_AmountPickedUp++;

}

Diamond::~Diamond()
{

	delete m_HitRegionDiamondPtr;
	m_AmountPickedUp--;

}

//---------------------------
// Own methods
//---------------------------

void Diamond::Paint(MATRIX3X2 matView)
{
	
	RECT clip;
	clip.left = m_Width * m_CurrentAnimationStep;
	clip.right = clip.left + m_Width;
	clip.top = 0;
	clip.bottom = m_Height;
	
	if (!m_IsPickedUp) // If item is not picked up, paint it
	{
		GAME_ENGINE->DrawBitmap(m_BmpDiamondPtr,m_Position.x,m_Position.y,clip);
		GAME_ENGINE->SetColor(COLOR(255,0,0,170));
		// GAME_ENGINE->FillHitRegion(m_HitRegionDiamondPtr);
		GAME_ENGINE->SetColor(COLOR(0,0,0));
	}

}

void Diamond::Tick(HitRegion* verticalCollision, HitRegion* horizontalCollision)
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

void Diamond::Collision()
{

	// Vertical collision
	RECT2 verticalTest = m_HitCharlieVerticalPtr->CollisionTest(m_HitRegionDiamondPtr);

	if (verticalTest.top > 0)
	{
		m_IsPickedUp = true;
	}
		
	if (abs(m_HitCharlieVerticalPtr->GetBounds().top - verticalTest.top) < 0.1 && m_HitCharlieVerticalPtr->GetBounds().top != 0)
	{
		m_IsPickedUp = true;
	}
	
	// Horizontal collision
	RECT2 horizontalTest = m_HitCharlieHorizontalPtr->CollisionTest(m_HitRegionDiamondPtr);

	if (abs(m_HitCharlieHorizontalPtr->GetBounds().right - horizontalTest.right) < 0.1)
	{
		m_IsPickedUp = true;
	}

	if (abs(m_HitCharlieHorizontalPtr->GetBounds().left - horizontalTest.left) < 0.1  && m_HitCharlieHorizontalPtr->GetBounds().left != 0)
	{
		m_IsPickedUp = true;
	}	

}

int Diamond::GetAmountPickedUp()
{
	
	return m_AmountPickedUp; // Word opgeroepen in de HUD klasse

}

bool Diamond::IsPickedUp()
{
	
	return m_IsPickedUp; // Word opgeroepen in de ItemList

}

void Diamond::SetIsInBox(bool inBox)
{
	m_IsInBox = inBox;
}

bool Diamond::ReturnIsInBox()
{
	return m_IsInBox;
}

DOUBLE2 Diamond::GetPosition()
{
	return m_Position;
}