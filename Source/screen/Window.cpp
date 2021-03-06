#include "Window.h"

#include <string>
#include <iostream>

#include <glload/gl_load.h>

#include <GLFW/glfw3.h>

/* Should be registered before GLFW is initialized. */
void errorCallback(int error, const char* description)
{
	std::cerr << "Error: " << description << std::endl;
}

Window::Window(const char* windowName) : m_windowWidth(INITIAL_WINDOW_WIDTH), m_windowHeight(INITIAL_WINDOW_HEIGHT)
{
	initGLFW(windowName);
	initGL_Load();
}

void Window::initGLFW(const char* windowName)
{
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
		throw std::runtime_error("Unable to initialize GLFW.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// TODO: Make this an option in the settings
	//glfwWindowHint(GLFW_SAMPLES, 4);

	m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, windowName, nullptr, nullptr);
	if (m_window == nullptr)
	{
		glfwTerminate();
		throw std::runtime_error("Unable to create a window with GLFW.");
	}

	glfwSetWindowSizeLimits(m_window, 100, 100, GLFW_DONT_CARE, GLFW_DONT_CARE);

	glfwMakeContextCurrent(m_window);

	glfwSwapInterval(1);
}

void Window::initGL_Load()
{
	int loadTest = ogl_LoadFunctions();
	if (loadTest == ogl_LOAD_FAILED)
	{
		std::string message = std::string("Unable to initialize GL Load. ") + std::to_string(loadTest - ogl_LOAD_SUCCEEDED) + " core functions failed to load.";
		std::cerr << message << std::endl;
		glfwTerminate();
		throw std::runtime_error(message);
	}
}

Window::~Window()
{
	glfwDestroyWindow(m_window);

	glfwTerminate();
}

void Window::updateFramebufferSize(int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	m_windowWidth = newWidth;
	m_windowHeight = newHeight;
}
