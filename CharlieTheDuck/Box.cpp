//---------------------------
// Includes
//---------------------------
#include "Box.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Box::Box(DOUBLE2 position, int itemID):

			m_BmpBoxPtr(nullptr),
			m_BmpAnimationPtr(nullptr),

			m_HitRegionBoxPtr(nullptr),
			m_HitCharlieVerticalPtr(nullptr),
		
			m_Width(0),
			m_Height(0),
			m_CurrentAnimationStep(0),
			m_TickCounter(0),
			m_ItemID(itemID),

			m_Velocity(0,0),
			m_Gravity(0,750),
			m_Position(position),

			m_IsBroken(false),
			m_FirstPoof(true),
			m_IsBoxGone(false),
			m_IsItemDisplayed(false)
			
{
	
	if (m_BmpBoxPtr == nullptr)
	{
		m_BmpBoxPtr = new Bitmap("./resources/Box.bmp");
		m_BmpBoxPtr->SetTransparencyColor(255,0,255);
		m_Width = m_BmpBoxPtr->GetWidth() / NR_OF_ANIMATIONS;
		m_Height = m_BmpBoxPtr->GetHeight();
	}

	m_HitRegionBoxPtr = new HitRegion();
	m_HitRegionBoxPtr->CreateFromRect(0,0,m_Width,m_Height);

	m_HitRegionBoxPtr->SetPos(position);

	m_BmpAnimationPtr = new Bitmap("./resources/AnimationBreakingBox.bmp");
	m_BmpAnimationPtr->SetTransparencyColor(255,0,255);

	for (int index = 0 ; index < NUMBER_OF_BLOCKS ; index++)
	{
		m_VelocityArray[index] = DOUBLE2(0,0);
		m_BlockPositions[index] = position;
	}

}

Box::~Box()
{
	
	delete m_HitRegionBoxPtr;
	delete m_BmpBoxPtr;
	delete m_BmpAnimationPtr;

}

//---------------------------
// Own methods
//---------------------------

void Box::Paint(MATRIX3X2 matView)
{
	
	RECT clip; // RECT aanmaken voor box
	clip.left = m_Width * m_CurrentAnimationStep;
	clip.right = clip.left + m_Width;
	clip.top = 0;
	clip.bottom = m_Height;

	if (!m_IsBroken) // Als box niet gebroken is, painten
	{
		GAME_ENGINE->DrawBitmap(m_BmpBoxPtr,m_Position.x,m_Position.y,clip);
		// HitRegions
		// GAME_ENGINE->SetColor(COLOR(255,0,0,170));
		// GAME_ENGINE->FillHitRegion(m_HitRegionBoxPtr);
		// GAME_ENGINE->SetColor(COLOR(0,0,0));
	}

	if (m_IsBroken == true) // Als de box gebroken is de animatieblokjes painten
	{
		for (int index = 0 ; index < NUMBER_OF_BLOCKS ; index++)
		{
			GAME_ENGINE->DrawBitmap(m_BmpAnimationPtr,m_BlockPositions[index]);
		}
	}

}

void Box::Tick(HitRegion* verticalCollision, double deltaTime)
{
	
	m_TickCounter++;

	m_HitCharlieVerticalPtr = verticalCollision;

	if (m_TickCounter % 15 == 0)
	{
		m_CurrentAnimationStep = ++m_CurrentAnimationStep % NR_OF_ANIMATIONS; // Vertragen van animatie
	}

	Collision(); // Collision method aanroepen

	if (m_IsBroken == true) // Als de box gebroken is (Charlie heeft er bovenop gesprongen)
	{ // Open m_IsBroken if
		
		if (m_FirstPoof) // De eerste keer / moment dat de blokjes tevoorschijn komen (FirstPoof == true)
		{
			for (int index = 0 ; index < NUMBER_OF_BLOCKS ; index++)
			{
					m_VelocityArray[index].y -= rand()% 201 + 100; 
					// Elk blokje die eruit springt een willekeurige velocity geven in de y richting.
					if (index % 2 == 0)
					{
						m_VelocityArray[index].x -= rand()% 51 + 50;
					}
					else
					{
						m_VelocityArray[index].x += rand()% 51 + 50;
					}
					// Elk blokje die eruit springt een willekeurige velocity geven in de x richting.
					// Als de nummer van het blokje (index) even is zal hij naar links vliegen anders naar rechts.
			}
		
			m_FirstPoof = false; // Als de for gebeurt is de m_FirstPoof op false zetten zo dat de for niet meer gebeurt.
			
		}

		for (int index = 0 ; index < NUMBER_OF_BLOCKS ; index++)
		{
				m_VelocityArray[index] += m_Gravity * deltaTime; 
				m_BlockPositions[index] += m_VelocityArray[index] * deltaTime;
				// Bij elk blokje gravity optellen bij de velocity zodat deze naar beneden vallen &
				// de posities aanpassen aan de hand van de velocity van het blokje.
		}

		int maxYPos = 634; // Hoogte van het scherm

		for (int index = 0 ; index < NUMBER_OF_BLOCKS ; index++)
		{
			if (index + 1 >= NUMBER_OF_BLOCKS)
			{
				int temp = maxYPos;
				maxYPos = Max(m_BlockPositions[index].y, m_BlockPositions[index + 1].y);

				if (temp < maxYPos)
				{
					maxYPos = temp;
				}
				// Bij elk blokje (index) kijken of zijn y-positie groter is dan het volgende blokje (index+1),
				// tussen beide de hoogste positie bijhouden.
				// "Groter" en "hoogste" als in visueel op het scherm hoger dan het andere blokje.
			}
		}

		if(maxYPos >= 633) // Als het hoogste blokje onder het scherm komt,
		{
			m_IsBoxGone = true; // word m_IsBoxGone op true gezet en word deze verwijderd.
		}

	} // Sluiten m_IsBroken if
	
}

void Box::Collision() // Method voor collision
{

	// Vertical collision
	RECT2 verticalTest = m_HitCharlieVerticalPtr->CollisionTest(m_HitRegionBoxPtr);

	if (verticalTest.top > 0 && m_IsBroken == false)
	{
		m_IsBroken = true;
		m_IsItemDisplayed == true;
	}

}

int Box::Max(int number1, int number2) // Method om grootste getal van 2 getallen te bepalen
{
	
	if (number1 < number2)
	{
		return number1;
	}

	else
	{
		return number2;
	}

}

bool Box::IsBoxGone()
{

	return m_IsBoxGone;

}

int Box::ReturnItemID()
{
	
	return m_ItemID;

}

bool Box::IsBoxBroken()
{
	
	return m_IsBroken;

}