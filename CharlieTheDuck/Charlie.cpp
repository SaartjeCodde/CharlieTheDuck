//---------------------------
// Includes
//---------------------------
#include "Charlie.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

Bitmap* Charlie::m_BmpCharlieSpriteSheetPtr = nullptr;
Bitmap* Charlie::m_BmpCharlieInvincibleSpriteSheetPtr = nullptr;
Audio* Charlie::m_JumpPtr = nullptr;

int Charlie::m_Life = 0;
int Charlie::m_Hearts = 0;
//---------------------------
// Constructor & Destructor
//---------------------------
Charlie::Charlie():
		
		m_TickCount(0),
		m_TickCounterForCorrectAnimation(0),
		m_CurrentAnimationStep(0),
		m_CurrentState(0),
		m_X(0),
		m_Y(0),
		m_Position(316,50),
		m_Velocity(200,0),
		m_Gravity(0,500),
	
		m_HitCharlieHorizontalPtr(nullptr),
		m_HitCharlieVerticalPtr(nullptr),
		m_HitLevelPtr(nullptr),
		m_HitWaterPtr(nullptr),
	
		m_IsCameraEnabled(true),
		m_IsSwimming(false),
		m_IsOutOfWater(false),
		m_IsInvincible(false),
		m_IsFlipped(false),
		m_CharlieDead(false),
		
		m_Seconds(0)
		
{
	
	if (m_BmpCharlieSpriteSheetPtr == nullptr)
	{
		m_BmpCharlieSpriteSheetPtr = new Bitmap("./resources/Charlie.bmp");
		m_BmpCharlieSpriteSheetPtr->SetTransparencyColor(255,0,255);
	}

	if (m_BmpCharlieInvincibleSpriteSheetPtr == nullptr)
	{
		m_BmpCharlieInvincibleSpriteSheetPtr = new Bitmap("./resources/CharlieInvincible.png");
		m_BmpCharlieInvincibleSpriteSheetPtr->SetTransparencyColor(255,0,255);
	}

	m_HitCharlieHorizontalPtr = new HitRegion();
	m_HitCharlieHorizontalPtr->CreateFromRect(0, 10, CHARLIE_WIDTH, CHARLIE_HEIGHT - 10);
	
	m_HitCharlieVerticalPtr = new HitRegion();
	m_HitCharlieVerticalPtr->CreateFromRect((CHARLIE_WIDTH / 4) + 5, CHARLIE_HEIGHT -20, (CHARLIE_WIDTH / 4) + 15, CHARLIE_HEIGHT);

	m_Life = 3;
	m_Hearts = 3;

	if (m_JumpPtr == nullptr)
	{
		m_JumpPtr = new Audio("./resources/Sounds/Jump.mp3");
	}

}

Charlie::~Charlie()
{
	
	delete m_HitCharlieHorizontalPtr;
	delete m_HitCharlieVerticalPtr;
	delete m_HitLevelPtr;
	delete m_HitWaterPtr;

}

//---------------------------
// Own methods
//---------------------------

