//---------------------------
// Includes
//---------------------------

#include "Frog.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

Bitmap* Frog::m_BmpFrogPtr = nullptr;
int Frog::m_Width = 0, Frog::m_Height = 0;

//---------------------------
// Constructor & Destructor
//---------------------------
Frog::Frog(DOUBLE2 position, int path): Enemy(position, path),

		m_HitRegionFrogVerticalPtr(nullptr),
		m_HitRegionFrogHorizontalPtr(nullptr),
		m_JumpHeight(100),
		m_EnemyGoingUp(true)

{
	
	if (m_BmpFrogPtr == nullptr)
	{
		m_BmpFrogPtr = new Bitmap("./resources/Frog.png");
		m_BmpFrogPtr->SetTransparencyColor(255,0,255);
		m_Width = m_BmpFrogPtr->GetWidth() / NR_OF_ANIMATIONS;
		m_Height = m_BmpFrogPtr->GetHeight();
	}

	m_StartPosition = m_Position;
	
	// Hitregions aanmaken
	m_HitRegionFrogVerticalPtr = new HitRegion();
	m_HitRegionFrogVerticalPtr->CreateFromRect(2, 0, (m_BmpFrogPtr->GetWidth()/NR_OF_ANIMATIONS)-2, m_BmpFrogPtr->GetHeight()/3);
	m_HitRegionFrogHorizontalPtr = new HitRegion();
	m_HitRegionFrogHorizontalPtr->CreateFromRect(0, 10, m_BmpFrogPtr->GetWidth()/NR_OF_ANIMATIONS, m_BmpFrogPtr->GetHeight()-10);


}

Frog::~Frog()
{
	
		delete m_HitRegionFrogVerticalPtr;
		delete m_HitRegionFrogHorizontalPtr;

}

//---------------------------
// Own methods
//---------------------------

void Frog::Tick(double deltaTime, HitRegion* verticalCollision, HitRegion* horizontalCollision)
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

	// Woordje uitleg voor mezelf:
	// Als de positie van de enemy kleiner is dan de startpositie + het pad dat de enemy moet afleggen, vermeerderd de positie naar rechts en omgekeerd.
	// De bool m_EnemyGoingRight is geimplementeert omdat als de enemy moet terug keren na een eerste keer het pad af te leggen,
	// de eerste if direct terug gebeurt en de enemy anders het pad maar 1 keer doet en op het einde blijft steken.
		
		if (m_Position.y >= m_StartPosition.y - m_JumpHeight && m_EnemyGoingUp == true)
		{
			m_Position.y -= 3;
		}
		if (m_Position.y <= m_StartPosition.y - m_JumpHeight)
		{
			m_EnemyGoingUp = false;
		}
		if (m_Position.y <= m_StartPosition.y && m_EnemyGoingUp == false)
		{
			m_Position.y += 3;
		}
		if (m_Position.y >= m_StartPosition.y)
		{
			m_EnemyGoingUp = true;
		}
		// Om de kikker te doen springen
	}

	else
	{
		m_Position.y += 5;

		if (m_Position.y > GAME_ENGINE->GetHeight())
		{
			// Delete enemy, gebeurt in de main
		}
	}

	m_HitRegionFrogHorizontalPtr->SetPos(m_Position);
	m_HitRegionFrogVerticalPtr->SetPos(m_Position);

}

void Frog::Paint(MATRIX3X2 matView)
{
	
	// Matrices
	MATRIX3X2 transformFrog;
	transformFrog.SetAsTranslate(m_Position);

	// Flip
	int offset;
	offset = m_BmpFrogPtr->GetWidth() / 2;
	MATRIX3X2 scaleFrog;

	if(!m_EnemyGoingRight)
	scaleFrog.SetAsScale(-1,1);
	else
	scaleFrog.SetAsScale(1,1);

	 if (m_IsEnemyDead == true)
	{
		scaleFrog.SetAsScale(1,-1);
	}

	 GAME_ENGINE->SetTransformMatrix(scaleFrog * transformFrog * matView);

	RECT clip;

	if (!m_EnemyGoingUp)
	clip.left = 0 * m_TickCount;
	else
	clip.left = m_Width ;

	clip.right = clip.left + m_Width;
	clip.top = 0;
	clip.bottom = m_Height;
	if (m_IsEnemyDead == false)
	{
		GAME_ENGINE->DrawBitmap(m_BmpFrogPtr,0,0,clip);
	
		GAME_ENGINE->SetColor(COLOR(255,0,0,170));
		// GAME_ENGINE->FillHitRegion(m_HitRegionFrogPtr);
		GAME_ENGINE->SetColor(COLOR(0,0,0));
	}
	else
	{
		GAME_ENGINE->DrawBitmap(m_BmpFrogPtr,0,0-50,clip);
	}

}

bool Frog::Bounce()
{
	
	// Vertical collision
	RECT2 verticalTest = m_HitCharlieVerticalPtr->CollisionTest(m_HitRegionFrogVerticalPtr);

	if (verticalTest.top > 0 && verticalTest.bottom - verticalTest.top < 10 )
	{
		m_IsEnemyDead = true;
		return true;
	}
	
	return false;

}

bool Frog::EnemyDead()
{

	return m_IsEnemyDead;

}

bool Frog::EnemyHit()
{

	// Horizontal collision
	RECT2 horizontalTest = m_HitCharlieHorizontalPtr->CollisionTest(m_HitRegionFrogHorizontalPtr);

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

DOUBLE2 Frog::GetPosition()
{
	
	return m_Position;

}