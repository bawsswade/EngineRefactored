#include "quad.h"

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


	Orthographic(0.f, (float)1024, (float)720, 0.f, -1.f, 1.f, Ortho);

	Quad *rect = new Quad;

	//rect->CreateSprite("smile.png");
	//rect->SetUVs(uiTextureId, 0, 1, 0.5f, 0);

	//loop until window closes
	while (!glfwWindowShouldClose(window))
	{
		//DRAW SHIT!
		glClearColor(0.1f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		rect->DrawSprite();

		//spaw front and back buffers
		glfwSwapBuffers(window);

		//poll for and process events
		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}