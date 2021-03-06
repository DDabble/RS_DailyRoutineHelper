#include "Game.h"

//// Must be included before the GLFW header
//#include <glload/gl_load.h>

//// Must be included before the GLFW header
//#include "util/graphics/gl.h"

#define GLFW_DLL
#include <GLFW/glfw3.h>

Game::Game() : m_window("RS Daily Routine Helper"), m_gameObjectManager(*this), m_input(*this)
{
	EventHandler::init(*this);
	m_physicsThread = std::thread(physics, this);
}

Game::~Game()
{
	m_keepRunning = false;
	m_physicsThread.join();
}

void Game::run()
{
	while (!glfwWindowShouldClose(m_window.m_window))
	{
		frameUpdate();
		graphicsUpdate();

		glfwSwapBuffers(m_window.m_window);

		glfwPollEvents();
	}
}

// Argument has to be pointer type, not reference type, because compilation error..
void Game::physics(Game* game)
{
	game->runPhysics();
}

void Game::runPhysics()
{
	m_lastPhysicsTime = glfwGetTime() - PHYSICS_UPDATE_INTERVAL;
	while (m_keepRunning)
	{
		double currentTime = glfwGetTime();
		if (currentTime - m_lastPhysicsTime >= PHYSICS_UPDATE_INTERVAL)
		{
			physicsUpdate();
			m_lastPhysicsTime += PHYSICS_UPDATE_INTERVAL;
			m_hasSlept = false;
		} else if (!m_hasSlept)
		{
			double durationUntilNextPhysicsTime = (m_lastPhysicsTime + PHYSICS_UPDATE_INTERVAL - currentTime) * 0.90; // Leaves 10 % of the actual duration as a time buffer, just in case
			std::this_thread::sleep_for(std::chrono::microseconds(int(durationUntilNextPhysicsTime * 1e6)));
			m_hasSlept = true;
		}
	}
}

void Game::frameUpdate()
{
	m_gameObjectManager.frameUpdate();
}

void Game::graphicsUpdate()
{
	m_gameObjectManager.graphicsUpdate();
}

void Game::physicsUpdate()
{
	m_gameObjectManager.physicsUpdate();
}
