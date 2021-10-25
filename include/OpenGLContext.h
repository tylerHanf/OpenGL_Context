#pragma once

#include "glew.h"
#include "glfw3.h"
#include "Logger.h"

#define CONTEXT_MAJOR_VERSION 4
#define CONTEXT_MINOR_VERSION 5

namespace OpenGL {
    enum BufferType { 
	VERT=0, 
	TEXTURE=1, 
	NORMAL=2, 
	VERT_TEXTURE=3, 
	VERT_NORMAL=4, 
	VERT_TEXTURE_NORMAL=5,
	NONE = 6,
    };

    inline bool GLFWInit(void) {
	if (!glfwInit()) {
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CONTEXT_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CONTEXT_MINOR_VERSION);
    }

    inline bool GLEWInit(void) {
	if (glewInit() != GLEW_OK) {
		Logger::LogPrint("Failed to init GLEW");
		return false;
	}
	return true;
    }

    inline void* MakeWindow(float width, float height, const char* name) {
	GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);

	if (!window) {
		Logger::LogPrint("Failed to make window");
		return NULL;
	}
	return (void*)window;
    }

    inline void SetCurrentContext(GLFWwindow* window) {
	glfwMakeContextCurrent(window);
    }

    inline bool WindowShouldClose(GLFWwindow* window) {
	return glfwWindowShouldClose(window);
    }

    inline void SetGLFWSwap(int swapPeriod) {
	glfwSwapInterval(swapPeriod);
    }

    inline void ClearColorBuffer(void) {
	glClear(GL_COLOR_BUFFER_BIT);
    }

    inline void ClearDepthBuffer(void) {
	glClear(GL_DEPTH_BUFFER_BIT);
    }

    inline void ClearGLBuffers(void) {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }

    inline void SwapBuffers(GLFWwindow* window) {
	glfwSwapBuffers(window);
    }

    inline void PollEvents(void) {
	glfwPollEvents();
    }

    inline void DestroyContext(void) {
	glfwTerminate();
    }

    inline void DestroyWindow(GLFWwindow* window) {
	glfwDestroyWindow(window);
    }

    // IDs is numVAO in size
    inline void GenVAOs(GLuint* IDs, size_t numVAOs=1) {
	glGenVertexArrays((GLsizei)numVAOs, IDs);
    }

    inline void InitVAO(unsigned int ID, BufferType type) {
	glBindVertexArray(ID);
	switch (type) {
	case VERT:
	case NORMAL:
	    glEnableVertexAttribArray(0);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	    break;
	case TEXTURE:
	    glEnableVertexAttribArray(0);
	    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	    break;
	case VERT_TEXTURE:
	    for (int i=0; i<2; ++i) glEnableVertexAttribArray(i);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const void*) 0);
	    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const void*)(3 * sizeof(GLfloat)));
	case VERT_NORMAL:
	    for (int i=0; i<2; ++i) glEnableVertexAttribArray(i);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const void*) 0);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const void*)(3 * sizeof(GLfloat)));
	    break;
	case VERT_TEXTURE_NORMAL:
	    for (int i=0; i<3; ++i) glEnableVertexAttribArray(i);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const void*) 0);
	    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const void*)(3 * sizeof(GLfloat)));
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const void*)(6 * sizeof(GLfloat)));
	    break;
	}
    }

    inline void BindVAO(unsigned int ID) {
	    glBindVertexArray(ID);
    }

    // IDs is numVBO in size
    inline void GenVBOs(unsigned int* IDs, size_t numVBOs=1) {
	glGenBuffers((GLsizei)numVBOs, (GLuint*)IDs);
    }

    // TODO: Allow different buffer types
    inline void BindVBO(unsigned int ID) {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    inline void BufferData(unsigned int size, float* startPtr) {
	glBufferData(GL_ARRAY_BUFFER, size, (const void*)startPtr, GL_STATIC_DRAW);
    }

    inline void GenTextures(unsigned int* IDs, size_t numTexts=1) {
	glGenTextures((GLsizei)numTexts, (GLuint*)IDs);
    }

    inline double GetTime(void) {
	    return glfwGetTime();
    }
}
