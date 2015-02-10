#include "quad.h"
#include "Sprite.h"
#include "Text.h"

int main()
{
	//Initialize GLFW
	if (!glfwInit())
		return -1;

	//create window 
	GLFWwindow* window;
	window = glfwCreateWindow(1024, 720, "A$$teroids", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//make  window's context current
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		//ohh no it didnt start up!
		glfwTerminate();
		return -1;
	}
	
	Sprite *testSprite = new Sprite;

	//testSprite->CreateSprite("smile.png");
	//testSprite->SetUVs(testSprite->Shape.uiTextureId, 0, 1, 0.5f, 0.5f); 
	/*Quad *rect = new Quad;
	rect->CreateSprite("smile.png");
	rect->SetUVs(rect->uiTextureId, 0, 1, 0.5f, 0);*/

	TextFont text;
	text.LoadDoc("textfont.xml");

	//loop until window closes
	while (!glfwWindowShouldClose(window))
	{
		//DRAW SHIT!
		glClearColor(0.0f, 0.1f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//testSprite->Shape.Draw();
		text.DrawString('a', 1, 2);

		//spaw front and back buffers
		glfwSwapBuffers(window);

		//poll for and process events
		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}