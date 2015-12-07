//-----------------------------------------------------------------
// Game File
// C++ Source - CharlieTheDuck.cpp - version v2_12 jan 2013 
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "CharlieTheDuck.h"	

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//-----------------------------------------------------------------
// CharlieTheDuck methods																				
//-----------------------------------------------------------------

CharlieTheDuck::CharlieTheDuck():
				
		m_BmpLevelPtr(nullptr),
		m_BmpWaterPtr(nullptr),
		m_BmpCloudPtr(nullptr),

		m_HitLevelPtr(nullptr),
		m_HitWaterPtr(nullptr),

		m_TickCounter(0),
		m_WaterAnimationStep(0),
		m_CloudAnimationStep(0),

		m_PositionCamera(0,0),
		m_CloudPosition(0,0),

		m_IsCameraEnabled(true),

		m_IsGameStarted(false)

{
	// nothing to create
}

CharlieTheDuck::~CharlieTheDuck()																						
{
	
	delete m_BmpLevelPtr;
	delete m_BmpWaterPtr;
	delete m_BmpCloudPtr;

	delete m_HitLevelPtr;
	delete m_HitWaterPtr;

}

void CharlieTheDuck::GameInitialize(HINSTANCE hInstance)			
{
	// Set the required values
	AbstractGame::GameInitialize(hInstance);
	GAME_ENGINE->SetTitle("CharlieTheDuck - Codde Saartje");					
	GAME_ENGINE->RunGameLoop(true);
	
	// Set the optional values
	GAME_ENGINE->SetWidth(632);
	GAME_ENGINE->SetHeight(632);
	//GAME_ENGINE->SetKeyList(String("QSDZ") + (TCHAR) VK_SPACE);
}

void CharlieTheDuck::GameStart()
{
	
	// HitRegion aanmaken voor click area startscherm
	m_HitRegionStartScherm = new HitRegion;
	m_HitRegionStartScherm->CreateFromRect(203,304,425,367);
	
	// Bitmap & HitRegion van level aanmaken
	m_BmpLevelPtr = new Bitmap("./resources/Background.png");
	m_HitLevelPtr = new HitRegion();
	m_HitLevelPtr->CreateFromSVG("./resources/Background.svg");

	// Bitmap & HitRegion van water maken
	m_BmpWaterPtr = new Bitmap("./resources/Water.bmp");
	m_BmpWaterPtr->SetTransparencyColor(255,0,255);
	m_HitWaterPtr = new HitRegion();
	m_HitWaterPtr->CreateFromSVG("./resources/Water hitregion.svg");

	// Bitmap van wolkjes aanmaken
	m_BmpCloudPtr = new Bitmap("./resources/Cloud.bmp");
	m_BmpCloudPtr->SetTransparencyColor(255,0,255);

	// Charlie aanmaken
	m_CharliePtr = new Charlie();
	
	// Itemlist aanmaken
	m_ArrayOfItemsPtr = new ItemList();

	// End level sign aanmaken
	m_EndLevelSignPtr = new EndLevel(DOUBLE2(6017,282));

	// Startscherm aanmaken
	m_BmpStartSchermPtr = new Bitmap("./resources/StartScherm.png");

	// Boxes
	// m_BoxArrayPtr[x] = new Box(DOUBLE2(x,y),ItemID)
	// -> ItemID is het nummer van de corresponderende index in de Itemlist
	m_BoxArrayPtr[0] = new Box(DOUBLE2(845,478),3); 
	m_BoxArrayPtr[1] = new Box(DOUBLE2(885,478),4); 
	m_BoxArrayPtr[2] = new Box(DOUBLE2(1890,478),33);
	m_BoxArrayPtr[3] = new Box(DOUBLE2(1931,478),43);
	m_BoxArrayPtr[4] = new Box(DOUBLE2(2272,445),34); 
	m_BoxArrayPtr[5] = new Box(DOUBLE2(2272,478),9); 
	m_BoxArrayPtr[6] = new Box(DOUBLE2(2957,320),14);
	m_BoxArrayPtr[7] = new Box(DOUBLE2(3919,482),38);
	m_BoxArrayPtr[8] = new Box(DOUBLE2(3960,482),39);
	m_BoxArrayPtr[9] = new Box(DOUBLE2(5067,415),21);
	m_BoxArrayPtr[10] = new Box(DOUBLE2(4793,482),44);
	
	// Bouncing boxes aanmaken
	m_BouncingBoxPtr = new BouncingBox(DOUBLE2(2544,478));
	m_BouncingBox2Ptr = new BouncingBox(DOUBLE2(2593,339));

	// Enemylist aanmaken
	m_EnemyListPtr = new EnemyList();
	
	for (int index = 0 ; index < MAX_ENEMIES ; index++)
	{
		m_EnemyArrayPtr[index] = m_EnemyListPtr->GetArrayOfEnemies(index);
	}
	// Woordje uitleg voor mezelf:
	// Enemy array wordt gevuld in EnemyList, en via loop steek ik deze één voor één in de array van main (CharlieTheDuck.cpp)
	// -> Waarom bij enemies en niet bij items? 
	// Items worden aangemaakt in de ItemList en moeten niet via loop één voor één in de array van de main komen omdat alles wat er met de items moet gebeuren, gewoon in de ItemList klasse kan gebeuren.
	// Bij de enemies gaat dit niet omdat Charlie moet bounce'n en dat kan niet vanuit de EnemyList klasse omdat ik daar niet aan Charlie kan.	

	// HUD aanmaken
	m_HUDPtr = new HUD;

}

