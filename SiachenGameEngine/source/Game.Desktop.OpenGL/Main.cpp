#include "pch.h"
#include "SList.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
	
	// Return if can't initialize
	if (!glfwInit())
	{
		return -1;
	}

	// Create a OpenGL window and check if it is created
	GLFWwindow* window = glfwCreateWindow(1280, 720, "SiachenGameEngine", nullptr, nullptr);
	if (window == nullptr)
	{
		return -1;
	}

	// Provide window to the API
	glfwMakeContextCurrent(window);

	// Setup OpenGL on our platform
	if (gl3wInit() != 0)
	{
		return -1;
	}

	// Dimensions for the viewport
	glViewport(0, 0, 1280, 720);

	float cornFlowerBlueColor[4] = { 0.392f, 0.584f, 0.929f, 1.0f };

	// While the window is not closed (Game loop)
	while (!glfwWindowShouldClose(window))
	{

		// Give the entire buffer a color (back buffer)
		glClearBufferfv(GL_COLOR, 0, &cornFlowerBlueColor[0]);

		// Rendering the display (double buffering)
		glfwSwapBuffers(window);
		// Process mouse or keyboard events (generally done once per loop)
		glfwPollEvents();
	}

	// Cleanup and close the application
	glfwDestroyWindow(window);
	glfwTerminate();

	// Demonstrating SList class
	SiachenGameEngine::SList myList(10);

	return 0;
}