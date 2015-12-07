//---------------------------
// Includes
//---------------------------
#include "ItemList.h"

#include "Coin.h"
#include "Diamond.h"
#include "Heart.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
ItemList::ItemList():

		m_HitCharlieVerticalPtr(nullptr),
		m_HitCharlieHorizontalPtr(nullptr),

		m_BmpCollectingStarsPtr(nullptr),
		
		m_TickCounter(0),
		m_CurrentAnimationStep(0),

		m_PositionStars(0,0)	

{
		
		// ----- Array vullen -----

		// Coins
		m_ArrayOfItemsPtr[0] = new Coin(DOUBLE2(198,288),false); 
		m_ArrayOfItemsPtr[1] = new Coin(DOUBLE2(238,288),false); 
		m_ArrayOfItemsPtr[2] = new Coin(DOUBLE2(278,288),false); 
		m_ArrayOfItemsPtr[3] = new Coin(DOUBLE2(845,478),true); 
		m_ArrayOfItemsPtr[4] = new Coin(DOUBLE2(885,478),true); 
		m_ArrayOfItemsPtr[5] = new Coin(DOUBLE2(1200,448),false); 
		m_ArrayOfItemsPtr[6] = new Coin(DOUBLE2(1835,284),false); 
		m_ArrayOfItemsPtr[7] = new Coin(DOUBLE2(1875,284),false); 
		m_ArrayOfItemsPtr[8] = new Coin(DOUBLE2(1915,284),false); 
		m_ArrayOfItemsPtr[9] = new Coin(DOUBLE2(2272,478),true); 
		m_ArrayOfItemsPtr[10] = new Coin(DOUBLE2(2592,131),false); 
		m_ArrayOfItemsPtr[11] = new Coin(DOUBLE2(2592,169),false); 
		m_ArrayOfItemsPtr[12] = new Coin(DOUBLE2(2592,207),false); 
		m_ArrayOfItemsPtr[13] = new Coin(DOUBLE2(2917,320),false); 
		m_ArrayOfItemsPtr[14] = new Coin(DOUBLE2(2957,320),true); 
		m_ArrayOfItemsPtr[15] = new Coin(DOUBLE2(3007,320),false); 
		m_ArrayOfItemsPtr[16] = new Coin(DOUBLE2(2307,285),false); 
		m_ArrayOfItemsPtr[17] = new Coin(DOUBLE2(2347,285),false); 
		m_ArrayOfItemsPtr[18] = new Coin(DOUBLE2(4240,484),false);
		m_ArrayOfItemsPtr[19] = new Coin(DOUBLE2(4987,395),false);
		m_ArrayOfItemsPtr[20] = new Coin(DOUBLE2(5027,395),false);
		m_ArrayOfItemsPtr[21] = new Coin(DOUBLE2(5067,415),true);
		m_ArrayOfItemsPtr[22] = new Coin(DOUBLE2(5107,395),false);
		m_ArrayOfItemsPtr[23] = new Coin(DOUBLE2(5147,395),false);
		m_ArrayOfItemsPtr[24] = new Coin(DOUBLE2(5845,320),false);
		m_ArrayOfItemsPtr[25] = new Coin(DOUBLE2(5885,320),false);
		m_ArrayOfItemsPtr[26] = new Coin(DOUBLE2(5925,320),false);
		m_ArrayOfItemsPtr[27] = new Coin(DOUBLE2(6132,320),false);
		m_ArrayOfItemsPtr[28] = new Coin(DOUBLE2(6172,320),false);
		m_ArrayOfItemsPtr[29] = new Coin(DOUBLE2(6212,320),false);
		// Diamonds
		m_ArrayOfItemsPtr[30] = new Diamond(DOUBLE2(499,355),false); 
		m_ArrayOfItemsPtr[31] = new Diamond(DOUBLE2(522,355),false); 
		m_ArrayOfItemsPtr[32] = new Diamond(DOUBLE2(545,355),false); 
		m_ArrayOfItemsPtr[33] = new Diamond(DOUBLE2(1890,478),true); 
		m_ArrayOfItemsPtr[34] = new Diamond(DOUBLE2(2272,445),true);
		m_ArrayOfItemsPtr[35] = new Diamond(DOUBLE2(3000,451),false);
		m_ArrayOfItemsPtr[36] = new Diamond(DOUBLE2(3200,325),false);
		m_ArrayOfItemsPtr[37] = new Diamond(DOUBLE2(3568,447),false);
		m_ArrayOfItemsPtr[38] = new Diamond(DOUBLE2(3919,482),true);
		m_ArrayOfItemsPtr[39] = new Diamond(DOUBLE2(3960,482),true);
		m_ArrayOfItemsPtr[40] = new Diamond(DOUBLE2(5270,320),false);
		m_ArrayOfItemsPtr[41] = new Diamond(DOUBLE2(5310,320),false);
		m_ArrayOfItemsPtr[42] = new Diamond(DOUBLE2(5350,320),false);
		// Hearts
		m_ArrayOfItemsPtr[43] = new Heart(DOUBLE2(1931,478),true); 
		m_ArrayOfItemsPtr[44] = new Heart(DOUBLE2(4793,482),true);	

		m_BmpCollectingStarsPtr = new Bitmap("./resources/Collecting Stars.bmp");
		m_BmpCollectingStarsPtr->SetTransparencyColor(255,0,255);
			
}

