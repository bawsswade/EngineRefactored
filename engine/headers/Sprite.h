//////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------Sprite.h---------------------------------------------//
//																								//
// This file creates a quad with a image texture										 		//
// Texture can be draw with soecific UVs														//
// It also has basic functionality including translating and scaling, 							//
//                                                                           					//
// Created by: Wade Gushikuma                                                  					//
// Created on: 2/24/15                                                       					//
//                                                                           					//
//-------------------------------------------Notes----------------------------------------------//
//                                                                           					//
// AdjustSprite() added to reset sprite size because animation is fucked up and					//
// scales each
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "quad.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

//!	type defining glm mat4 for ease of use
typedef glm::mat4 mat4;
//!	type defining glm vec3 for ease of use
typedef glm::vec3 vec3;

//////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------Sprite Class--------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////
//!	reads and creates texture for a quad
class Sprite
{
public:
	Sprite(){};			//	Sprite constructor
	Quad SpriteQuad;	//!<	creates quad to attach texture
	//mat4 position;	//	holds sprite position in matrix. will used for matrix math

	/*!
	*	\brief		enables shader program, vertex data, and texture to draw quad
	*	\param		file name of texture
	*/
	void CreateSprite(const char* filename);

	/*!
	*	\brief		sets the uvs of the texture being used
	*	\param		spriteID, top x and y, bottom x and y
	*/
	void SetUVs(unsigned int spriteId, float topX, float topY, float bottomX, float bottomY);

	/*!
	*	\brief		calls quad.draw()
	*/
	void Draw();

	/*!
	*	\brief		ability to adjust the x position adn y position of sprite
	*	\param		x and y translation
	*/
	void MoveSprite(float x, float y);

	/*
	*	\brief		ability to scale the sprite
	*	\param		scale width by x and scale height by y
	*/
	void ScaleSprite(float x, float y);
	
	/*
	*	\brief		sets sprite to original scale and position
	*/
	void AdjustSprite();
	

	~Sprite(){};		//	destructor
private:
	/*
	*	\brief		loads texture of a_pFilename
	*/
	void loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP);
};

#endif