#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color, bool fill = false);
	//Mesh* CreateBird(std::string name, glm::vec3 leftBottomCornerSquare1, float lengthSquare1,
		//glm::vec3 leftBottomCornerSquare2, float lengthSquare2, glm::vec3 color, glm::vec3 color2);
	Mesh* CreateBackround(std::string name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color);
	Mesh* CreateFloor(std::string name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color);
	Mesh* CreatePrincipalBird(std::string name, glm::vec3 corner,  glm::vec3 red, glm::vec3 black, glm::vec3 white, glm::vec3 orange, glm::vec3 yellow);
	//Mesh* CreateCircle(std::string name, glm::vec3 center,float radius);

}

