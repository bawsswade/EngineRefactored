#ifndef _TEXT_H_
#define _TEXT_H_

#include <TINYXML2\tinyxml2.h>
#include "quad.h"
#include "Sprite.h"
#include <iostream>
#include <string>

const int MAXTEXT = 256;

struct TextSheet
{
	float width, height;  //size
	int x, y;             //position on sheet
	int cID;              //ascii num
};

class TextFont
{
public:
	TextFont(){};
	Quad arrSprite[MAXSPRITES];

	Sprite test;
	
	void LoadDoc(const char* a_filename);
	void DrawString(char letters, float x, float y);

	TextSheet sheet[MAXTEXT];
	~TextFont(){};
private:
	const char* filename;
};



#endif 