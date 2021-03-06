//--------------------------------------------------
// File:    GLTechnique.h
// Created: 01/12/2013 14:50:59
//
// Description: $
//

//--------------------------------------------------

#ifndef _GLTECHNIQUE_H__2013_12_01_14_50_59
#define _GLTECHNIQUE_H__2013_12_01_14_50_59

#pragma once

#ifdef SHOW_HEADERS
#pragma message(" < "__FILE__)
#endif // SHOW_HEADERS

// includes ////////////////////////////////////////
#include "Core/Core.h"
#include "Resource/Resource.h"
#include "RenderDevice/GLRenderer/GLDefines.h"
#include "RenderDevice/GLRenderer/Buffer/GLVertexInputLayout.h"

// type declarations (enum struct class) //////////
class CGLCommonGpuProgram
{
public:
	CGLCommonGpuProgram();
	virtual ~CGLCommonGpuProgram();

	static GLint	ShaderType(const Renderer::ShaderType t);

	virtual GLint	ShaderType()=0;
	virtual void	Apply()=0;

	bool			Compile(const string& src);
	bool			Compile(const fs::path & fn);

	GLuint			ShaderProgramHandle() const			{ return m_ShaderProgramHandle; }
	const string&	Error() const						{ return m_ErrorString; }
private:
	GLuint			m_ShaderProgramHandle;
	string			m_ErrorString;
	
};

class CGLVertexShader : public CGLCommonGpuProgram 
{
public:
	virtual GLint	ShaderType()	{ return GL_VERTEX_SHADER; }
	virtual void	Apply()			{};

	void SetInputLayoutDesc(const CGLVertexInputLayout& ia_desc) { m_InputLayoutDesc = ia_desc; };
	CGLVertexInputLayout& InputLayout() { return m_InputLayoutDesc; }
private:
	CGLVertexInputLayout			m_InputLayoutDesc;
};

class CGLGeometryShader : public CGLCommonGpuProgram
{
public:
	virtual GLint	ShaderType()	{ return GL_GEOMETRY_SHADER; }
	virtual void	Apply()			{};

private:
};

class CGLPixelShader : public CGLCommonGpuProgram 
{
public:
	virtual GLint	ShaderType()	{ return GL_FRAGMENT_SHADER; }
	virtual void	Apply()			{};

private:
};

class CGLComputeShader : public CGLCommonGpuProgram
{
public:
	virtual GLint	ShaderType()	{ return GL_COMPUTE_SHADER; }
	virtual void	Apply()			{};
};

class CGLTechniqueCommon
{
public:
	CGLTechniqueCommon()
		: m_TechniqueHandle(0)
	{ }

	virtual void			Apply() = 0;

	const string&			GetName() const { return m_Name; }
	void					SetName(const string& val) { m_Name = val; }

	static CGLCommonGpuProgram*	CreateAndCompile(Renderer::ShaderType t, const string& source);
protected:
	bool					LinkShaders(CGLCommonGpuProgram** shaders, uint32_t num_elems);

	string					m_Name;
	GLuint					m_TechniqueHandle;
};

class CGLRenderTechnique : public CGLTechniqueCommon
{
public:
	CGLRenderTechnique()
	{
		m_Shaders.assign(nullptr);
	}

	bool					Load(const CResourceObject& resource_obj);
	virtual void			Apply();

	template<class T> 
	T*						GetShader(Renderer::ShaderType type) { return static_cast<T*>(m_Shaders[type]); }	
private:
	array<CGLCommonGpuProgram*, 5>	m_Shaders;
};

class CGLComputeTechnique : public CGLTechniqueCommon
{
public:
	CGLComputeTechnique()
	{
		m_Shaders.assign(nullptr);
	}

	bool					Load(const CResourceObject& resource_obj);
	virtual void			Apply();
private:
	array<CGLCommonGpuProgram*, 1>	m_Shaders;
};


// inline file ///////////


// eof /////////////////////////////////////////////

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _GLTECHNIQUE_H__2013_12_01_14_50_59