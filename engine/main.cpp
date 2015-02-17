#include "quad.h"
#include "Sprite.h"
#include "Text.h"
#include "Animator.h"

int main()
{
	Initialize("Test", 1024.0f, 720.0f);
	Orthographic(0.f, (float)width, (float)height, 0.f, -1.f, 1.f, Ortho);

	//Sprite w/UVS
	Sprite s;
	s.CreateSprite("smile.png");
	s.SetUVs(s.SpriteQuad.uiTextureId, 0, 1, 0.5f, 0.5f); 

	//Animation
	Animator a;
	a.LoadAtlas("MegamanXSheet.xml");
	a.SetSprites(11, 20);

	//Text
	TextFont text;
	text.LoadDoc("textfont.xml");
	
	//loop until window closes
	while (!FrameworkUpdate())
	{
		//DRAW SHIT!
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		s.Draw();
		//text.DrawString('W', 1, 2);
		//a.Draw();

		//spaw front and back buffers
		glfwSwapBuffers(window);

		//poll for and process events
		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}