#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include "../ext/glfw/include/GLFW/glfw3.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

struct ShaderUtils
{

    struct ShaderProgramSource
    {
        std::string vertex;
        std::string fragment;
    };

    enum class ShaderType
    {
        NONE = -1,
        VERTEX,
        FRAGMENT
    };
    
    static unsigned int compileShader (unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // Error handling
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);

            const char* shaderType;
            if (type == GL_VERTEX_SHADER) {
                shaderType = "vertex";
            } else if (type == GL_FRAGMENT_SHADER) {
                shaderType = "fragment";
            } else {
                shaderType = "undefined";
            }

            std::cout << "Failed to compile " << shaderType << " shader!" << std::endl;
            std::cout << message << std::endl;

            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    static unsigned int createShader (const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        // Can delete because already link to program
        glDetachShader(program, vs);
        glDetachShader(program, fs);

        return program;
    }

    static ShaderProgramSource parseShader (const std::string& filepath)
    {
        std::ifstream stream(filepath);

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;
        while (std::getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos) 
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
                else
                    type = ShaderType::NONE;
            } 
            else
            {
                ss[(int)type] << line << '\n';
            }
        }

        return { ss[0].str(), ss[1].str() };
    }
};