void CharlieTheDuck::GameEnd()
{	
}

void CharlieTheDuck::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{	

	// HitTest voor click area startscherm
	if (isLeft == true && isDown == true)
	{
		if (m_HitRegionStartScherm->HitTest(x,y))
		{
			m_IsGameStarted = true; 
		}
	}	

}

//void CharlieTheDuck::MouseMove(int x, int y, WPARAM wParam)
//{	
//}

//void CharlieTheDuck::CheckKeyboard()
//{	
//}

//void CharlieTheDuck::KeyPressed(TCHAR cKey)
//{	
//}

void CharlieTheDuck::GameTick(double deltaTime)
{
	
	if (m_IsGameStarted == true) 
	// Wanneer er op de click area van het startscherm geklikt word, 
	// word de bool op true gezet en mag de tick uitgevoerd worden.
	{ // Start grote if

		m_EndLevelSignPtr->Tick(m_CharliePtr->GetPosition().x); 
		// Bordje begint te draaien zodra Charlie er voorbij loopt, 
		// x-pos van Charlie word meegegeven in de tick

		m_TickCounter++;
		if (m_TickCounter % 10 == 0)
		{
			m_WaterAnimationStep = ++m_WaterAnimationStep % 3;
			m_CloudAnimationStep = ++m_CloudAnimationStep % 2;
		} // Animaties van water en wolkjes regelen

		m_CharliePtr->Tick(deltaTime, m_HitLevelPtr, m_HitWaterPtr);

		m_IsCameraEnabled = m_CharliePtr->GetCameraState();

		// Keep Charlie in the middle of the screen
		if (GAME_ENGINE->IsKeyDown((TCHAR) VK_LEFT) && m_IsCameraEnabled && m_CharliePtr->GetPosition().x <= m_BmpLevelPtr->GetWidth() - GAME_ENGINE->GetWidth()/2)
		{
			m_PositionCamera.x -= 200 *deltaTime;
		}
		// Als er op links geduwt word en de camera staat aan (mag bewegen) en hij is niet voorbij het eindpunt van het level
		// (width bitmap - helft van gamescreen)**
		// -> Verplaats de camera met dezelfde hoeveelheid als Charlie.

		if (GAME_ENGINE->IsKeyDown((TCHAR) VK_RIGHT) && m_IsCameraEnabled && m_CharliePtr->GetPosition().x >= GAME_ENGINE->GetWidth()/2)
		{
			m_PositionCamera.x += 200 *deltaTime;
		}
		// Als er op rechts geduwd word en de camera staat aan (mag bewegen) en hij is niet achter het het begintpunt van het level
		// (helft van gamescreen)**
		// -> Verplaats de camera met dezelfde hoeveelheid als Charlie

		// ** De camera beweegt niet mee naar links als hij voorbij dat punt is zelfde principe bij rechts maar omgekeerd

		// Camera limitations at beginning & end of level
		if (m_PositionCamera.x <= 0) // Als de camera zijn positie kleiner of gelijk is aan het begin van het level (0)
		{
			m_PositionCamera.x = 0; // -> De positie terug gelijk stellen aan het begin van het level
		}
		if (m_PositionCamera.x >= m_BmpLevelPtr->GetWidth() - GAME_ENGINE->GetWidth()) 
		// Als de camera zijn positie groter of gelijk is aan het eind van het level
		// (width bitmap - width gamescreen)
		{
			m_PositionCamera.x = m_BmpLevelPtr->GetWidth() - GAME_ENGINE->GetWidth();
			// -> De positie terug gelijk stellen aan eind van level
		}

		m_CharliePtr->SetCameraState(true);

		for (int index = 0; index < MAX_ENEMIES; index++)
		{
			if (m_EnemyArrayPtr[index] != nullptr)
			{
				if (m_EnemyArrayPtr[index]->GetPosition().y > GAME_ENGINE->GetHeight())
				{
					delete m_EnemyArrayPtr[index];
					m_EnemyArrayPtr[index] = nullptr;
					m_HUDPtr->AddToEnemyScore(100);
				}
			}	
		}

		// Als Charlie de sterfanimatie uitvoert mag er niets meer gebeuren
		if (m_CharliePtr->ReturnState() != 4) // Als Charlie niet dood is (4 = STATE_DYING), uitvoeren
		{ // Open if state
			
			for (int index = 0 ; index < MAX_ENEMIES ; index ++)
			{
				if (m_EnemyArrayPtr[index] != nullptr) // Alle enemies checken of ze nog bestaan
				{
					m_EnemyArrayPtr[index]->Tick(deltaTime, m_CharliePtr->GetVerticalHitregion(),m_CharliePtr->GetHorizontalHitregion());
					// De enemy laten ticken (verplaatsing & collision (= ->Bounce() & -> EnemyHit())
					if (m_EnemyArrayPtr[index]->Bounce())
					{
						// Als de enemy bovenaan geraakt word door Charlie (->Bounce() == true)
						// -> Charlie gaat omhoog springen
						m_CharliePtr->Bounce(DOUBLE2(0,-300));
					}

					if (m_EnemyArrayPtr[index]->EnemyHit() && m_CharliePtr->GetIsInvincible() == false)
					{
						// Als de enemy aan de zijkant geraakt word door Charlie (->EnemyHit() == true), en
						// Charlie geraakt kan worden (!= invincible)
						m_CharliePtr->SetIsInvincible(true); // Charlie word invincible,						
						Charlie::m_Hearts--; // en verliest een hartje
				
						if (Charlie::m_Hearts < 0) // Als Charlie minder als 0 hartjes heeft,
						{
						m_CharliePtr->SetState(4); // word zijn state op 4 gezet (STATE_DYING, en valt hij naar beneden)
						}
					}
				}
			}
	
		} // Sluiten if state

		if (Charlie::m_Hearts < 0 && m_CharliePtr->GetPosition().y >= GAME_ENGINE->GetHeight())
		// Als Charlie minder als 0 hartjes heeft & hij onder het scherm gevallen is,
		{	
			Charlie::m_Life--; // -> Word er een leven afgetrokken,
			Reset(); // word alles terug gereset,
			Charlie::m_Hearts = 3; // krijgt Charlie terug 3 hartjes,
			m_CharliePtr->SetState(0); // & zijn state komt terug op 0 (STATE_WAITING)
		}
		

		// Woordje uitleg voor mezelf:
		// In tick van gebeurt collision, dus hitregions van Charlie worden meegegeven,
		// EnemyHiy is voor als Charlie horizontaal geraakt word en damage moet krijgen, 
		// Bounce voor als er verticaal geraakt word en moet bounce'n
 		// Gebeurt in de main omdat de m_CharliePtr niet opgeroepen kan worden in de EnemyList


		// ----- Itemlist -----

		// Als Charlie de sterfanimatie uitvoert mag er niets meer gebeuren
		if (m_CharliePtr->ReturnState() != 4) // Als Charlie niet dood is (4 = STATE_DYING), uitvoeren
		{
			m_ArrayOfItemsPtr->Tick(m_CharliePtr->GetVerticalHitregion(),m_CharliePtr->GetHorizontalHitregion()); // Items ticken
		}
		

		// ----- Items in boxes -----

		// Als Charlie de sterfanimatie uitvoert mag er niets meer gebeuren
		if (m_CharliePtr->ReturnState() != 4) // Als Charlie niet dood is (4 = STATE_DYING), uitvoeren
		{ // Open if state 

			for (int index = 0; index < NUMBER_OF_BOXES ; index++)
			{ // For open
			
				if (m_BoxArrayPtr[index] != nullptr) 
				{
					m_BoxArrayPtr[index]->Tick(m_CharliePtr->GetVerticalHitregion(),deltaTime);
					// ItemId = de index van de itemlist, geeft id 3 mee
					if (m_ArrayOfItemsPtr->ItemExists(m_BoxArrayPtr[index]->ReturnItemID())) // Als het item dat in de box zit nog bestaat (!= nullptr wordt gechecked in ItemExists)
					{
						if(m_BoxArrayPtr[index]->IsBoxBroken() && m_ArrayOfItemsPtr->IsItemInBox(m_BoxArrayPtr[index]->ReturnItemID())) 
						// Kijken of de box gebroken is en het item die gelinkt is met de box niet getoond word (nog altijd in de box zit, IsItemInBox geeft true of false terug)
						{
							m_CharliePtr->Bounce(DOUBLE2(0,-300));
							m_ArrayOfItemsPtr->SetItemDisplayed(m_BoxArrayPtr[index]->ReturnItemID());	
							// -> Charlie springt omhoog & het item word zichtbaar
						}
					}
				}
			
				if(m_BoxArrayPtr[index] != nullptr) // Als de box nog bestaat,
				{
					if(m_BoxArrayPtr[index]->IsBoxGone()) // kijken of de box al uit het scherm is (blokjes animatie volledig gevallen).
					{
						delete m_BoxArrayPtr[index];
						m_BoxArrayPtr[index] = nullptr;
						// -> Verwijderen van de box & op nullptr zetten.
					}
				}

			} // For sluiten 

		} // Sluiten if state 
		

		// ----- Bouncing boxes -----
		
		// Als Charlie de sterfanimatie uitvoert mag er niets meer gebeuren
		if (m_CharliePtr->ReturnState() != 4) // Als Charlie niet dood is (4 = STATE_DYING), uitvoeren
		{ // Open if state

			m_BouncingBoxPtr->Tick(m_CharliePtr->GetVerticalHitregion()); // Bouncing boxes ticken
			m_BouncingBox2Ptr->Tick(m_CharliePtr->GetVerticalHitregion());
	
			if (m_BouncingBoxPtr->Bounce())
			{
				m_CharliePtr->Bounce(DOUBLE2(0,-450)); // -> Charlie bounces
			}
			if (m_BouncingBox2Ptr->Bounce())
			{
				m_CharliePtr->Bounce(DOUBLE2(0,-450)); // -> Charlie bounces
			}

		} // Sluiten if state


		// ----- HUD -----

		m_HUDPtr->Tick(); // HUD ticken

	} // Einde grote if	
		
}

