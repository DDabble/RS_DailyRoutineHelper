﻿#pragma once

#include <glm/glm.hpp>

#include "../../GraphicsObject.h"
#include "../../../../event/types/FramebufferSizeHook.h"

#include "../../../../util/graphics/gl.h"

class Map;

class Arrow : public GraphicsObject, FramebufferSizeHook
{
private:
	GLuint m_program;
	GLuint m_vertexArrayObject;
	GLuint m_vertexBufferObject;

	GLint m_projection_uniformIndex;

	const glm::vec2 m_mapStartPoint;
	const glm::vec2 m_mapEndPoint;

	const GLint m_lineWidth;

private:
	void makeVertices(const Map& map, GLint lineWidth);

public:
	Arrow(const GraphicsObjectManager& graphics, const Map& map, glm::vec2 mapStartPoint, glm::vec2 mapEndPoint, GLint lineWidth = 10);
	~Arrow();

	void updatePosition(const Map& map);

	void graphicsUpdate(const GraphicsObjectManager& graphics) override;

	void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphics) override;
};
