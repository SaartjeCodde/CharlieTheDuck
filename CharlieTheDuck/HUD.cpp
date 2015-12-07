//---------------------------
// Includes
//---------------------------
#include "HUD.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
HUD::HUD():

		m_BmpCoinIconPtr(nullptr),
		m_BmpDiamondIconPtr(nullptr),
		m_BmpHeartIconPtr(nullptr),
		m_HUDFontPtr(nullptr),
		m_AmountOfCoins(0),
		m_AmountOfDiamonds(0),
		m_AmountOfHearts(0),
		m_Score(0),
		m_Position(0,0),
		m_EnemyScore(0)

{
	
	m_BmpCoinIconPtr = new Bitmap("./resources/Coin icon.png");
	m_BmpCoinIconPtr->SetTransparencyColor(255,255,255);
	
	m_BmpHeartIconPtr = new Bitmap("./resources/Heart icon.bmp");
	m_BmpHeartIconPtr->SetTransparencyColor(255,0,255);
	
	m_BmpDiamondIconPtr = new Bitmap("./resources/Diamond icon.png");
	m_BmpDiamondIconPtr->SetTransparencyColor(255,0,255);
	
	m_BmpGameOverPtr = new Bitmap("./resources/Game Over.png");
	
	m_HUDFontPtr = new Font("Calibri",20);
	
}

HUD::~HUD()
{
	
	delete m_BmpCoinIconPtr;
	delete m_BmpDiamondIconPtr;
	delete m_BmpHeartIconPtr;
	delete m_HUDFontPtr;

}

//---------------------------
// Own methods
//---------------------------

void HUD::Tick()
{
	
	m_AmountOfCoins = MAX_COINS - Coin::GetAmountPickedUp();
	m_AmountOfHearts = Heart::GetAmountPickedUp();
	m_AmountOfDiamonds = MAX_DIAMONDS - Diamond::GetAmountPickedUp();
	m_Score = (m_AmountOfCoins * SCORE_COINS) + (m_AmountOfDiamonds * SCORE_DIAMONDS) + (m_AmountOfHearts * SCORE_HEARTS) + (m_EnemyScore);
	m_Life = Charlie::ReturnAmountOfLives();

}

void HUD::Paint()
{
	
	GAME_ENGINE->SetFont(m_HUDFontPtr);
	GAME_ENGINE->SetColor(COLOR(255,255,255));

	MATRIX3X2 matView;
	matView.SetAsTranslate(m_Position);
	matView = matView.Inverse();

	GAME_ENGINE->SetTransformMatrix(matView);

	// Coins collected
	GAME_ENGINE->DrawBitmap(m_BmpCoinIconPtr, m_Position.x + 250, 10);
	GAME_ENGINE->DrawString(String("x ") + m_AmountOfCoins, m_Position.x + 285, 10);
	// Diamonds collected
	GAME_ENGINE->DrawBitmap(m_BmpDiamondIconPtr, m_Position.x + 150, 10);
	GAME_ENGINE->DrawString(String("x ") + m_AmountOfDiamonds, m_Position.x + 185, 10);
	// Hearts collected
	GAME_ENGINE->DrawBitmap(m_BmpHeartIconPtr, m_Position.x + 350, 10);
	GAME_ENGINE->DrawString(String("x ") + (Charlie::m_Hearts + m_AmountOfHearts),m_Position.x + 385, 10);
	// Score
	GAME_ENGINE->DrawString(String("SCORE: ") + m_Score, m_Position.x + 450, 10);
	// Leven
	GAME_ENGINE->DrawString(String("CHARLIE x ") + m_Life, m_Position.x + 10, 10);
	
}

void HUD::GameOver(bool isDead)
{
		
	if (isDead == true)
	{
		GAME_ENGINE->DrawBitmap(m_BmpGameOverPtr,0,0);			
	}

}

void HUD::AddToEnemyScore(int enemyScore)
{
	
	m_EnemyScore += enemyScore; // Wordt opgeroepen in de main

}