#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

//for this function, I inspired myself from: https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
float  random_between_two_floats(float min, float max)
{
	return (max - min) * ((((float)rand()) / (float)RAND_MAX)) + min;
}

void Tema1::Init()
{

	cullFace = GL_BACK;
	polygonMode = GL_FILL;

	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	//glm::vec3 trianglecorner = glm::vec3(300, 300, 0);
	glm::vec3 square1corner = glm::vec3(350, 350, 0);
	glm::vec3 square2corner = glm::vec3(380, 355, 0);
	float squareSide1 = 30;
	float squareSide2 = 20;

	glm::vec3 PRcorner = glm::vec3(150, 300, 0);


	float rectangleWidth = 50;
	float rectangleHeight = 350;

	float backWidth = 1280;
	float backHeight = 720;
	glm::vec3 backCorner = glm::vec3(0, 0, 0);

	float floorWidth = 1280;
	float floorHeight = 30;
	glm::vec3 floorCorner = glm::vec3(0, 0, 0);
	glm::vec3 rectangledowncorner = glm::vec3(0, 0, 0);
	glm::vec3 rectangleupcorner = glm::vec3(0, 520, 0);


	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;

	// initialize angularStep
	angularStep = 0;

	for (int i = 0; i < 10000; i++)
	{
		vectorScaleDown[i] = random_between_two_floats(0.8f, 0.95f);
		vectorScaleUpper[i] = random_between_two_floats(1.1f, 1.2f);
	}

	Mesh* rectangleDown = Object2D::CreateRectangle("rectangleDown", rectangledowncorner,  glm::vec3(0, 1, 0), true);
	AddMeshToList(rectangleDown);
	Mesh* rectangleUpper = Object2D::CreateRectangle("rectangleUpper", rectangleupcorner,  glm::vec3(0, 1, 0), true);
	AddMeshToList(rectangleUpper);

	Mesh* back = Object2D::CreateBackround("back", backCorner, backHeight, backWidth, glm::vec3(0.3, 0.9, 1));
	AddMeshToList(back);

	Mesh* floor = Object2D::CreateBackround("floor", floorCorner, floorHeight, floorWidth, glm::vec3(206/255.f, 133 / 255.f,63 / 255.f));
	AddMeshToList(floor);

	Mesh* PRbird = Object2D::CreatePrincipalBird("prBird", PRcorner, glm::vec3(1,0,0), glm::vec3(0, 0, 0),
		glm::vec3(1, 1, 1), glm::vec3(1, 165/255.f, 0), glm::vec3(1, 1, 0));
	AddMeshToList(PRbird);

	
	
}



void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