void Charlie::Tick(double deltaTime, HitRegion* hitLevelPtr, HitRegion* hitWaterPtr)
{
	
	if (m_CurrentState != STATE_DYING) 
	{ // Open grote if state
		m_JumpPtr->Tick();

		m_HitLevelPtr = hitLevelPtr;
		m_HitWaterPtr = hitWaterPtr;

		m_Velocity.x = 0;

		// Knoppen instellen
		if (GAME_ENGINE->IsKeyDown(VK_LEFT))
		{
			m_Velocity.x = -200;
			m_IsFlipped = true;
		}

		if (GAME_ENGINE->IsKeyDown(VK_RIGHT))
		{
			m_Velocity.x = 200;
			m_IsFlipped = false;
		}
	
		if (GAME_ENGINE->IsKeyDown(VK_SPACE) && m_Velocity.y == 0)
		{
			m_Velocity.y = -400;
			m_JumpPtr->Play();
		}
	
		m_Velocity += m_Gravity * deltaTime; // Gravity implementeren
		m_Position += m_Velocity * deltaTime; // Positie aanpassen

		// HitRegions laten meegaan met Charlie
		m_HitCharlieHorizontalPtr->SetPos(m_Position);
		m_HitCharlieVerticalPtr->SetPos(m_Position);

		// Collisions
		if (m_CurrentState !=4)
		{
			HorizontalLevelCollision();
			VerticalLevelCollision();

			if (m_IsOutOfWater == false)
			{
				WaterCollision();
			}	
			// Woordje uitleg voor mezelf:
			// De m_IsOutOfWater bool is een test bool om het probleem van uit het water springen te omzeilen,
			// als Charlie in het water zat en hij sprong eruit gebeurde de collision in feite nog is en was de m_IsSwimming nog steeds true,
			// waardoor hij eenmaal terug op het land nog altijd in de zwem clip zat.

			if (m_IsSwimming == true && m_Position.y >= 480) 
			{
				m_Position.y = 480; // Charlie blijft drijven op deze positie
				m_Velocity.y = 0;
			}
		}

		// HitRegions laten meegaan met Charlie
		m_HitCharlieVerticalPtr->SetPos(m_Position);
		m_HitCharlieHorizontalPtr->SetPos(m_Position);

	} // Sluiten grote if state

	++m_TickCount;

	// Switchen tussen states
	switch(m_CurrentState)
	{
	case STATE_WAITING:
		if (GAME_ENGINE->IsKeyDown(VK_RIGHT)  && m_Velocity.y == 0) 
		// Velocity word hier bijgeplaats om het probleem te verhelpen dat Charlie ook de walking clip deed wanneer er terwijl hij in de lucht was (sprong) op het rechterpijltje werd gedrukt. 
		{
			m_CurrentState = STATE_WALKING;
		}

		if (GAME_ENGINE->IsKeyDown(VK_LEFT) && m_Velocity.y == 0) 
		// Velocity word hier bijgeplaats om het probleem te verhelpen dat Charlie ook de walking clip deed wanneer er terwijl hij in de lucht was (sprong) op het rechterpijltje werd gedrukt. 
		{
			m_CurrentState = STATE_WALKING;
		}

		if (GAME_ENGINE->IsKeyDown(VK_SPACE))
		{
			m_CurrentState = STATE_JUMPING;
			m_IsSwimming = false; 
			// De m_IsSwimming word hier op false gezet omdat als Charlie in het water zat en hij sprong eruit, de collision in feite nog is gebeurde.
			// Hierdoor bleef de m_IsSwimming true alsook de bijhorende clip.
			// Analoog hiermee ook de verklaring voor m_IsSwimming in onderstaande code.
		}

		if (m_IsSwimming == true)
		{
			m_CurrentState = STATE_SWIMMING;
		}

		m_TickCount = 0;
		break;
	
	case STATE_WALKING:
		if (!GAME_ENGINE->IsKeyDown(VK_RIGHT) || m_Velocity.y < 0)
		{
			m_CurrentState = STATE_WAITING;
		}
		if (m_TickCount == 2)
		{
			m_TickCount = 0;
		}

		if (m_IsSwimming == true)
		{
			m_CurrentState = STATE_SWIMMING;
		}

		m_IsOutOfWater = false;
		break;

	case STATE_JUMPING:
		if (m_Velocity.y == 0)
		{
			m_CurrentState = STATE_WAITING;
		}

		if (m_Position.y <= 400)
		{
			m_IsOutOfWater = false;
		}
		break;

	case STATE_SWIMMING:
		{
			if (m_Velocity.y < 0)
			{
				m_IsSwimming = false;
			}
			if (m_IsSwimming == false)
			{
				m_CurrentState = STATE_WAITING;
			}
			break;
		}
	
	}

	// Charlie's animatie vertragen
	m_TickCounterForCorrectAnimation++;
	if (m_TickCounterForCorrectAnimation % 10 == 0)
	{
		m_CurrentAnimationStep = ++m_CurrentAnimationStep % 2; 
	}
	
	if(m_IsInvincible)
	{
	m_Seconds += deltaTime;

	if(m_Seconds >= 2)
	{
		m_Seconds = 0;
		m_IsInvincible = false;
	}

	}

	if (m_CurrentState == STATE_DYING)
	{
		m_Position.y += 6; // Charlie valt naar beneden
		m_HitCharlieHorizontalPtr->SetPos(m_Position);
		m_HitCharlieVerticalPtr->SetPos(m_Position);
	}

}

