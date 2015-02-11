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
	float x, y;             //position on sheet
};

class TextFont
{
public:
	TextFont(){};
	Quad arrSprite[MAXSPRITES];

	Sprite textSprite;
	
	void LoadDoc(const char* a_filename);
	void DrawString(char letters, float x, float y);
	
	TextSheet sheet[MAXTEXT]; //arr ID = ascii number
	~TextFont(){};
private:
	const char* filename;
	int sheetW, sheetH;
	
};



#endif 