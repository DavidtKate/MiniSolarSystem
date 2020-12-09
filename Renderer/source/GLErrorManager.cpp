#include "repch.h"
#include "GLErrorManager.h"

bool GLLogError(const char* a_function, const char* a_file, int a_line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << std::hex << error << std::dec << "): " << a_function <<
			" " << a_file << ":" << a_line << std::endl;
		return false;
	}

	return true;
}