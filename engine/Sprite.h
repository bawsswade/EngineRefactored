#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "Quad.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	Quad m_Quad;
	GLuint m_TexId;
	GLuint tex_location;
	GLuint m_UVO;

	void Update(float a_DeltaTime);
	void Draw();
	void LoadTexture(const char* a_pTexture);
private:
};


#endif  //_SPRITE_H_