void Charlie::Paint(MATRIX3X2 matView)
{ 
	
	// Matrices
	MATRIX3X2 transformCharlie;
	transformCharlie.SetAsTranslate(m_Position);

	// Flip
	int offset;
	offset = m_BmpCharlieInvincibleSpriteSheetPtr->GetWidth() / 6;
	MATRIX3X2 scaleCharlie;

	if (m_IsFlipped)
	{
		scaleCharlie.SetAsScale(-1,1);
	}
	else
	{
		scaleCharlie.SetAsScale(1,1);
	}

	 GAME_ENGINE->SetTransformMatrix(scaleCharlie * transformCharlie * matView);
	
	// Determine clips
	RECT clip;

	switch (m_CurrentState) // Switch tussen cases
	{
	case STATE_WAITING:
		{
			//RECT clip;
			clip.left = 0;
			clip.right = CHARLIE_WIDTH;
			clip.top = 0;
			clip.bottom = CHARLIE_HEIGHT;

			//GAME_ENGINE->DrawBitmap(m_BmpCharlieSpriteSheetPtr, m_X, m_Y, clip);
			break;
		}

	case STATE_WALKING:
		{			
			//RECT clip;
			clip.left = CHARLIE_WIDTH * (m_CurrentAnimationStep);
			clip.right = clip.left + CHARLIE_WIDTH;
			clip.top = 0;
			clip.bottom = CHARLIE_HEIGHT;

			//GAME_ENGINE->DrawBitmap(m_BmpCharlieSpriteSheetPtr, m_X, m_Y, clip);
			break;
		}
	
	case STATE_JUMPING:
		{
			//RECT clip;
			clip.left = CHARLIE_WIDTH * 3;
			clip.right = clip.left + CHARLIE_WIDTH;
			clip.top = 0;
			clip.bottom = CHARLIE_HEIGHT;
			
			//GAME_ENGINE->DrawBitmap(m_BmpCharlieSpriteSheetPtr, m_X, m_Y, clip);
			break;	
		}

	case STATE_SWIMMING:
		{
			//RECT clip;
			clip.left = CHARLIE_WIDTH * 4;
			clip.right = clip.left + CHARLIE_WIDTH;
			clip.top = 0;
			clip.bottom = CHARLIE_HEIGHT;
			
			//GAME_ENGINE->DrawBitmap(m_BmpCharlieSpriteSheetPtr, m_X, m_Y, clip);
			break;
		}

	case STATE_DYING:
		{
			clip.left = CHARLIE_WIDTH * 5;
			clip.right = clip.left + CHARLIE_WIDTH;
			clip.top = 0;
			clip.bottom = CHARLIE_HEIGHT;
		}

	}

	if (!m_IsInvincible && !m_IsFlipped) 
	{
		GAME_ENGINE->DrawBitmap(m_BmpCharlieSpriteSheetPtr, m_X, m_Y, clip);
	}
	else if (m_IsInvincible && !m_IsFlipped) 
	{
		GAME_ENGINE->DrawBitmap(m_BmpCharlieInvincibleSpriteSheetPtr, m_X, m_Y, clip);
	}
	else if (!m_IsInvincible && m_IsFlipped) 
	{
		GAME_ENGINE->DrawBitmap(m_BmpCharlieSpriteSheetPtr, m_X - offset , m_Y, clip);
	}
	else if (m_IsInvincible && m_IsFlipped) 
	{
		GAME_ENGINE->DrawBitmap(m_BmpCharlieInvincibleSpriteSheetPtr, m_X - offset, m_Y, clip);
	}

	GAME_ENGINE->SetTransformMatrix(matView);
	
	// Hitregions
	// GAME_ENGINE->SetColor(COLOR(255,0,0,170));
	// GAME_ENGINE->FillHitRegion(m_HitCharlieHorizontalPtr);
	// GAME_ENGINE->FillHitRegion(m_HitCharlieVerticalPtr);
	// GAME_ENGINE->SetColor(COLOR(0,0,0));	

}

