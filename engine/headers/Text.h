#ifndef _TEXT_H_
#define _TEXT_H_

#include <TINYXML2\tinyxml2.h>
#include "quad.h"
#include "Sprite.h"
//////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------Animator.h-----------------------------------------------//
//																								//
//! This file creates quad, allocate memory on the buffer for it, and saves the data. 			//
//! The quad data includes shader data, vertex transforms from orthographic projection			//
//! Quad also initializes the OpenGL window.                                    				//
//                                                                           					//
// Created by: Wade Gushikuma                                                  					//
// Created on: 2/24/15                                                       					//
//                                                                           					//
//-------------------------------------------Notes----------------------------------------------//
//                                                                           					//
//	Quad only saves everythig to the VBO and does not make use of a VAO or EBO					//
//                                                                           					//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <map>

//const int MAXTEXT = 256;
//typedef std::string string;
using std::string;
using std::map;

//!	stores each letter's data
struct TextSheet
{
	float width, height;	//!<	width and height of letter
	float x, y;             //!<	position of letter on sheet
};

//!	loads and stores an atlas of letters to draw a string 
class TextFont
{
public:
	TextFont(){};
	//Quad arrSprite[MAXSPRITES];
	
	const char* filename;		//!<	stores filename of texture
	map<int, TextSheet> sheet;	//!<	map of letter data

	/*!
	*	\brief		extracts data from xml file
	*	\param		takes in filename to be loaded
	*/
	void LoadDoc(const char* a_filename);

	/*!
	*	\brief		draws all character sprites
	*/
	void DrawString();

	/*!
	*	\brief		creates sprite for each char, sets uvs to be used, and scales and translates accordingly
	*	\param		string to be drawn
	*	\param		x and y location to be drawn
	*/
	void CreateString(string letters, float x, float y);

	/*!
	*	\brief		moves sprites
	*	\param		translates by x and y amount
	*/
	void MoveSprite(float x, float y);
	
	
	//TextSheet sheet[MAXTEXT]; //arr ID = ascii number
	~TextFont(){};
private:
	int strsize;			//	stores size of string drawn
	float offset = 0;		//	initialize offset for sprite letters
	int sheetW, sheetH;		//	sheet width and height
	char c[15];				//	char array to store char from string
	int ascii[15];			//	stores ascii num of char
	Sprite textSprite[15];	//	stores sprite data of char
};

#endif 