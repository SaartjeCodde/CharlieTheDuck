#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Coin.h"
#include "Heart.h"
#include "Diamond.h"
#include "Charlie.h"


//-----------------------------------------------------
// HUD Class									
//-----------------------------------------------------
class HUD
{
public:
	HUD();				// Constructor
	virtual ~HUD();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	void Tick();
	void Paint();

	void GameOver(bool isDead);

	void AddToEnemyScore(int enemyScore);

	static const int MAX_COINS = 30;
	static const int MAX_DIAMONDS = 13;
	static const int MAX_HEARTS = 2;

	static const int SCORE_COINS = 50;
	static const int SCORE_DIAMONDS = 100;
	static const int SCORE_HEARTS = 500;	
	

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
			
	Bitmap *m_BmpCoinIconPtr;
	Bitmap *m_BmpHeartIconPtr;
	Bitmap *m_BmpDiamondIconPtr;
	Bitmap *m_BmpGameOverPtr;

	int m_AmountOfCoins;
	int m_AmountOfDiamonds;
	int m_AmountOfHearts;
	int m_Score;
	int m_Life;

	DOUBLE2 m_Position;

	int m_EnemyScore;

	Font *m_HUDFontPtr;

	double m_DeltaTime;
	
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	HUD(const HUD& yRef);									
	HUD& operator=(const HUD& yRef);	
};

 