DOUBLE2 Charlie::GetPosition()
{
	
	return m_Position;

}

void Charlie::HorizontalLevelCollision() 
{
	
	RECT2 horizontalTest = m_HitCharlieHorizontalPtr->CollisionTest(m_HitLevelPtr);

	if (abs(m_HitCharlieHorizontalPtr->GetBounds().right - horizontalTest.right) < 0.1)
	 {
		  m_Position.x -= horizontalTest.right - horizontalTest.left;
		  m_IsCameraEnabled = false;
	}

	if (abs(m_HitCharlieHorizontalPtr->GetBounds().left - horizontalTest.left) < 0.1  && m_HitCharlieHorizontalPtr->GetBounds().left != 0)
	{
		 m_Position.x += horizontalTest.right - horizontalTest.left;
		 m_IsCameraEnabled = false;
	}
	// Woordje uitleg voor mezelf:
	// De m_IsCameraEnabled word hier op false gezet zodat de camera niet verder gaat in het level als Charlie ergens tegen loopt.

}

void Charlie::VerticalLevelCollision() 
{
	
	RECT2 verticalTest = m_HitCharlieVerticalPtr->CollisionTest(m_HitLevelPtr);

	if (verticalTest.top > 0)
	{
		m_Velocity.y = 0;
		m_Position.y -=  verticalTest.bottom - verticalTest.top;
	}

	verticalTest =  m_HitCharlieHorizontalPtr->CollisionTest(m_HitLevelPtr);

	if (abs(m_HitCharlieVerticalPtr->GetBounds().top - verticalTest.top) < 0.1 )
	{
		m_Velocity.y = 0;
		m_Position.y += verticalTest.bottom - verticalTest.top;
	}
	
}

void Charlie::Bounce(DOUBLE2 velocity)
{
	
	m_Velocity = velocity; // Wordt opgeroepen in de main om Charlie zijn velocity aan te passen als hij op een enemy springt

}

HitRegion* Charlie::GetVerticalHitregion() // Hitregion returnen
{
	
	return m_HitCharlieVerticalPtr;

}

HitRegion* Charlie::GetHorizontalHitregion() // Hitregion returnen
{

	return m_HitCharlieHorizontalPtr; 

}

bool Charlie::GetCameraState()
{
	
	return m_IsCameraEnabled; // Deze word opgeroepen in de main

}

void Charlie::SetCameraState(bool state)
{
	
	m_IsCameraEnabled = state;

}

void Charlie::WaterCollision() // Collision met het water
{

	RECT2 waterTest = m_HitCharlieVerticalPtr->CollisionTest(m_HitWaterPtr);

	if (waterTest.top > 0)
	{
		m_IsSwimming = true;
		m_IsOutOfWater = true;			
	}

}

bool Charlie::GetIsInvincible()
{

	return m_IsInvincible;

}

void Charlie::SetIsInvincible(bool isInvincible)
{

	m_IsInvincible = isInvincible;
	// Word gebruikt in de main om Charlie invincible te zetten als hij geraakt word door een enemy

}

int Charlie::ReturnAmountOfHearts()
{
	
	return m_Hearts;

}

int Charlie::ReturnAmountOfLives()
{
	
	return m_Life;

}

bool Charlie::GetIsCharlieDead()
{
	
	if (m_Life < 0)
	{
		m_CharlieDead = true;
	}
	else
	{ 
		m_CharlieDead = false;
	}
	return m_CharlieDead;
	// Geeft terug of Charlie dood is of niet

}

void Charlie::SetPos(DOUBLE2 position)
{

	m_Position = position;
	m_HitCharlieHorizontalPtr->SetPos(position);
	m_HitCharlieVerticalPtr->SetPos(position);
	// Zet de posities en hitregions van Charlie, wordt gebruikt in de main als Charlie moet respawnen

}

void Charlie::SetState(int state)
{
	
	m_CurrentState = state; // Zet de state van Charlie, wordt gebruikt in de main als Charlie sterft

}

int Charlie::ReturnState()
{
	
	return m_CurrentState; // Returned de state van Charlie

}