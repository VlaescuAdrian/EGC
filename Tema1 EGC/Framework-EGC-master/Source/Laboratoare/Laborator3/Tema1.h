#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:

		Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat3 modelMatrix;
		glm::mat3 modelMatrix1;
		glm::mat3 modelBackAndFloor;
		glm::mat3 rectangleMatrixUp;
		glm::mat3 rectangleMatrixDown;
		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;
		GLenum cullFace;
		GLenum polygonMode;
		int n = 15;
		float vectorScaleDown[10000];
		float vectorScaleUpper[10000];
		bool pressSpace = false;
		float angularStepOY = 0;
		float counter;
		float generateNewRectangleUpDown;
		bool start = false;
		int defaultStart = 0;
		bool gameOver = false;
		float diffDown = 0;
		float diffUp = 0;
		float endGame = 0;
		float score;
		float currScore;
		float scoreDiff = 0;
		
};