ItemList::~ItemList()
{
	
	for (int index = 0 ; index < MAX_ITEMS; index++)
	{
		delete m_ArrayOfItemsPtr[index];
		m_ArrayOfItemsPtr[index] = nullptr;
	}

	delete m_BmpCollectingStarsPtr;

}

//---------------------------
// Own methods
//---------------------------

void ItemList::Tick(HitRegion* verticalCollision, HitRegion* horizontalCollision)
{
	
	m_TickCounter++;

	m_HitCharlieVerticalPtr = verticalCollision;
	m_HitCharlieHorizontalPtr = horizontalCollision;
	
	for (int index = 0; index < MAX_ITEMS; index++)
	{
		if (m_ArrayOfItemsPtr[index] != nullptr)
		{
			if (m_ArrayOfItemsPtr[index]->IsPickedUp() == true)
			{
				m_PositionStars = m_ArrayOfItemsPtr[index]->GetPosition();
				delete m_ArrayOfItemsPtr[index];
				m_ArrayOfItemsPtr[index] = nullptr;
				m_CurrentAnimationStep = 0;					
			}
		}	
	}
	for (int index = 0 ; index < MAX_ITEMS ; index++)
	{	

		if (m_ArrayOfItemsPtr[index] != nullptr)
		{
			m_ArrayOfItemsPtr[index]->Tick(m_HitCharlieVerticalPtr, m_HitCharlieHorizontalPtr);	
		}
	}	

	if (m_TickCounter == 10)
	{
		m_CurrentAnimationStep++;
		m_TickCounter = 0;
	}	

}

void ItemList::Paint(MATRIX3X2 matView)
{
	
	for (int index = 0 ; index < MAX_ITEMS ; index++)
	{

		if (m_ArrayOfItemsPtr[index] != nullptr)
		{
			m_ArrayOfItemsPtr[index]->Paint(matView);
		}

	}

	RECT clip; // RECT voor sterretjes
	clip.left = m_BmpCollectingStarsPtr->GetWidth()/4 * m_CurrentAnimationStep;
	clip.right = clip.left + m_BmpCollectingStarsPtr->GetWidth()/4;
	clip.top = 0;
	clip.bottom = m_BmpCollectingStarsPtr->GetHeight();
	if (m_CurrentAnimationStep <= 4)
	GAME_ENGINE->DrawBitmap(m_BmpCollectingStarsPtr,m_PositionStars.x,m_PositionStars.y,clip);


}

void ItemList::SetItemDisplayed(int ItemId)
{
	
	m_ArrayOfItemsPtr[ItemId]->SetIsInBox(false);

}

bool ItemList::IsItemInBox(int ItemId)
{
	
	return m_ArrayOfItemsPtr[ItemId]->ReturnIsInBox();

}


bool ItemList::ItemExists(int ItemId)
{
	
	if (m_ArrayOfItemsPtr[ItemId] != nullptr)
	{
		return true;
	}
	else 
	{
		return false;
	}

}