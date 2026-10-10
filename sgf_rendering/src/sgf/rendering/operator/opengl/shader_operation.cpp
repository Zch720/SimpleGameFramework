#include "sgf/rendering/operator/opengl/shader_operation.h"

#include <fmt/format.h>
#include <glad/gl.h>
#include <stdexcept>

namespace sgf::rendering {
#pragma region static_helper
    static bool isShaderCompileSuccess(
        GLuint nShaderHandle
    ) {
        GLint nSuccess;
        glGetShaderiv(nShaderHandle, GL_COMPILE_STATUS, &nSuccess);
        return nSuccess == GL_TRUE;
    }

    static std::string getShaderCompileError(
        GLuint nShaderHandle
    ) {
        GLint nLogLength;
        glGetShaderiv(nShaderHandle, GL_INFO_LOG_LENGTH, &nLogLength);
        GLchar* pRawLog = new GLchar[nLogLength];
        glGetShaderInfoLog(nShaderHandle, nLogLength, nullptr, pRawLog);
        std::string sLog(pRawLog);
        delete[] pRawLog;
        return sLog;
    }

    static void checkShaderCompileStatus(
        GLuint nShaderHandle
    ) {
        if (!isShaderCompileSuccess(nShaderHandle)) {
            throw std::runtime_error(
                fmt::format("Compile shader failed, cause: {}", getShaderCompileError(nShaderHandle))
            );
        }
    }

    static void compileShader(
        GLuint nShaderHandle,
        const char* pSource
    ) {
        glShaderSource(nShaderHandle, 1, &pSource, nullptr);
        glCompileShader(nShaderHandle);
        checkShaderCompileStatus(nShaderHandle);
    }

    static bool isProgramLinkSuccess(
        GLuint nProgramHandle
    ) {
        GLint nSuccess;
        glGetProgramiv(nProgramHandle, GL_LINK_STATUS, &nSuccess);
        return nSuccess == GL_TRUE;
    }

    static std::string getProgramLinkError(
        GLuint nProgramHandle
    ) {
        GLint nLogLength;
        glGetProgramiv(nProgramHandle, GL_INFO_LOG_LENGTH, &nLogLength);
        GLchar* pRawLog = new GLchar[nLogLength];
        glGetProgramInfoLog(nProgramHandle, nLogLength, nullptr, pRawLog);
        std::string sLog(pRawLog);
        delete[] pRawLog;
        return sLog;
    }
    
    static void checkProgramLinkStatus(
        GLuint nProgramHandle
    ) {
        if (!isProgramLinkSuccess(nProgramHandle)) {
            std::runtime_error(
                fmt::format("Link shader failed, cause: {}", getProgramLinkError(nProgramHandle))
            );
        }
    }

    static void linkProgram(
        GLuint nProgramHandle,
        GLuint nVertexShaderHandle,
        GLuint nFragmentShaderHandle
    ) {
        glAttachShader(nProgramHandle, nVertexShaderHandle);
        glAttachShader(nProgramHandle, nFragmentShaderHandle);
        glLinkProgram(nProgramHandle);
        checkProgramLinkStatus(nProgramHandle);
        glDetachShader(nProgramHandle, nVertexShaderHandle);
        glDetachShader(nProgramHandle, nFragmentShaderHandle);
    }
#pragma endregion static_helper

    void ShaderOperationOpenGL::create(
        const ShaderId& rId,
        const Shader& rShader
    ) {
        GLuint nVertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
        compileShader(nVertexShaderHandle, rShader.getVertexShaderSource().c_str());
        GLuint nFragmentShaderHandle = glCreateShader(GL_VERTEX_SHADER);
        compileShader(nFragmentShaderHandle, rShader.getFragmentShaderSource().c_str());

        GLuint nProgramHandle = glCreateProgram();
        linkProgram(nProgramHandle, nFragmentShaderHandle, nVertexShaderHandle);
        glDeleteShader(nVertexShaderHandle);
        glDeleteShader(nFragmentShaderHandle);

        m_mapShaderProgramHandles.emplace(rId, nProgramHandle);
    }

    void ShaderOperationOpenGL::destroy(
        const ShaderId &rId,
        const Shader &rShader
    ) {
        auto oIt = getHandle(rId, true);
        glDeleteProgram(oIt->second);
        m_mapShaderProgramHandles.erase(oIt);
    }

    void ShaderOperationOpenGL::bind(
        const ShaderId& rId,
        const Shader& rShader
    ) {
        auto oIt = getHandle(rId, true);
        glUseProgram(oIt->second);
    }

    ShaderOperationOpenGL::HandleMap::iterator ShaderOperationOpenGL::getHandle(
        const ShaderId &rId,
        bool bThrowWhenNotFound
    ) {
        auto oIt = m_mapShaderProgramHandles.find(rId);
        if (oIt == m_mapShaderProgramHandles.end() && bThrowWhenNotFound) {
            throw std::runtime_error(
                fmt::format("Try to destroy shader with id {}, but not exist", rId.toString())
            );
        }
        return oIt;
    }
}
