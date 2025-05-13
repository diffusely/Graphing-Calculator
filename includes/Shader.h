#pragma once

#include <string>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader 
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void Use() const;

	void SetFloat(const std::string& name, float value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;
	void SetMat4(const std::string& name, const float* matrix) const;

private:
	GLuint ID;

	std::string ReadFile(const std::string& path) const;
	GLuint CompileShader(GLenum type, const std::string& source);
};