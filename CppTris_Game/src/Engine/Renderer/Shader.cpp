#include "Shader.h"

#include "Engine/Log.h"

#include "glad/glad.h"

#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_ShaderID(0)
{
	ShaderProgramSource source = parseShader(filepath);
	m_ShaderID = createShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GL_CALL(glDeleteProgram(m_ShaderID));
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GL_CALL(glAttachShader(program, vs));
	GL_CALL(glAttachShader(program, fs));
	GL_CALL(glLinkProgram(program));
	GL_CALL(glValidateProgram(program));

	GL_CALL(glDeleteShader(vs));
	GL_CALL(glDeleteShader(fs));

	return program;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	GL_CALL(glShaderSource(id, 1, &src, nullptr));
	GL_CALL(glCompileShader(id));

	int result;
	GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GL_CALL(glGetShaderInfoLog(id, length, &length, message));

		DEBUG_LOG_ERROR("Failed to compile shader: %s", message);
		return 0;
	}

	return id;
}

//retrieve the vertex source code and fragment source code from the file
ShaderProgramSource Shader::parseShader(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {	//Getting a line from the stream and storing it in the line variable
		if (line.find("#shader") != std::string::npos) {	//std::string::npos is the equivalent of -1 (used to check for matches)
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

void Shader::bind() const
{
	GL_CALL(glUseProgram(m_ShaderID));
}

void Shader::unbind() const
{
	GL_CALL(glUseProgram(0));
}

void Shader::setUniform1i(const std::string& name, int i)
{
	bind();
	GL_CALL(glUniform1i(getUniformLocation(name), i));
	unbind();
}

void Shader::setUniform1f(const std::string& name, float f)
{
	bind();
	GL_CALL(glUniform1f(getUniformLocation(name), f));
	unbind();
}

void Shader::setUniform3f(const std::string& name, float f0, float f1, float f2) {
	bind();
	GL_CALL(glUniform3f(getUniformLocation(name), f0, f1, f2));
	unbind();
}

void Shader::setUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
	bind();
	GL_CALL(glUniform4f(getUniformLocation(name), f0, f1, f2, f3));
	unbind();
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& mat4)
{
	bind();
	GL_CALL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat4[0][0]));
	unbind();
}

int Shader::getUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
		return m_UniformLocationCache[name];
	}

	GL_CALL(int location = glGetUniformLocation(m_ShaderID, name.c_str()));
	if (location == -1) {
		DEBUG_LOG_ERROR("Uniform %s does not exist.", name);
	}
	return location;
}
