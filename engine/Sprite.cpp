#include "Sprite.h"

void Sprite::CreateSprite(const char* filename)
{
	int width = 50, height = 50, bpp = 4;  //default size
	loadTexture(filename, width, height, bpp);
}

void Sprite::SetUVs(unsigned int spriteId, float topX, float topY, float bottomX, float bottomY)
{
	glBindBuffer(GL_ARRAY_BUFFER, SpriteQuad.VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 4, NULL, GL_STATIC_DRAW);

	this->SpriteQuad.rect[0].fUVs[0] = bottomX; //top right
	this->SpriteQuad.rect[0].fUVs[1] = topY;
	this->SpriteQuad.rect[1].fUVs[0] = bottomX; //bottom right
	this->SpriteQuad.rect[1].fUVs[1] = bottomY;
	this->SpriteQuad.rect[2].fUVs[0] = topX; //bottom left
	this->SpriteQuad.rect[2].fUVs[1] = bottomY;
	this->SpriteQuad.rect[3].fUVs[0] = topX; //top left
	this->SpriteQuad.rect[3].fUVs[1] = topY;


	//allocate space on graphics card
	GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	// copy data to graphics card 
	memcpy(vBuffer, SpriteQuad.rect, sizeof(Vertex)* 4);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP)
{
	SpriteQuad.uiTextureId = 0;
	//check file exists
	if (a_pFilename != nullptr)
	{
		//read in image data from file
		unsigned char* pImageData = SOIL_load_image(a_pFilename, &a_iWidth, &a_iHeight, &a_iBPP, SOIL_LOAD_AUTO);

		//check for successful read
		if (pImageData)
		{
			//create opengl texture handle
			SpriteQuad.uiTextureId = SOIL_create_OGL_texture(pImageData, a_iWidth, a_iHeight, a_iBPP,
				SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
			//clear what was read in from file now that it is stored in the handle
			SOIL_free_image_data(pImageData);
		}

		//check for errors
		if (SpriteQuad.uiTextureId == 0)
		{
			std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
		}
		//return Shape.uiTextureId;
	}
}

void Sprite::Draw()
{
	this->SpriteQuad.Draw();
}

void Sprite::MoveSprite(float x, float y)
{

}