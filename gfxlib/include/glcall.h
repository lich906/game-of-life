#pragma once

#ifndef GLCALL_H
#define GLCALL_H

#include <iostream>

#include "common.h"

#if _DEBUG

	#define GlCall(x) GlClearError(); \
		x; \
		if (!GlLogCall(#x, __FILE__, __LINE__)) \
			__debugbreak()

	static void GlClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	static std::string GlGetErrorName(GLenum errorCode)
	{
		switch (errorCode)
		{
		case GL_INVALID_ENUM:
			return "GL_INVALID_ENUM";
		case GL_INVALID_VALUE:
			return "GL_INVALID_VALUE";
		case GL_INVALID_OPERATION:
			return "GL_INVALID_OPERATION";
		case GL_STACK_OVERFLOW:
			return "GL_STACK_OVERFLOW";
		case GL_STACK_UNDERFLOW:
			return "GL_STACK_UNDERFLOW";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return "GL_INVALID_FRAMEBUFFER_OPERATION";
		case GL_OUT_OF_MEMORY:
			return "GL_OUT_OF_MEMORY";
		default:
			return "unknown";
		}
	}

	static bool GlLogCall(const char* function, const char* file, int line)
	{
		while (GLenum errCode = glGetError())
		{
			std::cout << "[OpenGL Error] (" << GlGetErrorName(errCode) << "): "
				<< function << " " << file << ":" << line << std::endl;
			return false;
		}
		return true;
	}

#else

	#define GlCall(x) x

#endif

#endif // !GLCALL_H
