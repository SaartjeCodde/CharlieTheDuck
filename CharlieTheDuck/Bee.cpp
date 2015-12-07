//---------------------------
// Includes
//---------------------------
#include "Bee.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

Bitmap* Bee::m_BmpBeePtr = nullptr;
int Bee::m_Width = 0, Bee::m_Height = 0;

//---------------------------
// Constructor & Destructor
//---------------------------
Bee::Bee(DOUBLE2 position, int path): Enemy(position, path),

		m_CurrentAnimationStep(0),
		m_Random(0),

		m_EnemyGoingUp(false)

{
		
	if (m_BmpBeePtr == nullptr)
	{
		m_BmpBeePtr = new Bitmap("./resources/Bee.png");
		m_BmpBeePtr->SetTransparencyColor(255,0,255);
		m_Width = m_BmpBeePtr->GetWidth()/NR_OF_ANIMATIONS;
		m_Height = m_BmpBeePtr->GetHeight();
	}

	m_StartPosition = m_Position;
	
	// Hitregions
	m_HitRegionBeeVerticalPtr = new HitRegion();
	m_HitRegionBeeVerticalPtr->CreateFromRect(10,0,(m_BmpBeePtr->GetWidth()/NR_OF_ANIMATIONS)-10,m_BmpBeePtr->GetHeight()/3);
	m_HitRegionBeeHorizontalPtr = new HitRegion();
	m_HitRegionBeeHorizontalPtr->CreateFromRect(0,10,m_BmpBeePtr->GetWidth()/NR_OF_ANIMATIONS,m_BmpBeePtr->GetHeight()-10);

}

Bee::~Bee()
{
	
	delete m_HitRegionBeeVerticalPtr;
	delete m_HitRegionBeeHorizontalPtr;
	m_HitRegionBeeVerticalPtr = nullptr;
	m_HitRegionBeeHorizontalPtr = nullptr;

}

//---------------------------
// Own methods
//---------------------------

void Bee::Tick(double deltaTime, HitRegion* verticalCollision, HitRegion* horizontalCollision)
{
	
	m_HitCharlieVerticalPtr = verticalCollision;
	m_HitCharlieHorizontalPtr = horizontalCollision;

	++m_TickCount;

	if (m_TickCount == 2)
	{
		m_TickCount = 0;
	}	

	m_Random = rand() % 70 + 10;	
	if (m_IsEnemyDead == false)
	{ // Open if m_IsEnemyDead

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
				m_IsFacingLeft = true;
			}
		}
		// Positie op de x-as verplaatsen
		
		if (m_Position.y >= m_StartPosition.y - 50 && m_EnemyGoingUp == true)
		{
			m_Position.y -= 1;
		}
		if (m_Position.y <= m_StartPosition.y - 30)
		{
			m_EnemyGoingUp = false;
		}
		if (m_Position.y <= m_StartPosition.y + 50 && m_EnemyGoingUp == false)
		{
			m_Position.y += 1;
		}
		if (m_Position.y >= m_StartPosition.y + 30)
		{
			m_EnemyGoingUp = true;
		}
		// Positie op de y-as verplaatsen

		// Woordje uitleg voor mezelf:
		// Als de positie van de enemy kleiner is dan de startpositie + het pad dat de enemy moet afleggen, vermeerderd de positie naar rechts en omgekeerd.
		// De bool m_EnemyGoingRight is geimplementeert omdat als de enemy moet terug keren na een eerste keer het pad af te leggen,
		// de eerste if direct terug gebeurt en de enemy anders het pad maar 1 keer doet en op het einde blijft steken.

	} // Sluiten if m_IsEnemyDead
	
	else
	{
		m_Position.y += 5;

		if (m_Position.y > GAME_ENGINE->GetHeight())
		{
			// Delete enemy, word gedelete in de main
		}
	}

	if (!m_EnemyGoingRight)
	{
		m_HitRegionBeeVerticalPtr->SetPos(m_Position);
		m_HitRegionBeeHorizontalPtr->SetPos(m_Position);
	}
	
	else
	{
		// Zorgen dat de hitregion mee draait en op de correcte positie staat, anders zweefde hij ernaast
		int offset;
		offset = m_BmpBeePtr->GetWidth() / 3;

		DOUBLE2 tempPos = m_Position;
		tempPos.x -= offset;

		m_HitRegionBeeVerticalPtr->SetPos(tempPos);
		m_HitRegionBeeHorizontalPtr->SetPos(tempPos);
	}

	m_TickCount++;

	if (m_TickCount % 5 == 0)
	{
		m_CurrentAnimationStep = ++m_CurrentAnimationStep % NR_OF_ANIMATIONS; // Animaties vertragen
	}

}

void Bee::Paint(MATRIX3X2 matView)
{

	// Matrices
	MATRIX3X2 transformBee;
	transformBee.SetAsTranslate(m_Position);

	// Flip
	 int offset;
	 offset = m_Width;
	 MATRIX3X2 scaleBee;

	 if (!m_EnemyGoingRight)
	 {
		scaleBee.SetAsScale(-1,1);
	 }
	 else
	 {
		scaleBee.SetAsScale(1,1);
	 }

	 if (m_IsEnemyDead == true)
	 {
		 scaleBee.SetAsScale(1,-1);
	 }
	 
	 GAME_ENGINE->SetTransformMatrix(scaleBee * transformBee * matView);
	 	
		RECT clip;
		clip.left = m_Width * m_CurrentAnimationStep;
		clip.right = clip.left + m_Width;
		clip.top = 0;
		clip.bottom = m_Height;
				
	if (m_IsEnemyDead == true)
	{
		GAME_ENGINE->DrawBitmap(m_BmpBeePtr,0,0 - 50,clip);
	}
	else
	{
		GAME_ENGINE->DrawBitmap(m_BmpBeePtr,0 - offset,0,clip);
	}	
	
	// Hitregions
	// GAME_ENGINE->SetTransformMatrix(matView);
	// GAME_ENGINE->SetColor(COLOR(255,0,0,170));
	// GAME_ENGINE->FillHitRegion(m_HitRegionBeeVerticalPtr);
	// GAME_ENGINE->SetColor(COLOR(0,255,0,170));
	// GAME_ENGINE->FillHitRegion(m_HitRegionBeeHorizontalPtr);
	// GAME_ENGINE->SetColor(COLOR(0,0,0));	

}

bool Bee::Bounce()
{
	
	// Vertical collision
	RECT2 verticalTest = m_HitCharlieVerticalPtr->CollisionTest(m_HitRegionBeeVerticalPtr);

	if (verticalTest.top > 0 && verticalTest.bottom - verticalTest.top < 10 )
	{
		m_IsEnemyDead = true;
		return true;
	}

	return false;

}

bool Bee::EnemyDead()
{

	return m_IsEnemyDead;

}

bool Bee::EnemyHit()
{
	
	// Horizontal collision
	RECT2 horizontalTest = m_HitCharlieHorizontalPtr->CollisionTest(m_HitRegionBeeHorizontalPtr);

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

DOUBLE2 Bee::GetPosition()
{
	
	return m_Position;

}