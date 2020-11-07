#pragma once
#include <Component/SimpleScene.h>
#include "LabCamera.h"
#include <Core/Engine.h>
#include "Transform3D.h"

class Laborator5 : public SimpleScene
{
	public:
		Laborator5();
		~Laborator5();

		bool isOrtho = false;
		float orthoRight = 8.0f, orthoUp = 4.5f, orthoDown = -4.5f, orthoLeft = -8.0f;

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void CreateCylinder(float radius, float halfLength, int slices);

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;
		Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		Laborator::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		float translateY = 0;
		float fov = 60.f;
		bool start = false;
		bool up = false, down = false,straight = false;
		float angle = 0;
		int n = 100;
		float cubeStep = 0;
		float translateX = 0;
		float generateNewRectangleUpDown = 0;
		int vectorY[100000];
		int vectorLife[100000];
		float translateFuel = 0;
		int freq[10000];
		int freqHit[10000];
		int cnt_life = 3;
		float translateSky = 0;
		float dont_stop = 0;
		float angleWater = 0;

		float angleStep;
};