glm::mat2 matrix(float x, float y) {
	return glm::mat2(x,y,
					x,y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	glm::vec3 upperCorner = glm::vec3(0,720,0);
	if (gameOver == false) {
		if (start == true) {
			if (pressSpace == false) {
				//if i don't press space, the bird is going down with the value below
				translateY -= deltaTimeSeconds * 200;
				angularStepOY = -0.1f;
			}
			else
			{
				counter++;
				angularStepOY = 0.5f;
				translateY += 15;

			}
		}
	}
	else
	{
		//after the bird colides, i moved it on the floor and wait 100 frames to exit the game and print the score
		translateY = -300;
		angularStepOY = -0.1f;
		endGame++;
		if (endGame == 50) {
			cout << "Total score is:" << score - scoreDiff - 1 << endl;
			exit(1);
		}
	}

	if (fmod(counter, 5) == 0) {
		pressSpace = false;
	}

	glm::vec3 birdcorner = glm::vec3(150, 300 + translateY, 0);
	//h is the square length for every square who makes the bird
	float h = 4;
	float birdHeight = 11 * h;
	//this is like a G point for the bird
	glm::vec3 G_bird = birdcorner + glm::vec3(birdHeight / 2, birdHeight / 2, 0);

	//create the backround and the floor
	modelBackAndFloor = glm::mat3(1);
	RenderMesh2D(meshes["floor"], shaders["VertexColor"], modelBackAndFloor);
	RenderMesh2D(meshes["back"], shaders["VertexColor"], modelBackAndFloor);

	//translate the bird up or down and rotate it with angularStepOY
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(G_bird.x, G_bird.y) * Transform2D::Rotate(angularStepOY) * Transform2D::Translate(-G_bird.x, -G_bird.y) *
		Transform2D::Translate(0, translateY);
	RenderMesh2D(meshes["prBird"], shaders["VertexColor"], modelMatrix);


	diffDown = 200;
	diffUp = 200;
	float rectHeight = 200;
	float rectWidth = 50;
	float rectDistance = 320;
	float deltaRectangle = 10;

	//these 4 points are the points of the rectangle which surround the bird 
	glm::vec2 leftDownCorner = glm::vec2(150 - 7 * h, 300 + translateY);
	glm::vec2 rightDownCorner = glm::vec2(150 + 9 * h, 300 + translateY);
	glm::vec2 leftUpCorner = glm::vec2(150 - 7 * h, 300 + translateY + 11 * h);
	glm::vec2 rightUpCorner = glm::vec2(150 + 9 * h, 300 + translateY + 11 * h);

	//generate new rectangles for upper side and down side 3 times from 4 when generateNewRectangleUpDown +=deltaTimeSeconds
	generateNewRectangleUpDown += deltaTimeSeconds;
	if (fmod(generateNewRectangleUpDown,4) < 3) {
		n++;
	}

	rectangleMatrixUp = glm::mat3(1);
	rectangleMatrixDown = glm::mat3(1);
	translateX -= deltaTimeSeconds * 230;

	rectangleMatrixUp *= Transform2D::Translate(translateX, 0);
	rectangleMatrixDown *= Transform2D::Translate(translateX, 0);
	//i generate the first down and upper rectangle here (not in for loop) because i don't want to scale the first two rectangles. 
	RenderMesh2D(meshes["rectangleDown"], shaders["VertexColor"], rectangleMatrixDown);
	RenderMesh2D(meshes["rectangleUpper"], shaders["VertexColor"], rectangleMatrixUp);
	currScore = score;
	if (!gameOver) {
		score = 0;
	}
	if (defaultStart == 0) {
		scoreDiff = 0;
	}
	for (int i = 0; i < n; i++)
	{
		//current position on Ox for every rectangle
		float currX = translateX + (i + 1) * rectDistance;
		//calculate the score in function of current position of every rectangle

		if (currX <= 0 && defaultStart == 0) {
			scoreDiff++;
		}
		if (currX <= 0 && gameOver == false && defaultStart >= 1)
		{
			score++;
			
		}
		//this step it was meant to alternate the height for upp and down rectangles
		//ScaleDown makes diffDown or diffUp smaller than their previous size.
		//ScaleUpper makes diffDown or diffUp bigger than their previous size.
		if (i % 4 < 2) {
			diffDown *= vectorScaleDown[i];
			diffUp *= vectorScaleUpper[i];
		}
		else
		{
			diffDown *= vectorScaleUpper[i];
			diffUp *= vectorScaleDown[i];
		}


		//conditions for bird to colide with the rectangle from downside
		if ((diffDown >= leftDownCorner.y || diffDown >= rightDownCorner.y ) &&
			((leftDownCorner.x >= currX && leftDownCorner.x <= currX + rectWidth ) ||
			(rightDownCorner.x >= currX && rightDownCorner.x <= currX + rectWidth)))
		{
			gameOver = true;

		}
		//conditions for bird to colide with the rectangle from upperside
		if ((720 - diffUp <= leftUpCorner.y || 720 - diffUp <= rightUpCorner.y) && ((leftUpCorner.x  >= currX && leftUpCorner.x <= currX + rectWidth) ||
			(rightUpCorner.x >= currX && rightUpCorner.x <= currX + rectWidth)))
		{
			gameOver = true;
		}
		//this is where i scale every rectangle and translate it with rectDistance from their left neighbour
		if (i % 4  < 2) {
			rectangleMatrixDown *= Transform2D::Scale(1, vectorScaleDown[i]) *  Transform2D::Translate(rectDistance, 0);
			if (currX >= -70 && currX <= 1280) {
				RenderMesh2D(meshes["rectangleDown"], shaders["VertexColor"], rectangleMatrixDown);
			}
			rectangleMatrixUp *= Transform2D::Translate(0, upperCorner.y) *
				Transform2D::Scale(1, vectorScaleUpper[i]) *
				Transform2D::Translate(0, -upperCorner.y) *
				Transform2D::Translate(rectDistance, 0);
			if (currX >= -70 && currX <= 1280) {
				RenderMesh2D(meshes["rectangleUpper"], shaders["VertexColor"], rectangleMatrixUp);
			}
		}
		else{
			rectangleMatrixDown *= Transform2D::Scale(1, vectorScaleUpper[i])*  Transform2D::Translate(rectDistance, 0);
			if (currX >= -70 && currX <= 1280) {
				RenderMesh2D(meshes["rectangleDown"], shaders["VertexColor"], rectangleMatrixDown);
			}
			rectangleMatrixUp *= Transform2D::Translate(0, upperCorner.y) *
				Transform2D::Scale(1, vectorScaleDown[i]) *
				Transform2D::Translate(0, -upperCorner.y) *
				Transform2D::Translate(rectDistance, 0);
			if (currX >= -70 && currX <= 1280) {
				RenderMesh2D(meshes["rectangleUpper"], shaders["VertexColor"], rectangleMatrixUp);
			}
		}

	

	}
	if (currScore < score && defaultStart > 1) {
		cout <<"Current score is: "<< currScore - scoreDiff << endl;
	}


}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE) {
		defaultStart++;
		if (defaultStart > 1) {
			pressSpace = true;
		}

		start = true;
	}
	else
	{
		pressSpace = false;
	}

}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
