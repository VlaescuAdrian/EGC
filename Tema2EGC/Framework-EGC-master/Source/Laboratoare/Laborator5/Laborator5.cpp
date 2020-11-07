#include "Laborator5.h"
#include "LabCamera.h"
#include "Transform3D.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator5::Laborator5()
{
}

Laborator5::~Laborator5()
{
}



int printRandoms(int lower, int upper)
{
	int i;
	int num = 0;
	num = (rand() %
		(upper - lower + 1)) + lower;

	return num;
}
void Laborator5::Init()
{
	renderCameraTarget = false;
	angleStep = 0;


	for (int i = 0; i < 100000; i++)
	{
		vectorY[i] = printRandoms(0, 7);
		vectorLife[i] = printRandoms(0, 7);
	}
	for (int i = 0; i < 10000; i++)
	{
		freq[i] = 0;
		freqHit[i] = 0;
	}

	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 3, 15), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	float cube_length = 0.5f;
	float diff = 0.15f;
	float second_cube_length = 0.2f;
	float alice_width = 0.1f;

	{
		Shader *shader = new Shader("ShaderLab5");
		shader->AddShader("Source/Laboratoare/Laborator5/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator5/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	float radius = 2;
	float halffLength = 2;
	float slices = 40;
	CreateCylinder(radius, halffLength, slices);

	{
		vector<VertexFormat> vertices
		{

			VertexFormat(glm::vec3(0,0,0), glm::vec3(1,1,1),glm::vec3(1,0,0)),//0
			VertexFormat(glm::vec3(cube_length,0,0), glm::vec3(1,1,1),glm::vec3(1,0,0)),//1
			VertexFormat(glm::vec3(cube_length,cube_length,0), glm::vec3(1,1,1),glm::vec3(1,0,0)),//2
			VertexFormat(glm::vec3(0,cube_length,0), glm::vec3(1,1,1),glm::vec3(1,0,0)),//3
			VertexFormat(glm::vec3(0,0,-cube_length), glm::vec3(1,1,1),glm::vec3(1,0,0)),//4
			VertexFormat(glm::vec3(cube_length,0,-cube_length), glm::vec3(1,1,1),glm::vec3(1,0,0)),//5
			VertexFormat(glm::vec3(cube_length,cube_length,-cube_length), glm::vec3(1,1,1),glm::vec3(1,0,0)),//6
			VertexFormat(glm::vec3(0,cube_length,-cube_length), glm::vec3(1,1,1),glm::vec3(1,0,0)),//7

			VertexFormat(glm::vec3(cube_length,diff,-diff), glm::vec3(1,1,1),glm::vec3(1,0,0)),//8
			VertexFormat(glm::vec3(cube_length + second_cube_length,diff,-diff), glm::vec3(1,1,1),glm::vec3(1,0,0)),//9
			VertexFormat(glm::vec3(cube_length + second_cube_length,second_cube_length + diff,-diff), glm::vec3(1,1,1),glm::vec3(1,0,0)),//10
			VertexFormat(glm::vec3(cube_length,second_cube_length + diff,-diff), glm::vec3(1,1,1),glm::vec3(1,0,0)),//11
			VertexFormat(glm::vec3(cube_length,diff,-diff - second_cube_length), glm::vec3(1,1,1),glm::vec3(1,0,0)),//12
			VertexFormat(glm::vec3(cube_length + second_cube_length,diff,-diff - second_cube_length), glm::vec3(1,1,1),glm::vec3(1,0,0)),//13
			VertexFormat(glm::vec3(cube_length + second_cube_length,second_cube_length + diff,-diff - second_cube_length), glm::vec3(1,0,0),glm::vec3(0,0,0)),//14
			VertexFormat(glm::vec3(cube_length,second_cube_length + diff,-diff - second_cube_length), glm::vec3(1,1,1),glm::vec3(1,0,0)),//15

			VertexFormat(glm::vec3(second_cube_length -0.2f,second_cube_length,cube_length),glm::vec3(1,1,1), glm::vec3(1,1,1)),//16
			VertexFormat(glm::vec3(alice_width + second_cube_length + 0.1f,second_cube_length ,cube_length),glm::vec3(1,1,1), glm::vec3(1,1,1)),//17
			VertexFormat(glm::vec3(alice_width + second_cube_length + 0.1f,alice_width + second_cube_length ,cube_length),glm::vec3(1,1,1), glm::vec3(1,1,1)),//18
			VertexFormat(glm::vec3(second_cube_length - 0.2f,alice_width + second_cube_length ,cube_length),glm::vec3(1,1,1), glm::vec3(1,1,1)),//19
			VertexFormat(glm::vec3(second_cube_length -0.2f,second_cube_length,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//20
			VertexFormat(glm::vec3(alice_width + second_cube_length +0.1f,second_cube_length,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//21
			VertexFormat(glm::vec3(alice_width + second_cube_length +0.1f,alice_width + second_cube_length,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//22
			VertexFormat(glm::vec3(second_cube_length -0.2f,alice_width + second_cube_length,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//23

			VertexFormat(glm::vec3(second_cube_length - 0.2f,second_cube_length,-cube_length),glm::vec3(1,1,1), glm::vec3(1,1,1)),//16
			VertexFormat(glm::vec3(alice_width + second_cube_length + 0.1f,second_cube_length ,-cube_length),glm::vec3(1,1,1), glm::vec3(1,1,1)),//17
			VertexFormat(glm::vec3(alice_width + second_cube_length + 0.1f,alice_width + second_cube_length ,-cube_length),glm::vec3(1,1,1), glm::vec3(1,1,1)),//18
			VertexFormat(glm::vec3(second_cube_length - 0.2f,alice_width + second_cube_length ,-cube_length),glm::vec3(1,1,1), glm::vec3(1,1,1)),//19
			VertexFormat(glm::vec3(second_cube_length - 0.2f,second_cube_length,-2 * cube_length),glm::vec3(1,1,1), glm::vec3(1,1,1)),//20
			VertexFormat(glm::vec3(alice_width + second_cube_length + 0.1f,second_cube_length,-2 * cube_length),glm::vec3(1,1,1), glm::vec3(1,1,1)),//21
			VertexFormat(glm::vec3(alice_width + second_cube_length + 0.1f,alice_width + second_cube_length,-2 * cube_length),glm::vec3(1,1,1), glm::vec3(1,1,1)),//22
			VertexFormat(glm::vec3(second_cube_length - 0.2f,alice_width + second_cube_length,-2 * cube_length),glm::vec3(1,1,1), glm::vec3(1,1,1)),//23

			VertexFormat(glm::vec3(-2*cube_length, cube_length/4,-cube_length/4), glm::vec3(1,1,1),glm::vec3(1,1,1)),//32
			VertexFormat(glm::vec3(-2*cube_length, 3* cube_length / 4,-cube_length / 4), glm::vec3(1,1,1),glm::vec3(1,1,1)),//33
			VertexFormat(glm::vec3(-2*cube_length, cube_length / 4,-3 * cube_length / 4), glm::vec3(1,1,1),glm::vec3(1,1,1)),//34
			VertexFormat(glm::vec3(-2*cube_length, 3 * cube_length / 4,-3 * cube_length / 4), glm::vec3(1,1,1),glm::vec3(1,1,1)),//35

			VertexFormat(glm::vec3(-3 * cube_length, cube_length / 4,-cube_length / 4), glm::vec3(1,1,1),glm::vec3(1,1,1)),//36
			VertexFormat(glm::vec3(-3 * cube_length, cube_length / 4,-3 * cube_length / 4), glm::vec3(1,1,1),glm::vec3(1,1,1)),//37
			VertexFormat(glm::vec3(-2 * cube_length, 5 * cube_length / 4,-cube_length / 4), glm::vec3(1,1,1),glm::vec3(1,1,1)),//38
			VertexFormat(glm::vec3(-3 * cube_length, 5*cube_length / 4,-cube_length / 4), glm::vec3(1,1,1),glm::vec3(1,1,1)),//39
			VertexFormat(glm::vec3(-2 * cube_length, 5*cube_length / 4,-3 * cube_length / 4), glm::vec3(1,1,1),glm::vec3(1,1,1)),//40
			VertexFormat(glm::vec3(-3 * cube_length, 5*cube_length / 4,-3 * cube_length / 4), glm::vec3(1,1,1),glm::vec3(1,1,1)),//41



		};

		vector<unsigned short> indices =
		{
			0,1,2,
			0,2,3,
			1,5,6,
			1,6,2,
			3,2,6,
			3,6,7,
			4,0,3,
			4,3,7,
			0,1,5,
			0,5,4,
			4,6,5,
			4,7,6,


			36,32,34,
			36,34,37,
			36,32,38,
			36,38,39,
			32,34,40,
			32,40,38,
			37,36,39,
			37,39,41,
			39,38,40,
			39,40,41,
			37,41,40,
			37,40,34,

			32,0,3,
			32,3,33,
			33,3,7,
			33,7,35,
			34,35,7,
			34,7,4,
			32,0,4,
			32,4,34,

			8,9,10,
			8,10,11,
			9,13,14,
			9,14,10,
			11,10,14,
			11,14,15,
			12,8,11,
			12,11,15,
			8,9,13,
			8,13,12,
			12,14,13,
			12,15,14,

			16,17,18,
			16,18,19,
			17,21,22,
			17,22,18,
			19,18,22,
			19,22,23,
			20,16,19,
			20,19,23,
			16,17,21,
			16,21,20,
			20,22,21,
			20,23,22,

			24,25,26,
			24,26,27,
			25,29,30,
			25,30,26,
			27,26,30,
			27,30,31,
			28,24,27,
			28,27,31,
			24,25,29,
			24,29,28,
			28,30,29,
			28,31,30,


		};

		CreateMesh("planeBody", vertices, indices);

	}


	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(cube_length + second_cube_length,diff,0), glm::vec3(1,1,1),glm::vec3(1,0,0)),//0
			VertexFormat(glm::vec3(cube_length + second_cube_length + 0.1f,diff,0), glm::vec3(1,1,1),glm::vec3(1,0,0)),//1
			VertexFormat(glm::vec3(cube_length + second_cube_length + 0.1f,diff + 0.1f,0), glm::vec3(1,1,1),glm::vec3(1,0,0)),//2
			VertexFormat(glm::vec3(cube_length + second_cube_length ,diff + 0.1f,0), glm::vec3(1,1,1),glm::vec3(1,0,0)),//3
			VertexFormat(glm::vec3(cube_length + second_cube_length,diff,-cube_length), glm::vec3(1,1,1),glm::vec3(1,0,0)),//4
			VertexFormat(glm::vec3(cube_length + second_cube_length + 0.1f,diff,-cube_length), glm::vec3(1,1,1),glm::vec3(1,0,0)),//5
			VertexFormat(glm::vec3(cube_length + second_cube_length + 0.1f,diff + 0.1f,-cube_length), glm::vec3(1,1,1),glm::vec3(1,0,0)),//6
			VertexFormat(glm::vec3(cube_length + second_cube_length ,diff + 0.1f,-cube_length), glm::vec3(1,1,1),glm::vec3(1,0,0)),//7
		};


		vector<unsigned short> indices =
		{
						0,1,2,
			0,2,3,
			1,5,6,
			1,6,2,
			3,2,6,
			3,6,7,
			4,0,3,
			4,3,7,
			0,1,5,
			0,5,4,
			4,6,5,
			4,7,6,

		};

		CreateMesh("elice", vertices, indices);
	}


	{
		vector<VertexFormat> vertices{
			VertexFormat(glm::vec3(8,8,0),glm::vec3(1,1,1), glm::vec3(0,1,0)),//0
			VertexFormat(glm::vec3(14.5f,8,0),glm::vec3(1,1,1), glm::vec3(0,1,0)),//1
			VertexFormat(glm::vec3(14.5f,9,0),glm::vec3(1,1,1), glm::vec3(0,1,0)),//2
			VertexFormat(glm::vec3(8,9,0),glm::vec3(1,1,1), glm::vec3(0,1,0)),//3


		};
		vector<unsigned short> indices =
		{
			0,1,2,
			0,2,3

		};
		CreateMesh("fuelGone", vertices, indices);
	}

	float small = 0.3f;
	float big = 0.4f;
	{
		vector<VertexFormat> vertices{
			VertexFormat(glm::vec3(0,0,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//0
			VertexFormat(glm::vec3(0 + small,0,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//1
			VertexFormat(glm::vec3(0+ small,0 + small,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//2
			VertexFormat(glm::vec3(0,0 + small,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//3

			VertexFormat(glm::vec3(0,0,-small),glm::vec3(1,1,1), glm::vec3(1,1,1)),//4
			VertexFormat(glm::vec3(0 + small,0,- small),glm::vec3(1,1,1), glm::vec3(1,1,1)),//5
			VertexFormat(glm::vec3(0 + small,0 + small,-small),glm::vec3(1,1,1), glm::vec3(1,1,1)),//6
			VertexFormat(glm::vec3(0,0 + small,-small),glm::vec3(1,1,1), glm::vec3(1,1,1)),//7

			VertexFormat(glm::vec3(small,0 + small/2,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//8
			VertexFormat(glm::vec3(big + small,0 + small/2,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//9
			VertexFormat(glm::vec3(big + small,0 + small/2 + big,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//10
			VertexFormat(glm::vec3(small,0 + small / 2 + big,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//11
			VertexFormat(glm::vec3(small,0 + small / 2,-big),glm::vec3(1,1,1), glm::vec3(1,1,1)),//8
			VertexFormat(glm::vec3(big + small,0 + small / 2,-big),glm::vec3(1,1,1), glm::vec3(1,1,1)),//9
			VertexFormat(glm::vec3(big + small,0 + small / 2 + big,-big),glm::vec3(1,1,1), glm::vec3(1,1,1)),//10
			VertexFormat(glm::vec3(small,0 + small / 2 + big,-big),glm::vec3(1,1,1), glm::vec3(1,1,1)),//11

			VertexFormat(glm::vec3(small + big/2,0,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//0
			VertexFormat(glm::vec3(small + big / 2 + big,0,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//1
			VertexFormat(glm::vec3(small + big / 2 + big,0 + big,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//2
			VertexFormat(glm::vec3(small + big / 2,0 + big,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//3

			VertexFormat(glm::vec3(small + big / 2,0,-big),glm::vec3(1,1,1), glm::vec3(1,1,1)),//0
			VertexFormat(glm::vec3(small + big / 2 + big,0,-big),glm::vec3(1,1,1), glm::vec3(1,1,1)),//1
			VertexFormat(glm::vec3(small + big / 2 + big,0 + big,-big),glm::vec3(1,1,1), glm::vec3(1,1,1)),//2
			VertexFormat(glm::vec3(small + big / 2,0 + big,-big),glm::vec3(1,1,1), glm::vec3(1,1,1)),//3


			VertexFormat(glm::vec3(small + big / 2 + big,0 + big -small/2,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//2
			VertexFormat(glm::vec3(small + big / 2 + big + small,0 + big - small/2,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//2
			VertexFormat(glm::vec3(small + big / 2 + big + small,0 + big + small - small/2,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//2
			VertexFormat(glm::vec3(small + big / 2 + big ,0 + big + small - small/2,0),glm::vec3(1,1,1), glm::vec3(1,1,1)),//2
			VertexFormat(glm::vec3(small + big / 2 + big,0 + big - small/2,-small),glm::vec3(1,1,1), glm::vec3(1,1,1)),//2
			VertexFormat(glm::vec3(small + big / 2 + big + small,0 + big - small/2,-small),glm::vec3(1,1,1), glm::vec3(1,1,1)),//2
			VertexFormat(glm::vec3(small + big / 2 + big + small,0 + big + small - small/2,-small),glm::vec3(1,1,1), glm::vec3(1,1,1)),//2
			VertexFormat(glm::vec3(small + big / 2 + big ,0 + big + small - small/2,-small),glm::vec3(1,1,1), glm::vec3(1,1,1)),//2



		};
		vector<unsigned short> indices =
		{
			0,1,2,
			0,2,3,
			1,5,6,
			1,6,2,
			3,2,6,
			3,6,7,
			4,0,3,
			4,3,7,
			0,1,5,
			0,5,4,
			4,6,5,
			4,7,6,
			8,9,10,
			8,10,11,
			9,13,14,
			9,14,10,
			11,10,14,
			11,14,15,
			12,8,11,
			12,11,15,
			8,9,13,
			8,13,12,
			12,14,13,
			12,15,14,
			16,17,18,
			16,18,19,
			17,21,22,
			17,22,18,
			19,18,22,
			19,22,23,
			20,16,19,
			20,19,23,
			16,17,21,
			16,21,20,
			20,22,21,
			20,23,22,
			24,25,26,
			24,26,27,
			25,29,30,
			25,30,26,
			27,26,30,
			27,30,31,
			28,24,27,
			28,27,31,
			24,25,29,
			24,29,28,
			28,30,29,
			28,31,30,

		};
		CreateMesh("firstCloud", vertices, indices);
	}

	{
		vector<VertexFormat> vertices{
			VertexFormat(glm::vec3(8,8,0),glm::vec3(1,1,1), glm::vec3(1,0,0)),//0
			VertexFormat(glm::vec3(14.5f,8,0),glm::vec3(1,1,1), glm::vec3(1,0,0)),//1
			VertexFormat(glm::vec3(14.5f,9,0),glm::vec3(1,1,1), glm::vec3(1,0,0)),//2
			VertexFormat(glm::vec3(8,9,0),glm::vec3(1,1,1), glm::vec3(1,0,0)),//3


		};
		vector<unsigned short> indices =
		{
			0,1,2,
			0,2,3

		};
		CreateMesh("fullFuel", vertices, indices);
	}
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("teapot");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;

		{
			vector<VertexFormat> vertices{
				VertexFormat(glm::vec3(-14,8,0),glm::vec3(1,1,1), glm::vec3(1,0,0)),//0
				VertexFormat(glm::vec3(-13,8,0),glm::vec3(1,1,1), glm::vec3(1,0,0)),//1
				VertexFormat(glm::vec3(-13,9,0),glm::vec3(1,1,1), glm::vec3(1,0,0)),//2
				VertexFormat(glm::vec3(-14,9,0),glm::vec3(1,1,1), glm::vec3(1,0,0)),//3


			};
			vector<unsigned short> indices =
			{
				0,1,2,
				0,2,3

			};
			CreateMesh("firstLife", vertices, indices);
		}


	}


	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

void Laborator5::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(233.f/255.f, 201.f/255.f, 177.f/255.f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}




void Laborator5::Update(float deltaTimeSeconds)
{
	

	generateNewRectangleUpDown += deltaTimeSeconds;
	if (fmod(generateNewRectangleUpDown, 4) < 3) {
		n++;
	}

	angleStep += deltaTimeSeconds * 1000;
	angle += deltaTimeSeconds * 300;
	angleWater += deltaTimeSeconds * 100;
	translateX -= deltaTimeSeconds * 5;
	translateFuel += deltaTimeSeconds/4;
	translateSky -= deltaTimeSeconds * 2.5f;
	
	glm::mat4 modelMatrix = glm::mat4(1);
	glm::mat4 modelMatrix1 = glm::mat4(1);
	//avionnnnnnnnnnnnnnnnnnnnnn
	if (up == true) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(0, translateY  * 0.01f, 0))
			*  glm::rotate(modelMatrix, RADIANS(5.f), glm::vec3(0, 0, 1));
		RenderMesh(meshes["planeBody"], shaders["VertexNormal"], modelMatrix);

		//eliceeeeeeeeeeeeeeeeeeeee		
		modelMatrix1 = glm::mat4(1);
		glm::vec3 P = glm::vec3(0.7f, 0.25f + translateY * 0.01f, -0.25f);
		modelMatrix1 *= glm::translate(modelMatrix1, glm::vec3(P.x, P.y, P.z))
			* glm::rotate(modelMatrix1, RADIANS(angleStep), glm::vec3(1, 0, 0))
			* glm::translate(modelMatrix1, glm::vec3(-P.x, -P.y, -P.z)) * glm::translate(modelMatrix1, glm::vec3(0, translateY  * 0.01f, 0))
			;
		RenderMesh(meshes["elice"], shaders["VertexNormal"], modelMatrix1);
	}
	else if (down == true)
	{
		modelMatrix = glm::mat4(1);
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(0, translateY  * 0.01f, 0))
			*  glm::rotate(modelMatrix, RADIANS(-5.f), glm::vec3(0, 0, 1));
		RenderMesh(meshes["planeBody"], shaders["VertexNormal"], modelMatrix);

		//eliceeeeeeeeeeeeeeeeeeeee		
		modelMatrix1 = glm::mat4(1);
		glm::vec3 P = glm::vec3(0.7f, 0.25f + translateY * 0.01f, -0.25f);
		modelMatrix1 *= glm::translate(modelMatrix1, glm::vec3(P.x, P.y, P.z))
			* glm::rotate(modelMatrix1, RADIANS(angleStep), glm::vec3(1, 0, 0))
			* glm::translate(modelMatrix1, glm::vec3(-P.x, -P.y, -P.z)) * glm::translate(modelMatrix1, glm::vec3(0, translateY  * 0.01f, 0))
			;
		RenderMesh(meshes["elice"], shaders["VertexNormal"], modelMatrix1);
	}
	else if (up == false && down == false) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(0, translateY  * 0.01f, 0));
		RenderMesh(meshes["planeBody"], shaders["VertexNormal"], modelMatrix);

		//eliceeeeeeeeeeeeeeeeeeeee		
		modelMatrix1 = glm::mat4(1);
		glm::vec3 P = glm::vec3(0.7f, 0.25f + translateY * 0.01f, -0.25f);
		modelMatrix1 *= glm::translate(modelMatrix1, glm::vec3(P.x, P.y, P.z))
			* glm::rotate(modelMatrix1, RADIANS(angleStep), glm::vec3(1, 0, 0))
			* glm::translate(modelMatrix1, glm::vec3(-P.x, -P.y, -P.z)) * glm::translate(modelMatrix1, glm::vec3(0, translateY  * 0.01f, 0))
			;
		RenderMesh(meshes["elice"], shaders["VertexNormal"], modelMatrix1);
	}



	modelMatrix = glm::mat4(1);
	if (start == true) {
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(translateFuel, 0, 0));
	}
	RenderMesh(meshes["fuelGone"], shaders["VertexNormal"], modelMatrix);
	if (translateFuel + 8 >= 14.5f)
	{
		exit(1);
	}
	
	modelMatrix = glm::mat4(1);
	RenderMesh(meshes["fullFuel"], shaders["VertexNormal"], modelMatrix);


	float cnt = 0;
	float cnt_teapot = 0;
	float cnt_sky = 0;
	for (int i = 0; i < n; i++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(translateSky, 0, 0))
			* glm::translate(modelMatrix, glm::vec3(cnt_sky, vectorY[i], 0)) * glm::rotate(modelMatrix, RADIANS(angle), glm::vec3(1, 0.2f, 0));
		if (translateSky + cnt_sky < 20 && translateSky + cnt_sky > -20) {

			RenderMesh(meshes["firstCloud"], shaders["VertexNormal"], modelMatrix);
		}


		modelMatrix = glm::mat4(1);
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(translateX, 0, 0))
			* glm::translate(modelMatrix, glm::vec3(cnt, vectorY[i], 0)) * glm::rotate(modelMatrix, RADIANS(angle), glm::vec3(1, 0, 0));

		if (translateX + cnt < 20 && translateX + cnt > -20) {
			
			RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
		}
		modelMatrix = glm::mat4(1);
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(translateX, 0, 0))
			* glm::translate(modelMatrix, glm::vec3(cnt_teapot, vectorLife[i], 0));
		if (vectorY[i] != vectorLife[i] && translateX + cnt_teapot < 20 && translateX + cnt_teapot > -20 && freq[i] == 0)
		{
			RenderMesh(meshes["teapot"], shaders["VertexNormal"], modelMatrix);
		}

		if (translateX + cnt >= 0 && translateX + cnt <= 0.7f && vectorY[i] >= -0.7f + translateY * 0.01f &&
			vectorY[i] <= 0.7f + translateY * 0.01f && freqHit[i] == 0 && start == true) 
		{
			freqHit[i] = 1;
			cnt_life--;
		}
		float space = 0;
		for (int i = 0; i < cnt_life; i++) {
			modelMatrix = glm::mat4(1);
			modelMatrix *= glm::translate(modelMatrix, glm::vec3(space, 0, 0));
			RenderMesh(meshes["firstLife"], shaders["VertexNormal"], modelMatrix);
			space += 1.5f;
		}
		if (cnt_life == 0)
		{
			exit(1);
		}
		if (translateX + cnt_teapot >= 0 && translateX + cnt_teapot <= 0.7f && vectorLife[i] >= -0.5f + translateY * 0.01f
			&& vectorLife[i] <= 0.5f + translateY * 0.01f && start == true)
		{
			freq[i] = 1;
			if (translateFuel - 0.4f >= 0) {
				translateFuel -= 0.4f;
			}
			else
			{
				translateFuel = 0;
			}
		}
		if (start == false)
		{
			translateFuel = 0;
		}
		cnt += 5;
		cnt_teapot += 15;
		cnt_sky += 3;
	}
	modelMatrix1 = glm::mat4(1);
	modelMatrix1 *= glm::translate(modelMatrix1, glm::vec3(0, -8, 0)) 
				* glm::scale(modelMatrix1,glm::vec3(8.f,2.f,1.3f)) * glm::rotate(modelMatrix1, RADIANS(angleWater), glm::vec3(0, 0, 1));
	RenderMesh(meshes["cylinder"], shaders["ShaderLab5"], modelMatrix1);

	
	

}

void Laborator5::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Laborator5::CreateCylinder(float radius, float halfLength, int slices) {
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	for (int i = 0; i < slices; i++)
	{
		float theta = ((float)i / slices) * 2.0 * M_PI;
		float theta1 = ((float)i + 1) / slices * 2.0 * M_PI;

		vertices.push_back(VertexFormat(glm::vec3(0.0, halfLength, 0.0), glm::vec3(0, 0, 1),glm::vec3(0.04f,0.88f,1.f)));
		vertices.push_back(VertexFormat(glm::vec3(radius * cos(theta), halfLength, radius * sin(theta)), glm::vec3(0, 0, 1), glm::vec3(0.04f, 0.88f, 1.f)));
		vertices.push_back(VertexFormat(glm::vec3(radius * cos(theta1), halfLength, radius * sin(theta1)), glm::vec3(0, 0, 1), glm::vec3(0.04f, 0.88f, 1.f)));

		vertices.push_back(VertexFormat(glm::vec3(0.0, -halfLength, 0.0), glm::vec3(0, 0, 1), glm::vec3(0.04f, 0.88f, 1.f)));
		vertices.push_back(VertexFormat(glm::vec3(radius * cos(theta), -halfLength, radius * sin(theta)), glm::vec3(0, 0, 1), glm::vec3(0.04f, 0.88f, 1.f)));
		vertices.push_back(VertexFormat(glm::vec3(radius * cos(theta1), -halfLength, radius * sin(theta1)), glm::vec3(0, 0, 1), glm::vec3(0.04f, 0.88f, 1.f)));
	}

	for (int i = 0; i < 6 * slices; i++)
	{
		indices.push_back(i);
	}
	Mesh* cilindru = CreateMesh("cylinder", vertices, indices);
	cilindru->SetDrawMode(GL_TRIANGLE_STRIP);

	
}

Mesh* Laborator5::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}

void Laborator5::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator5::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_O)) {
			orthoLeft = -8.0f;
			orthoRight = 8.0f;
			orthoUp = 4.5f;
			orthoDown = -4.5;
			projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
			isOrtho = true;
		}

		// increase height
		if (window->KeyHold(GLFW_KEY_UP) && isOrtho) {
			orthoUp += deltaTime;
			orthoDown -= deltaTime;
			projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
		}

		// increase height
		if (window->KeyHold(GLFW_KEY_DOWN) && isOrtho) {
			orthoUp -= deltaTime;
			orthoDown += deltaTime;
			projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
		}

		// increase length
		if (window->KeyHold(GLFW_KEY_RIGHT) && isOrtho) {
			orthoRight += deltaTime;
			orthoLeft -= deltaTime;
			projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
		}

		// decrease length
		if (window->KeyHold(GLFW_KEY_LEFT) && isOrtho) {
			orthoRight -= deltaTime;
			orthoLeft += deltaTime;
			projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
		}

		// inversare FOV
		if (window->KeyHold(GLFW_KEY_K)) {
			projectionMatrix = glm::perspective(fov, -2.f, 0.01f, -200.0f);
			isOrtho = false;
		}
		if (window->KeyHold(GLFW_KEY_1)) {
			fov += deltaTime * 10.f;
			projectionMatrix = glm::perspective(fov, -2.f, 0.01f, -200.0f);
			isOrtho = false;
		}if (window->KeyHold(GLFW_KEY_2)) {
			fov += deltaTime * 10.f;
			projectionMatrix = glm::perspective(fov, -2.f, 0.01f, -200.0f);
			isOrtho = false;
		}
		// FOV normal
		if (window->KeyHold(GLFW_KEY_P))
		{
			projectionMatrix = glm::perspective(fov, 2.f, 0.01f, 200.0f);
			isOrtho = false;
		}
	}
}



void Laborator5::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
		//window->GetSpecialKeyState() = 1;
	}
}

void Laborator5::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (start)
	{
		translateY = window->GetResolution().y - mouseY;
		if (deltaY < 0)
		{
			up = true;
			down = false;
			straight = false;
		}
		else if (deltaY > 0)
		{
			up = false;
			down = true;
			straight = false;
		}
		else if (deltaY == 0)
		{
			up = false;
			down = false;
			straight = true;
		}
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-2 * sensivityOX * deltaY);
			camera->RotateFirstPerson_OY(-2 * sensivityOY * deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(-2 * sensivityOX * deltaY);
			camera->RotateThirdPerson_OY(-2 * sensivityOY * deltaX);
		}

	}
}

void Laborator5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (button == 1 && mods == 0 && dont_stop == 0)
	{
		start = !start;
		dont_stop++;
	}
}

void Laborator5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator5::OnWindowResize(int width, int height)
{
}
