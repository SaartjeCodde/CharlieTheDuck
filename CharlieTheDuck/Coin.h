#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Item.h"
//-----------------------------------------------------
// Coin Class									
//-----------------------------------------------------
class Coin: public Item
{
public:
	Coin(DOUBLE2 position, bool inBox);				// Constructor
	virtual ~Coin();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	virtual void Paint(MATRIX3X2 matView);
	virtual void Tick(HitRegion* verticalCollision, HitRegion* horizontalCollision);
	virtual void Collision();
	virtual void SetIsInBox(bool inBox);
	virtual bool ReturnIsInBox();

	virtual DOUBLE2 GetPosition();

	virtual bool IsPickedUp();

	static int GetAmountPickedUp();

	static int m_AmountPickedUp;



private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	static Audio* m_CoinCollectedPtr;

	static Bitmap* m_BmpCoinPtr;
	
	static int m_Width;
	static int m_Height;
	
	static const int NR_OF_ANIMATIONS = 8;

	HitRegion* m_HitRegionCoinPtr;
	
	int m_CurrentAnimationStep;
	int m_TickCounter;	

	bool m_IsInBox;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Coin(const Coin& yRef);									
	Coin& operator=(const Coin& yRef);	
};

 
