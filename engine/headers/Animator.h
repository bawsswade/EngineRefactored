//////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------Animator.h---------------------------------------------//
//																								//
//! This file takes in multiple sprites and outputs them as an animation						//
//                                                                           					//
// Created by: Wade Gushikuma                                                  					//
// Created on: 2/24/15                                                       					//
//                                                                           					//
//-------------------------------------------Notes----------------------------------------------//
//                                                                           					//
//	AdjustSprite() added to reset sprite size because animation is fucked up and				//
//	scales each. So animated sprites can't move.....																					//
//                                                                           					//
//////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include <TINYXML2\tinyxml2.h>
#include "Sprite.h"

//!	sets global for max amount of sprites in an animation 
const int MAXSPRITE = 30;

//!	holds sprite UV data
struct SpriteData
{
	unsigned int id;		//!<	sprite iD
	float x0, y0, x1, y1;	//!<	uvs
	//float width, height; 
	const char* name;		//!<	sprite name
};

//!	holds atlas data
struct Atlas
{
	float width, height;	//!<	sheet width and height
	const char* name;		//!<	sheet name
};

//////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------Animator Class---------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////
//! stores atlas texture and changes sprite UV accordingly to perform animation
class Animator
{
public:
	Animator(){};
	SpriteData spriteList[MAXSPRITE];	//!<	list of sprite uvs
	Sprite AniSprites;					//!<	initialize sprite for animations
	double deltaTime;					//!<	stores delta time
	double elapsedTime = 0;				//!<	elapsed time since last previousTime 
	double previousTime = 0;			//!<	sets start time forswitching frames
	double frameSwitch = 10;			//!<	when to switch frame
	int startFrame;						//!<	starting frame
	int frame = 11;						//!<	frame iterator
	int endFrame;						//!<	end frame
	int sheetW, sheetH;					//!<	sheet width and height

	/*!
	*	\brief		using timyxml, loads uv data into spriteList
	*	\param		takes in the filename of atlas
	*/
	void LoadAtlas(const char* a_filename);

	/*!
	*	\brief		sets which uvs to use
	*	\param		start and end index to use
	*/
	void SetSprites(int startIndex, int endIndex);

	/*!
	*	\brief		cycles through spriteList and changes UVs every frame
	*/
	void Draw();

	/*!
	*	\brief		translates sprite
	*	\param		translate by x amount and y amount
	*/
	void MoveSprite(int x, int y);

	~Animator(){};
private:
	const char* filename;	//	holds filename to open when reading from xml file
	
};

#endif