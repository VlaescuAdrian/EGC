#include "Laborator2.h"

#include <vector>
#include <iostream>

#include <stb/stb_image.h>
#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator2::Laborator2()
{
}

Laborator2::~Laborator2()
{
}

void Laborator2::Init()
{
	auto camera = GetSceneCamera();
	camera->SetPositionAndRotation(glm::vec3(2, 40, 20), glm::quat(glm::vec3(-30 * TO_RADIANS, 0, 0)));
	camera->Update();

	std::string texturePath = RESOURCE_PATH::TEXTURES + "Cube2/";
	std::string shaderPath = "Source/Laboratoare/Laborator2/Shaders/";

	{
		Mesh* mesh = new Mesh("cube");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		mesh->UseMaterials(false);
		meshes[mesh->GetMeshID()] = mesh;
	}
	// Create a shader program for rendering to texture
	{
		Shader* shader = new Shader("CubeMap");
		shader->AddShader(shaderPath + "CubeMap.VS.glsl", GL_VERTEX_SHADER);
		shader->AddShader(shaderPath + "CubeMap.FS.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for rendering to texture
	{
		Shader* shader = new Shader("ShaderNormal");
		shader->AddShader(shaderPath + "Normal.VS.glsl", GL_VERTEX_SHADER);
		shader->AddShader(shaderPath + "Normal.FS.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//cubeMapTextureID = UploadCubeMapTexture(
	//	texturePath + "posx.png",
	//	texturePath + "posy.png",
	//	texturePath + "posz.png",
	//	texturePath + "negx.png",
	//	texturePath + "negy.png",
	//	texturePath + "negz.png"
	//);

	cubeMapTextureID = UploadCubeMapTexture(
			texturePath + "dark_rt.png",
			texturePath + "dark_up.png",
			texturePath + "dark_bk.png",
			texturePath + "dark_lf.png",
			texturePath + "dark_dn.png",
			texturePath + "dark_ft.png"
		);




	{
		Mesh* mesh = new Mesh("boat");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "Fantasy yatch.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}



	//ToggleGroundPlane();

	// Create a shader program for surface generation
	{
		Shader* shader = new Shader("SurfaceGeneration");
		shader->AddShader("Source/Laboratoare/Laborator2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator2/Shaders/GeometryShader.glsl", GL_GEOMETRY_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("RightMarginalMountainsGeneration");
		shader->AddShader("Source/Laboratoare/Laborator2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator2/Shaders/GeometryShader.glsl", GL_GEOMETRY_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shaderMountains = new Shader("MountainsGeneration");
		shaderMountains->AddShader("Source/Laboratoare/Laborator2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shaderMountains->AddShader("Source/Laboratoare/Laborator2/Shaders/GeometryShaderInterMountains.glsl", GL_GEOMETRY_SHADER);
		shaderMountains->AddShader("Source/Laboratoare/Laborator2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shaderMountains->CreateAndLink();
		shaders[shaderMountains->GetName()] = shaderMountains;
	}

	//parameters related to surface generation
	dist = 0.5f;
	orientation = -1.0f;
	vertical_translation = 0;
	no_of_generated_points = 10;	//number of points on a Bezier curve
	no_of_instances = 30;			//number of instances (number of curves that contain the surface)
	max_translate = 8.0f;			//for the translation surface, it's the distance between the first and the last curve
	max_rotate = glm::radians(360.0f);	//for the rotation surface, it's the angle between the first and the last curve

	//define control points for the main water line
	control_p1 = glm::vec3(0, 0, 20);
	control_p2 = glm::vec3(0, 0, -10);
	control_p3 = glm::vec3(0, 0, -20);
	control_p4 = glm::vec3(0, 0, -30);

	//define control points for the second water line
	control_p5 = glm::vec3(-20, 0, -50);
	control_p6 = glm::vec3(-40, 0, -70);
	control_p7 = glm::vec3(-60, 0, -90);

	//define control points for the third water line
	control_p8 = glm::vec3(20, 0, -90);

	//define control points for the fourth water line
	control_p9 = glm::vec3(40, 0, -70);
	control_p10 = glm::vec3(60, 0, -90);

	pos_boat = glm::vec3(7.5f, 0, 10);
	// Create a bogus mesh with 2 points (a line)
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-4.0, -2.5,  1.0), glm::vec3(0, 1, 0)),
			VertexFormat(glm::vec3(-4.0, 5.5,  1.0), glm::vec3(0, 1, 0))
		};

		vector<unsigned short> indices =
		{
			0, 1
		};

		meshes["surface"] = new Mesh("generated initial surface points");
		meshes["surface"]->InitFromData(vertices, indices);
		meshes["surface"]->SetDrawMode(GL_LINES);
	}

	// Load textures
	{
		texture = new Texture2D;
		texture->Load2D("Resources/Textures/water.png");

		texture_rock = new Texture2D;
		texture_rock->Load2D("Resources/Textures/stone-texture.jpg");
	}
	glLineWidth(3);


}


void Laborator2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator2::RenderMeshInstanced(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int instances, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader 
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object instanced
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElementsInstanced(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, (void*)0, instances);

}


void Laborator2::Update(float deltaTimeSeconds)
{
	ClearScreen();

	auto camera = GetSceneCamera();

	//pe tot ecranul
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// draw the cubemap
	{
		Shader* shader = shaders["ShaderNormal"];
		shader->Use();

		glm::mat4 modelMatrix = glm::scale(glm::mat4(1), glm::vec3(180));

		glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
		glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
		int loc_texture = shader->GetUniformLocation("texture_cubemap");
		glUniform1i(loc_texture, 0);

		meshes["cube"]->Render();
	}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	{
		Shader* shader = shaders["SurfaceGeneration"];
		shader->Use();

		// texture for water
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(shader->program, "water"), 0);

		glUniform1i(glGetUniformLocation(shader->program, "vertical_translation"), 0.0);
		glUniform1i(glGetUniformLocation(shader->program, "orientation"), 1);
		//glUniform3f(glGetUniformLocation(shader->program, "color"), 0.08, 0.84, 0.82);
		//send uniforms main water line to shaders
		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), control_p1.x, control_p1.y, control_p1.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), control_p2.x, control_p2.y, control_p2.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p3.x, control_p3.y, control_p3.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), control_p4.x, control_p4.y, control_p4.z);
		glUniform1i(glGetUniformLocation(shader->program, "no_of_instances"), no_of_instances);

		//TODO 
		//trimitei la shadere numarul de puncte care aproximeaza o curba (no_of_generated_points)
		//si caracteristici pentru crearea suprafetelor de translatie/rotatie (max_translate, max_rotate)
		glUniform1i(glGetUniformLocation(shader->program, "no_of_generated_points"), no_of_generated_points);

		Mesh* mesh = meshes["surface"];
		//draw the object instanced
		RenderMeshInstanced(mesh, shader, glm::mat4(1), no_of_instances);

		//send uniforms second water line to shaders
		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), control_p4.x, control_p4.y, control_p4.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), control_p5.x, control_p5.y, control_p5.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p6.x, control_p6.y, control_p6.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), control_p7.x, control_p7.y, control_p7.z);

		RenderMeshInstanced(mesh, shader, glm::mat4(1), no_of_instances);

		//send uniforms third water line to shaders
		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), 0, control_p4.y, control_p4.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), 0, control_p5.y, control_p5.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), 0, control_p6.y, control_p6.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), 0, control_p8.y, control_p8.z);
		RenderMeshInstanced(mesh, shader, glm::mat4(1), no_of_instances);

		//send uniforms fourth water line to shaders
		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), -control_p4.x, control_p4.y, control_p4.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), -control_p5.x, control_p5.y, control_p5.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p9.x, control_p9.y, control_p9.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), control_p10.x, control_p10.y, control_p10.z);
		RenderMeshInstanced(mesh, shader, glm::mat4(1), no_of_instances);

		glDisable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, texture_rock->GetTextureID());
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(shader->program, "rock"), 0);
		//left marginal mountains
		//glUniform3f(glGetUniformLocation(shader->program, "color"), 0.59, 0.29, 0);
		glUniform1i(glGetUniformLocation(shader->program, "vertical_translation"), 1);
		glUniform1i(glGetUniformLocation(shader->program, "orientation"), -1);
		//glUniform1i(glGetUniformLocation(shader->program, "no_of_instances"), 50);

		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), control_p1.x, control_p1.y, control_p1.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), control_p2.x, control_p2.y, control_p2.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p3.x, control_p3.y, control_p3.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), control_p4.x, control_p4.y, control_p4.z);
		RenderMeshInstanced(mesh, shader, glm::mat4(1), 50);

		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), control_p4.x, control_p4.y, control_p4.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), control_p5.x, control_p5.y, control_p5.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p6.x, control_p6.y, control_p6.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), control_p7.x, control_p7.y, control_p7.z);
		RenderMeshInstanced(mesh, shader, glm::mat4(1), 50);


		//inner middle mountains
		glUniform1i(glGetUniformLocation(shader->program, "vertical_translation"), 2);
		glUniform1i(glGetUniformLocation(shader->program, "orientation"), -1);
		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), 0, control_p4.y, control_p4.z - no_of_instances * dist);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), 0, control_p5.y, control_p5.z - no_of_instances * dist);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), 0, control_p6.y, control_p6.z - no_of_instances * dist);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), 0, control_p7.y, control_p7.z);
		RenderMeshInstanced(mesh, shader, glm::mat4(1), 50);

		glUniform1i(glGetUniformLocation(shader->program, "vertical_translation"), 2);
		glUniform1i(glGetUniformLocation(shader->program, "orientation"), 1);
		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), no_of_instances * dist, control_p4.y, control_p4.z - no_of_instances * dist);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), no_of_instances * dist, control_p5.y, control_p5.z - no_of_instances * dist);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), no_of_instances * dist, control_p6.y, control_p6.z - no_of_instances * dist);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), no_of_instances * dist, control_p7.y, control_p7.z);
		RenderMeshInstanced(mesh, shader, glm::mat4(1), 50);

		glUniform1i(glGetUniformLocation(shader->program, "vertical_translation"), 1);
		glUniform1i(glGetUniformLocation(shader->program, "orientation"), 1);

		//right mountains

		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), control_p1.x + no_of_instances * dist, control_p1.y, control_p1.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), control_p2.x + no_of_instances * dist, control_p2.y, control_p2.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p3.x + no_of_instances * dist, control_p3.y, control_p3.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), control_p4.x + no_of_instances * dist, control_p4.y, control_p4.z);
		RenderMeshInstanced(mesh, shader, glm::mat4(1), 50);

		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), control_p4.x + no_of_instances * dist, control_p4.y, control_p4.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), -control_p5.x + no_of_instances * dist, control_p5.y, control_p5.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p9.x + no_of_instances * dist, control_p9.y, control_p9.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), control_p10.x + no_of_instances * dist, control_p10.y, control_p10.z);
		RenderMeshInstanced(mesh, shader, glm::mat4(1), 50);

		//inner outter mountains

		glUniform1i(glGetUniformLocation(shader->program, "vertical_translation"), 3);
		glUniform1i(glGetUniformLocation(shader->program, "orientation"), 1);
		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), control_p4.x, control_p4.y, control_p4.z - no_of_instances * dist);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), control_p5.x , control_p5.y, control_p5.z - no_of_instances * dist);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p6.x, control_p6.y, control_p6.z - no_of_instances * dist);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), control_p7.x, control_p7.y, control_p7.z - no_of_instances * dist);
		RenderMeshInstanced(mesh, shader, glm::mat4(1), 50);

		glUniform1i(glGetUniformLocation(shader->program, "vertical_translation"), 4);
		glUniform1i(glGetUniformLocation(shader->program, "orientation"), -1);
		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), -control_p4.x + no_of_instances * dist, control_p4.y, control_p4.z - no_of_instances * dist);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), -control_p5.x, control_p5.y, control_p5.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p9.x, control_p9.y, control_p9.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), control_p10.x, control_p10.y, control_p10.z);
		RenderMeshInstanced(mesh, shader, glm::mat4(1), no_of_instances);

		


	}
	/*
	{
		Shader* shader = shaders["RightMarginalMountainsGeneration"];
		shader->Use();

		glBindTexture(GL_TEXTURE_2D, texture_rock->GetTextureID());
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(shader->program, "rock"), 0);
		
		Mesh* mesh = meshes["surface"];


		

		//right marginal mountains
		glUniform1i(glGetUniformLocation(shader->program, "orientation"), 1);
		glUniform1i(glGetUniformLocation(shader->program, "vertical_translation"), 1);
		
		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), control_p1.x, control_p1.y, control_p1.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), control_p2.x, control_p2.y, control_p2.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p3.x, control_p3.y, control_p3.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), control_p4.x, control_p4.y, control_p4.z);
		RenderMeshInstanced(mesh, shader, glm::mat4(1), 50);

		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), control_p4.x, control_p4.y, control_p4.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), control_p5.x, control_p5.y, control_p5.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p6.x , control_p6.y, control_p6.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), control_p7.x , control_p7.y, control_p7.z);
		RenderMeshInstanced(mesh, shader, glm::mat4(1), 50);


		//draw the object instanced
		RenderMeshInstanced(mesh, shader, glm::mat4(1), no_of_instances);

		glDisable(GL_TEXTURE_2D);
	}
	*/
	{
		Shader* shader = shaders["MountainsGeneration"];
		shader->Use();

		glBindTexture(GL_TEXTURE_2D, texture_rock->GetTextureID());
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(shader->program, "rock"), 0);

		//init
		glUniform1i(glGetUniformLocation(shader->program, "vertical_translation"), 1);
		glUniform1i(glGetUniformLocation(shader->program, "orientation"), 1);
		//glUniform3f(glGetUniformLocation(shader->program, "color"), 0.59, 0.29, 0);
		glUniform1i(glGetUniformLocation(shader->program, "no_of_instances"), 50);
		glUniform1i(glGetUniformLocation(shader->program, "no_of_generated_points"), no_of_generated_points);

		//inter second and third water lines
		glUniform3f(glGetUniformLocation(shader->program, "control_p1"), control_p4.x + no_of_instances * dist, control_p4.y, control_p4.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p2"), control_p5.x + no_of_instances * dist, control_p5.y, control_p5.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p6.x + no_of_instances * dist, control_p6.y, control_p6.z);
		glUniform3f(glGetUniformLocation(shader->program, "control_p4"), control_p7.x + no_of_instances * dist, control_p7.y, control_p7.z);

		Mesh* mesh = meshes["surface"];
		//RenderMeshInstanced(mesh, shader, glm::mat4(1), 50);
	}

	if (go == true) {
		if (pos_boat.z + translateZ > -30)
			translateZ -= deltaTimeSeconds * speed;
	}

	if (pos_boat.z + translateZ < -30 || goDown == true) {
		go = false;
		if (goLeft == true) {
			if ((pos_boat.x + translateX < -40) || (goBack == true)) {
				translateZ += deltaTimeSeconds * speed;
				translateX += deltaTimeSeconds * speed;
				rotate = 3.14f / 4;
				goBack = true;	
				if (pos_boat.z + translateZ > -30) {
					rotate = 3.14f;
					goLeft = false;
					goBack = false;
					pos_boat = glm::vec3(7.5f, 0, -30.01f);
					translateX = translateZ = 0;
				}
				
			}
			else
			{
					translateZ -= deltaTimeSeconds * speed;
					translateX -= deltaTimeSeconds * speed;
					rotate = 3.14f + 3.14f / 4;
				
			}
		}
		else if (goRight == true) {
			if ((pos_boat.x + translateX > 60) || (goBack == true)) {
				translateZ += deltaTimeSeconds * speed;
				translateX -= deltaTimeSeconds * speed;
				rotate = 7* 3.14f / 4;
				goBack = true;
				if (pos_boat.z + translateZ > -30) {
					rotate = 3.14f;
					goRight = false;
					goBack = false;
					pos_boat = glm::vec3(7.5f, 0, -30.01f);
					translateX = translateZ = 0;
				}

			}
			else
			{
				translateZ -= deltaTimeSeconds * speed;
				translateX += deltaTimeSeconds * speed;
				rotate = 3*3.14f / 4;

			}
		}
		else if (goUp == true) {

			if ((pos_boat.z + translateZ < -80) || (goBack == true)) {
				translateZ += deltaTimeSeconds * speed;
				rotate = 0;
				goBack = true;
				if (pos_boat.z + translateZ > -30) {
					rotate = 3.14f;
					goUp = false;
					goBack = false;
					pos_boat = glm::vec3(7.5f, 0, -30.01f);
					translateX = translateZ = 0;
				}

			}
			else
			{
				translateZ -= deltaTimeSeconds * speed;
				rotate = 3.14f;

			}

		}
		else if (goDown == true) {
			if ((pos_boat.z + translateZ > 10) || (goBack == true)) {
				translateZ -= deltaTimeSeconds * speed;
				rotate = 3.14f;
				goBack = true;
				if (pos_boat.z + translateZ < -30) {
					rotate = 3.14f;
					goDown = false;
					goBack = false;
					pos_boat = glm::vec3(7.5f, 0, -30.01f);
					translateX = translateZ = 0;
				}

			}
			else
			{
				translateZ += deltaTimeSeconds * speed;
				rotate = 0;

			}
		}

		
	}
	{
		modelMatrixYacht = glm::translate(glm::mat4(1), pos_boat + glm::vec3(translateX, 0, translateZ));
		modelMatrixYacht *= glm::scale(glm::mat4(1), glm::vec3(0.02f, 0.02f, 0.02f));
		modelMatrixYacht *= glm::rotate(glm::mat4(1), rotate, glm::vec3(0, 1, 0));
		RenderMesh(meshes["boat"], shaders["Simple"], modelMatrixYacht);
	}






}

