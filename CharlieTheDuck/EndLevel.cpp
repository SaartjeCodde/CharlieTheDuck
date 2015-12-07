//---------------------------
// Includes
//---------------------------
#include "EndLevel.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
EndLevel::EndLevel(DOUBLE2 position): m_Position(position), m_CurrentState(0),m_CurrentAnimationStep(0),m_TickCount(0)
{
	m_BmpEndLevelSignPtr = new Bitmap("./resources/End Level.bmp");
	m_BmpEndLevelSignPtr->SetTransparencyColor(255,0,255);
	
}

EndLevel::~EndLevel()
{
	// nothing to destroy
}

//---------------------------
// Own methods
//---------------------------

// add your own methods here.


void EndLevel::Tick(double positionCharlie)
{


	if(positionCharlie >= m_Position.x)
	{
		m_CurrentState = TURNING;
	}

	m_TickCount++;

	if (m_TickCount >= 3 && m_CurrentState == TURNING)
	{
		m_CurrentAnimationStep = ++m_CurrentAnimationStep % 9;
		m_TickCount = 0;
	}

}

void EndLevel::Paint(MATRIX3X2 matView)
{
	RECT2 clip;
	switch (m_CurrentState)

	{
	case NOT_TURNING:
	{
		clip.left = m_BmpEndLevelSignPtr->GetWidth()/9;
		clip.right = clip.left + m_BmpEndLevelSignPtr->GetWidth()/9;
		clip.top = 0;
		clip.bottom = m_BmpEndLevelSignPtr->GetHeight();
		break;
	}
	
	case TURNING:
	{
		clip.left = (m_BmpEndLevelSignPtr->GetWidth()/9) * m_CurrentAnimationStep;
		clip.right = clip.left + m_BmpEndLevelSignPtr->GetWidth()/9;
		clip.top = 0;
		clip.bottom = m_BmpEndLevelSignPtr->GetHeight();
		break;
	}
	}

	GAME_ENGINE->SetTransformMatrix(matView);
	GAME_ENGINE->DrawBitmap(m_BmpEndLevelSignPtr, m_Position, clip);

}