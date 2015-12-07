//---------------------------
// Includes
//---------------------------
#include "FlatThingy.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

Bitmap* FlatThingy::m_BmpFlatThingyPtr = nullptr;
int FlatThingy::m_Width = 0, FlatThingy::m_Height = 0;
//---------------------------
// Constructor & Destructor
//---------------------------
FlatThingy::FlatThingy(DOUBLE2 position, int path): Enemy(position, path),

		m_HitRegionFlatThingyVerticalPtr(nullptr),
		m_HitRegionFlatThingyHorizontalPtr(nullptr)

{
	
	if (m_BmpFlatThingyPtr == nullptr)
	{
		m_BmpFlatThingyPtr = new Bitmap("./resources/Purple flat thingy.png");
		m_BmpFlatThingyPtr->SetTransparencyColor(255,0,255);
		m_Width = m_BmpFlatThingyPtr->GetWidth();
		m_Height = m_BmpFlatThingyPtr->GetHeight();
	}

	m_StartPosition = m_Position;
	
	// HitRegions
	m_HitRegionFlatThingyVerticalPtr = new HitRegion();
	m_HitRegionFlatThingyVerticalPtr->CreateFromRect(10, 0, (m_BmpFlatThingyPtr->GetWidth())-10, m_BmpFlatThingyPtr->GetHeight());
	m_HitRegionFlatThingyHorizontalPtr = new HitRegion();
	m_HitRegionFlatThingyHorizontalPtr->CreateFromRect(0, 10, m_BmpFlatThingyPtr->GetWidth(), m_BmpFlatThingyPtr->GetHeight()-10);
	
}

FlatThingy::~FlatThingy()
{
	
	delete m_HitRegionFlatThingyVerticalPtr;
	delete m_HitRegionFlatThingyHorizontalPtr;

}

//---------------------------
// Own methods
//---------------------------

void FlatThingy::Tick(double deltaTime, HitRegion* verticalCollision, HitRegion* horizontalCollision)
{
	
	m_HitCharlieVerticalPtr = verticalCollision;
	m_HitCharlieHorizontalPtr = horizontalCollision;

	++m_TickCount;

	if (m_TickCount == 2)
	{
		m_TickCount = 0;
	}	

	if (m_IsEnemyDead == false)
	{
		if (m_Position.x < (m_StartPosition.x + m_Path) && m_EnemyGoingRight == true ) 
		{
			m_Position.x += 2;
			if (m_Position.x >= (m_StartPosition.x + m_Path)) 
			{
				m_EnemyGoingRight = false;
			}
		}

		if (m_Position.x > m_StartPosition.x && m_EnemyGoingRight == false)
		{
			m_Position.x -= 2;
			if (m_Position.x <= m_StartPosition.x) 
			{
				m_EnemyGoingRight = true;
			}
		}
	}
	// Woordje uitleg voor mezelf:
	// Als de positie van de enemy kleiner is dan de startpositie + het pad dat de enemy moet afleggen, vermeerderd de positie naar rechts en omgekeerd.
	// De bool m_EnemyGoingRight is geimplementeert omdat als de enemy moet terug keren na een eerste keer het pad af te leggen,
	// de eerste if direct terug gebeurt en de enemy anders het pad maar 1 keer doet en op het einde blijft steken.

	else
	{
		m_Position.y += 5;

		if (m_Position.y > GAME_ENGINE->GetHeight())
		{
			// Delete enemy, gebeurt in de main
		}
	}

	m_HitRegionFlatThingyHorizontalPtr->SetPos(m_Position);
	m_HitRegionFlatThingyVerticalPtr->SetPos(m_Position);
		
}

void FlatThingy::Paint(MATRIX3X2 matView)
{
	
	// Matricen
	MATRIX3X2 transformFlatThingy;
	transformFlatThingy.SetAsTranslate(m_Position);

	// Flip
	MATRIX3X2 scaleFlatThingy;
	if (m_IsEnemyDead == true)
	{
		scaleFlatThingy.SetAsScale(1,-1);
	}
	GAME_ENGINE->SetTransformMatrix(scaleFlatThingy * transformFlatThingy * matView);
	
	if (m_IsEnemyDead ==true)
	{
		GAME_ENGINE->DrawBitmap(m_BmpFlatThingyPtr,0,0-50);
	}
	else
	{
		GAME_ENGINE->DrawBitmap(m_BmpFlatThingyPtr,0,0);
	}

	// GAME_ENGINE->SetTransformMatrix(matView);
	// GAME_ENGINE->SetColor(COLOR(255,0,0,170));
	// GAME_ENGINE->FillHitRegion(m_HitRegionFlatThingyVerticalPtr);
	// GAME_ENGINE->SetColor(COLOR(0,255,0,170));
	// GAME_ENGINE->FillHitRegion(m_HitRegionFlatThingyHorizontalPtr);
	// GAME_ENGINE->SetColor(COLOR(0,0,0));

}

bool FlatThingy::Bounce()
{
	
	// Vertical collision
	RECT2 verticalTest = m_HitCharlieVerticalPtr->CollisionTest(m_HitRegionFlatThingyVerticalPtr);

	if (verticalTest.top > 0 && verticalTest.bottom - verticalTest.top < 10 )
	{
		m_IsEnemyDead = true;
		return true;
	}
	
	return false;

}

bool FlatThingy::EnemyDead()
{

	return m_IsEnemyDead;

}

bool FlatThingy::EnemyHit()
{
	
	// Horizontal collision
	RECT2 horizontalTest = m_HitCharlieHorizontalPtr->CollisionTest(m_HitRegionFlatThingyHorizontalPtr);

	if (abs(m_HitCharlieHorizontalPtr->GetBounds().right - horizontalTest.right) < 0.1)
	{
		return true; 
	}

	if (abs(m_HitCharlieHorizontalPtr->GetBounds().left - horizontalTest.left) < 0.1  && m_HitCharlieHorizontalPtr->GetBounds().left != 0)
	{
		return true;
	}

	return false;

}

DOUBLE2 FlatThingy::GetPosition()
{
	
	return m_Position;

}