void CharlieTheDuck::GamePaint(RECT rect)
{
	
	if (!m_IsGameStarted)
	// Wanneer er nog niet op de click area van het startscherm geklikt is,
	// word het startscherm getekend
	{ 
		GAME_ENGINE->DrawBitmap(m_BmpStartSchermPtr,0,0);
	}
	else // Bool m_IsGameStarted is true en tick mag uitgevoerd worden.
	{ // Start grote else
		
		// ----- Level layout -----

		GAME_ENGINE->DrawSolidBackground(69,95,157); // Blauwe achtergrond (lucht) painten

		// View matrix aanmaken
		MATRIX3X2 matView;
		matView.SetAsTranslate(m_PositionCamera);
		matView = matView.Inverse();

		GAME_ENGINE->SetTransformMatrix(matView);

		// Level painten
		GAME_ENGINE->DrawBitmap(m_BmpLevelPtr, 0,0);

		// Hitregion level
		// GAME_ENGINE->SetColor(COLOR(255,0,0,170));
		// GAME_ENGINE->FillHitRegion(m_HitLevelPtr);
		// GAME_ENGINE->SetColor(COLOR(0,0,0));

		// Wolkjes
		// Matrix maken zodat de wolkjes meegaan met het scherm
		MATRIX3X2 matViewCloud;
		matViewCloud.SetAsTranslate(m_CloudPosition);
		matViewCloud = matViewCloud.Inverse();
	
		GAME_ENGINE->SetTransformMatrix(matViewCloud);
		
		// RECT maken voor de wolkjes
		RECT clipCloud; 
		clipCloud.left = (m_BmpCloudPtr->GetWidth() / 2) * m_CloudAnimationStep;
		clipCloud.right = clipCloud.left + m_BmpCloudPtr->GetWidth() / 2 ;
		clipCloud.bottom = 0;
		clipCloud.top = m_BmpCloudPtr->GetHeight();
		
		// Wolkjes painten
		GAME_ENGINE->DrawBitmap(m_BmpCloudPtr, m_CloudPosition.x + 100, 100, clipCloud);
		GAME_ENGINE->DrawBitmap(m_BmpCloudPtr, m_CloudPosition.x + 340, 100, clipCloud);
		GAME_ENGINE->DrawBitmap(m_BmpCloudPtr,m_CloudPosition.x + 220, 120, clipCloud);
		GAME_ENGINE->DrawBitmap(m_BmpCloudPtr,m_CloudPosition.x + 460, 120, clipCloud);

		// Normale view matrix terug aanroepen
		GAME_ENGINE->SetTransformMatrix(matView);

		// Charlie painten, vóór het water, anders zwemt hij ervoor
		m_CharliePtr->Paint(matView);

		// RECT maken voor water
		RECT waterClip;
		waterClip.left = (m_BmpWaterPtr->GetWidth() / 5) * m_WaterAnimationStep;
		waterClip.right = waterClip.left + m_BmpWaterPtr->GetWidth() / 6 ;
		waterClip.bottom = 0;
		waterClip.top = m_BmpWaterPtr->GetHeight();

		// Water painten
		GAME_ENGINE->DrawBitmap(m_BmpWaterPtr, 1277, 531, waterClip);
		GAME_ENGINE->DrawBitmap(m_BmpWaterPtr, 2634, 531, waterClip);
		GAME_ENGINE->DrawBitmap(m_BmpWaterPtr, 2634 + (m_BmpWaterPtr->GetWidth() / 9), 531, waterClip);
		GAME_ENGINE->DrawBitmap(m_BmpWaterPtr, 4070,531, waterClip);
		GAME_ENGINE->DrawBitmap(m_BmpWaterPtr, 4310, 531, waterClip);
		
		// Hitregions water
		// GAME_ENGINE->SetColor(COLOR(255,0,0,170));
		// GAME_ENGINE->FillHitRegion(m_HitWaterPtr); 
		// GAME_ENGINE->SetColor(COLOR(0,0,0));

	
		// ----- Enemies -----
		for (int index = 0 ; index < MAX_ENEMIES ; index++) // Enemy array overlopen en invullen
		{
			if (m_EnemyArrayPtr[index] != nullptr) // Als enemy bestaat,
			{
				m_EnemyArrayPtr[index]->Paint(matView); // painten
			}
		}

		GAME_ENGINE->SetTransformMatrix(matView);
		// ----- Items -----		
		m_ArrayOfItemsPtr->Paint(matView);


		// ----- Bouncing boxes
		m_BouncingBoxPtr->Paint(matView);
		m_BouncingBox2Ptr->Paint(matView);
	

		// ----- Boxes -----
		for (int index = 0 ; index < NUMBER_OF_BOXES ; index++) // Array overlopen en invullen
		{
			if (m_BoxArrayPtr[index] != nullptr) // Als box bestaat,
			{
				m_BoxArrayPtr[index]->Paint(matView); // painten
			}
		}
				
		// ----- HUD -----
		m_HUDPtr->Paint();

		m_HUDPtr->GameOver(m_CharliePtr->GetIsCharlieDead()); // Game over screen painten	

		// ----- End level sign -----
		m_EndLevelSignPtr->Paint(matView);

		// Als Charlie voorbij een bepaalde positie is aan het einde van het level moet het spel sluiten
		if (m_CharliePtr->GetPosition().x > m_BmpLevelPtr->GetWidth()-10)
		{
			GAME_ENGINE->QuitGame();
		}

	} // Einde grote else

}

