#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "quad.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

typedef glm::mat4 mat4;
typedef glm::vec3 vec3;

class Sprite
{
public:
	Sprite(){};
	Quad SpriteQuad;
	void CreateSprite(const char* filename);
	void SetUVs(unsigned int spriteId, float topX, float topY, float bottomX, float bottomY);
	void Draw();
	void MoveSprite(float x, float y);
	void ScaleSprite(float x, float y);
	void AdjustSprite();
	mat4 position;

	~Sprite(){};
private:
	void loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP);
};

#endif