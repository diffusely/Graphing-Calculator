#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
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
	void SetVec3(const std::string& name, const glm::vec3 &value) const;
	void SetMat4(const std::string &name, const glm::mat4 &mat) const;

private:
	GLuint ID;

	std::string ReadFile(const std::string& path) const;
	GLuint CompileShader(GLenum type, const std::string& source);
};