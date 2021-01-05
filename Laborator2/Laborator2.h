#pragma once

#include <Component/SimpleScene.h>

class Laborator2 : public SimpleScene
{
public:
	Laborator2();
	~Laborator2();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderMeshInstanced(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int instances, const glm::vec3& color = glm::vec3(1));
	unsigned int UploadCubeMapTexture(const std::string& posx, const std::string& posy, const std::string& posz, const std::string& negx, const std::string& negy, const std::string& negz);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;


protected:
	//informatii suprafata generate
	glm::vec3 control_p1, control_p2, control_p3, control_p4, control_p5, control_p6, control_p7, control_p8, control_p9, control_p10, control_p11, control_p12, control_p13, control_p14;
	unsigned int no_of_generated_points, no_of_instances, vertical_translation, orientation;
	float max_translate, max_rotate, dist;
	float translateZ = 0;
	float translateX = 0;
	float rotate = 3.14;
	bool go = false;
	bool goUp = false;
	bool goLeft = false;
	bool goRight = false;
	bool goDown = false;
	bool goBack = false;
	float speed = 20;


	Texture2D* texture;
	Texture2D* texture_rock;

	int cubeMapTextureID;

	glm::vec3 pos_boat;
	glm::mat4 modelMatrixYacht = glm::mat4(0);

};