//void CharlieTheDuck::CallAction(Caller* callerPtr)
//{
//}

void CharlieTheDuck::Reset() // Reset method voor als Charlie dood is
{
	
	m_CharliePtr->SetPos(DOUBLE2(316,100)); // Charlie terug op oorspronkelijke positie zetten
	
	m_PositionCamera = DOUBLE2(0,0); // Camera terug in het begin zetten

	int tempCoins = Coin::m_AmountPickedUp; // Zorgen dat de coins en diamond die al opgepikt zijn bijgehouden worden
	int tempDiamonds = Diamond::m_AmountPickedUp;

	delete m_ArrayOfItemsPtr; // Itemlist verwijderen, 
	m_ArrayOfItemsPtr = nullptr; // op nullptr zetten.

	m_ArrayOfItemsPtr = new ItemList(); // en opnieuw aanmaken

	Heart::m_AmountPickedUp = 0;
	Coin::m_AmountPickedUp = tempCoins;
	Diamond:: m_AmountPickedUp = tempDiamonds;
	
	//delete m_EnemyListPtr;
	//m_EnemyListPtr = nullptr;
	//m_EnemyListPtr = new EnemyList();

	m_EnemyListPtr->MakeEnemies();

	for (int index = 0 ; index < MAX_ENEMIES ; index++)
	{
		m_EnemyArrayPtr[index] = m_EnemyListPtr->GetArrayOfEnemies(index);
	}

}



