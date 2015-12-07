//---------------------------
// Includes
//---------------------------
#include "Coin.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

Bitmap* Coin::m_BmpCoinPtr = nullptr;
int Coin::m_Width = 0, Coin::m_Height = 0;
int Coin::m_AmountPickedUp = 0;
//---------------------------
// Constructor & Destructor
//---------------------------
Coin::Coin(DOUBLE2 position, bool inBox): Item(position, inBox), 
	
		m_TickCounter(0),
		m_CurrentAnimationStep(0),

		m_HitRegionCoinPtr(nullptr)	,
		
		m_IsInBox(inBox)
	
{
	
	if (m_BmpCoinPtr == nullptr)
	{
		m_BmpCoinPtr = new Bitmap("./resources/Coin.png");
		m_BmpCoinPtr->SetTransparencyColor(255,0,255);
		m_Width = m_BmpCoinPtr->GetWidth() / NR_OF_ANIMATIONS;
		m_Height = m_BmpCoinPtr->GetHeight();
	}

	m_HitRegionCoinPtr = new HitRegion();
	//m_HitRegionCoinPtr->CreateFromRect(0, 0, m_BmpCoinPtr->GetWidth()/NR_OF_ANIMATIONS, m_BmpCoinPtr->GetHeight());
	m_HitRegionCoinPtr->CreateFromRect(0, 15, m_BmpCoinPtr->GetWidth()/NR_OF_ANIMATIONS, m_BmpCoinPtr->GetHeight()/2);

	m_HitRegionCoinPtr->SetPos(position);	

	m_AmountPickedUp ++;

}

Coin::~Coin()
{

	delete m_HitRegionCoinPtr;
	m_HitRegionCoinPtr = nullptr;

	m_AmountPickedUp--;

}

//---------------------------
// Own methods
//---------------------------

void Coin::Paint(MATRIX3X2 matView)
{
	
	// Determine clip
	if (!m_IsInBox)
	{
	RECT clip;
	clip.left = m_Width * m_CurrentAnimationStep;
	clip.right = clip.left + m_Width;
	clip.top = 0;
	clip.bottom = m_Height;
	
	if (!m_IsPickedUp) // If item is not picked up, paint it
	{
		GAME_ENGINE->DrawBitmap(m_BmpCoinPtr,m_Position.x,m_Position.y,clip);
		GAME_ENGINE->SetColor(COLOR(255,0,0,170));
		// GAME_ENGINE->FillHitRegion(m_HitRegionCoinPtr);
		GAME_ENGINE->SetColor(COLOR(0,0,0));
	}
	}

}

void Coin::Tick(HitRegion* verticalCollision, HitRegion* horizontalCollision)
{
	
	if (!m_IsInBox)
	{
	m_HitCharlieHorizontalPtr = horizontalCollision;
	m_HitCharlieVerticalPtr = verticalCollision;

	m_TickCounter ++;

	if (m_TickCounter % 5 == 0)
	{
		m_CurrentAnimationStep = ++m_CurrentAnimationStep % NR_OF_ANIMATIONS; // Animatie vertragen
	}

	Collision();	
	}
}

void Coin::Collision()
{

	// Vertical collision
	RECT2 verticalTest = m_HitCharlieVerticalPtr->CollisionTest(m_HitRegionCoinPtr);

	if (verticalTest.top > 0)
	{
		m_IsPickedUp = true;		
	}
		
	if (abs(m_HitCharlieVerticalPtr->GetBounds().top - verticalTest.top) < 0.1 && m_HitCharlieVerticalPtr->GetBounds().top != 0)
	{
		m_IsPickedUp = true;
	}
	
	// Horizontal collision
	RECT2 horizontalTest = m_HitCharlieHorizontalPtr->CollisionTest(m_HitRegionCoinPtr);

	if (abs(m_HitCharlieHorizontalPtr->GetBounds().right - horizontalTest.right) < 0.1)
	{
		m_IsPickedUp = true;		
	}

	if (abs(m_HitCharlieHorizontalPtr->GetBounds().left - horizontalTest.left) < 0.1  && m_HitCharlieHorizontalPtr->GetBounds().left != 0)
	{
		m_IsPickedUp = true;		
	}	

}

int Coin::GetAmountPickedUp()
{
	
	return m_AmountPickedUp; // Word opgeroepen in de HUD klasse

}

bool Coin::IsPickedUp()
{
	
	return m_IsPickedUp; // Word opgeroepen in de ItemList

}

void Coin::SetIsInBox(bool inBox)
{
	m_IsInBox = inBox; //inBox word meegegeven in de constructor
}

bool Coin::ReturnIsInBox()
{
	return m_IsInBox;
}

DOUBLE2 Coin::GetPosition()
{
	return m_Position;
}