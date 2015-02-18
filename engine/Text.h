#ifndef _TEXT_H_
#define _TEXT_H_

#include <TINYXML2\tinyxml2.h>
#include "quad.h"
#include "Sprite.h"
#include <iostream>
#include <string>
#include <map>

const int MAXTEXT = 256;
//typedef std::string string;
using std::string;
using std::map;

struct TextSheet
{
	float width, height;  //size
	float x, y;             //position on sheet
};

class TextFont
{
public:
	TextFont(){};
	//Quad arrSprite[MAXSPRITES];

	
	const char* filename;

	void LoadDoc(const char* a_filename);
	void DrawString();
	void CreateString(string letters, float x, float y);
	void MoveSprite(float x, float y);
	
	map<int, TextSheet> sheet;
	//TextSheet sheet[MAXTEXT]; //arr ID = ascii number
	~TextFont(){};
private:
	int strsize;
	float offset = -10;
	int sheetW, sheetH;
	char c[15];
	int ascii[15];
	Sprite textSprite[15];
};



#endif 