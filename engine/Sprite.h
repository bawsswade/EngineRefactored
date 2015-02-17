#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "quad.h"

class Sprite
{
public:
	Sprite(){};
	Quad SpriteQuad;
	void CreateSprite(const char* filename);
	void SetUVs(unsigned int spriteId, float topX, float topY, float bottomX, float bottomY);
	void Draw();
	void MoveSprite(float x, float y);

	~Sprite(){};
private:
	void loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP);
};

#endif