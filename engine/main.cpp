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

	Quad *rect = new Quad;

	//loop until window closes
	while (!glfwWindowShouldClose(window))
	{
		//DRAW SHIT!
		glClearColor(0.1f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		rect->Draw();

		//spaw front and back buffers
		glfwSwapBuffers(window);

		//poll for and process events
		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}