#include "quad.h"
#include "Sprite.h"
#include "Text.h"

int main()
{
	Initialize("Test", 1024.0f, 720.0f);
	Orthographic(0.f, (float)width, (float)height, 0.f, -1.f, 1.f, Ortho);

	Sprite *testSprite = new Sprite;

	//testSprite->CreateSprite("smile.png");
	//testSprite->SetUVs(testSprite->SpriteQuad.uiTextureId, 0, 1, 0.5f, 0.5f); 
	/*Quad *rect = new Quad;
	rect->CreateSprite("smile.png");
	rect->SetUVs(rect->uiTextureId, 0, 1, 0.5f, 0);*/
	
	TextFont text;
	text.LoadDoc("textfont.xml");
	
	//loop until window closes
	while (!FrameworkUpdate())
	{
		//DRAW SHIT!
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//testSprite->SpriteQuad.Draw();
		text.DrawString('W', 1, 2);

		//spaw front and back buffers
		glfwSwapBuffers(window);

		//poll for and process events
		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}