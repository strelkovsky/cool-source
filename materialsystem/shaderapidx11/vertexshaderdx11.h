//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//

#ifndef VERTEXSHADERDX11_H
#define VERTEXSHADERDX11_H

#ifdef _WIN32
#pragma once
#endif

#include "shaderapi/ishaderapi.h"
#include "shaderapidx9/locald3dtypes.h"

enum VertexShaderLightTypes_t
{
	LIGHT_NONE = -1,
	LIGHT_SPOT = 0,
	LIGHT_POINT = 1,
	LIGHT_DIRECTIONAL = 2,
	LIGHT_STATIC = 3,
	LIGHT_AMBIENTCUBE = 4,
};

//-----------------------------------------------------------------------------
// Vertex + pixel shader manager
//-----------------------------------------------------------------------------
abstract_class IShaderManager
{
protected:

	// The current vertex and pixel shader index
	ShaderIndex_t m_nVertexShaderIndex;
	ShaderIndex_t m_nPixelShaderIndex;

public:
	// Initialize, shutdown
	virtual void Init() = 0;
	virtual void Shutdown() = 0;

	// Compiles vertex shaders
	virtual IShaderBuffer *CompileShader( const char *pProgram, size_t nBufLen, const char *pShaderVersion ) = 0;

	// New version of these methods	[dx10 port]
	virtual VertexShaderHandle_t CreateVertexShader( IShaderBuffer* pShaderBuffer ) = 0;
	virtual void DestroyVertexShader( VertexShaderHandle_t hShader ) = 0;
	virtual PixelShaderHandle_t CreatePixelShader( IShaderBuffer* pShaderBuffer ) = 0;
	virtual void DestroyPixelShader( PixelShaderHandle_t hShader ) = 0;

	// Creates vertex, pixel shaders
	virtual VertexShader_t CreateVertexShader( const char *pVertexShaderFile, ShaderIndex_t nStaticVshIndex = 0 ) = 0;
	virtual PixelShader_t CreatePixelShader( const char *pPixelShaderFile, ShaderIndex_t nStaticPshIndex = 0 ) = 0;

	// Sets which dynamic version of the vertex + pixel shader to use
	void SetVertexShaderIndex( ShaderIndex_t vshIndex );
	void SetPixelShaderIndex( ShaderIndex_t pshIndex );

	// Sets the vertex + pixel shader render state
	virtual void SetVertexShader( VertexShader_t shader ) = 0;
	virtual void SetPixelShader( PixelShader_t shader ) = 0;

	// Resets the vertex + pixel shader state
	virtual void ResetShaderState() = 0;

	// Returns the current vertex + pixel shaders
	virtual void *GetCurrentVertexShader() = 0;
	virtual void *GetCurrentPixelShader() = 0;

	virtual void ClearVertexAndPixelShaderRefCounts() = 0;
	virtual void PurgeUnusedVertexAndPixelShaders() = 0;

	// The low-level dx call to set the vertex shader state
	virtual void BindVertexShader( VertexShaderHandle_t shader ) = 0;
	virtual void BindPixelShader( PixelShaderHandle_t shader ) = 0;
};

//-----------------------------------------------------------------------------
//
// Methods related to setting vertex + pixel shader state
//
//-----------------------------------------------------------------------------
FORCEINLINE void IShaderManager::SetVertexShaderIndex( ShaderIndex_t vshIndex )
{
	m_nVertexShaderIndex = vshIndex;
}

FORCEINLINE void IShaderManager::SetPixelShaderIndex( ShaderIndex_t pshIndex )
{
	m_nPixelShaderIndex = pshIndex;
}

extern IShaderManager *g_pShaderManagerDx11;
inline IShaderManager* ShaderManager()
{
	return g_pShaderManagerDx11;
}

#endif // VERTEXSHADERDX11_H
