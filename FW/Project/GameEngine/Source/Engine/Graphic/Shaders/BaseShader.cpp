//--------------------------------------------------
// File:    BaseShader.cpp
// Created: 16/03/2013 15:01:27
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "BaseShader.h" 

#include "Graphic/Camera/Camera.h"

CGLConstantBuffer<cbViewCommon> CBaseShader::m_CbViewCommon;
CGLConstantBuffer<cbSceneCommon> CBaseShader::m_CbSceneCommon;

CBaseShader::CBaseShader()
{
	m_CbViewCommon.InputSlot(0);
	m_CbSceneCommon.InputSlot(1);
}

void CBaseShader::SetViewCommonData( const CBaseCamera& camera )
{
	cbViewCommon cb0;

	cb0.ViewXf			= camera.View();
	cb0.ViewIXf			= camera.ViewInverse();
	cb0.ProjectionXf	= camera.Projection();
	cb0.ProjectionIXf	= glm::inverse(camera.Projection());

	m_CbViewCommon.SetData(cb0);
}

void CBaseShader::SetSceneCommon(const CTimer& timer)
{
	cbSceneCommon cb;

	cb.GameTimerData = glm::vec4(timer.GetElapsedTime(), timer.GetFrameTime(), 0, 0);

	m_CbSceneCommon.SetData(cb);
}

// eof /////////////////////////////////////////////
