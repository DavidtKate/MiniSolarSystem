#pragma once

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCheckError(x) while (glGetError() != GL_NO_ERROR);\
	x;\
	ASSERT(GLLogError(#x, __FILE__, __LINE__))

bool GLLogError(const char* a_function, const char* a_file, int a_line);