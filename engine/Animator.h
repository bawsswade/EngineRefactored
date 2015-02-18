#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include <TINYXML2\tinyxml2.h>
#include "Sprite.h"

const int MAXSPRITE = 30;


struct SpriteData
{
	unsigned int id;
	float x0, y0, x1, y1; //uvs
	//float width, height; 
	const char* name;
};

struct Atlas
{
	float width, height;
	const char* name;
};

class Animator
{
public:
	Animator(){};
	SpriteData spriteList[MAXSPRITE];
	Sprite AniSprites;

	void LoadAtlas(const char* a_filename);
	void SetSprites(int startIndex, int endIndex);
	void Draw();
	void MoveSprite(int x, int y);

	double deltaTime;
	double elapsedTime = 0;
	double previousTime = 0;
	double frameSwitch = 10;
	int startFrame;
	int frame = 11;
	int endFrame;
	int sheetW, sheetH;
	~Animator(){};
private:
	const char* filename;
	
};

#endif