void Laborator2::FrameEnd()
{
	//DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator2::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
};

void Laborator2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_T)
	{
		go = true;
	}
	if (key == GLFW_KEY_UP)
	{
		goUp = true;
	}
	if (key == GLFW_KEY_LEFT)
	{
		goLeft = true;
	}
	if (key == GLFW_KEY_RIGHT)
	{
		goRight = true;
	}
	if (key == GLFW_KEY_DOWN)
	{
		goDown = true;
	}
};

void Laborator2::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator2::OnWindowResize(int width, int height)
{
	// treat window resize event
}

unsigned int Laborator2::UploadCubeMapTexture(const std::string& posx, const std::string& posy, const std::string& posz, const std::string& negx, const std::string& negy, const std::string& negz)
{
	int width, height, chn;

	unsigned char* data_posx = stbi_load(posx.c_str(), &width, &height, &chn, 0);
	unsigned char* data_posy = stbi_load(posy.c_str(), &width, &height, &chn, 0);
	unsigned char* data_posz = stbi_load(posz.c_str(), &width, &height, &chn, 0);
	unsigned char* data_negx = stbi_load(negx.c_str(), &width, &height, &chn, 0);
	unsigned char* data_negy = stbi_load(negy.c_str(), &width, &height, &chn, 0);
	unsigned char* data_negz = stbi_load(negz.c_str(), &width, &height, &chn, 0);

	// TODO - create OpenGL texture
	unsigned int textureID = 0;
	glGenTextures(1, &textureID);

	// TODO - bind the texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);



	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	float maxAnisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_posx);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_negx);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_posy);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_negy);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_posz);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_negz);


	// TODO - load texture information for each face

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	// free memory
	SAFE_FREE(data_posx);
	SAFE_FREE(data_posy);
	SAFE_FREE(data_posz);
	SAFE_FREE(data_negx);
	SAFE_FREE(data_negy);
	SAFE_FREE(data_negz);

	return textureID;
}
