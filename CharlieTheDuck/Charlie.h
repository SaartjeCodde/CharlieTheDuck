#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Charlie Class									
//-----------------------------------------------------
class Charlie
{
public:
	Charlie();				// Constructor
	virtual ~Charlie();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	void Tick(double deltaTime, HitRegion* hitLevelPtr, HitRegion* hitWaterPtr);
	void Paint(MATRIX3X2 matView);
	void HorizontalLevelCollision();
	void VerticalLevelCollision();
	void WaterCollision();
	void Bounce(DOUBLE2 velocity);
	void SetCameraState(bool state);
	void SetIsInvincible(bool isInvincible);

	void SetState(int state);

	int ReturnState();

	static int ReturnAmountOfLives();
	static int ReturnAmountOfHearts();

	DOUBLE2 GetPosition();
				
	HitRegion *GetVerticalHitregion();
	HitRegion *GetHorizontalHitregion();
	 
	bool GetCameraState();	
	bool GetIsInvincible();

	bool GetIsCharlieDead();

	void SetPos(DOUBLE2 position);

	static int m_Hearts;
	static int m_Life;

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	
	static Audio* m_JumpPtr;

	static Bitmap* m_BmpCharlieSpriteSheetPtr;
	static Bitmap* m_BmpCharlieInvincibleSpriteSheetPtr;

	static const int STATE_WAITING = 0; 
	static const int STATE_WALKING = 1; 
	static const int STATE_JUMPING = 2; 
	static const int STATE_SWIMMING = 3;
	static const int STATE_DYING = 4;
	static const int CHARLIE_WIDTH = 50;
	static const int CHARLIE_HEIGHT = 67;
	
	int m_TickCount;
	int m_TickCounterForCorrectAnimation; // Second tickcounter to slow Charlie's animations
	int m_CurrentAnimationStep;
	int m_CurrentState;
	int m_X;
	int m_Y;
	
	DOUBLE2 m_Position;
	DOUBLE2 m_Velocity;
	DOUBLE2 m_Gravity;
	
	double m_Seconds;

	HitRegion *m_HitCharlieHorizontalPtr;
	HitRegion *m_HitCharlieVerticalPtr;
	HitRegion *m_HitLevelPtr;
	HitRegion *m_HitWaterPtr;
	
	bool m_IsCameraEnabled;
	bool m_IsSwimming;
	bool m_IsOutOfWater; 
	bool m_IsInvincible;
	bool m_IsFlipped;
	bool m_CharlieDead;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Charlie(const Charlie& yRef);									
	Charlie& operator=(const Charlie& yRef);	
};

 
