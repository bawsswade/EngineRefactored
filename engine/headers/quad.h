//////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------quad.h----------------------------------------------//
//																								//
//! This file creates quad, allocate memory on the buffer for it, and saves the data. 			//
//! The quad data includes shader data, vertex transforms from orthographic projection			//
//! Quad also initializes the OpenGL window.                                    					//
//                                                                           					//
// Created by: Wade Gushikuma                                                  					//
// Created on: 2/24/15                                                       					//
//                                                                           					//
//-------------------------------------------Notes----------------------------------------------//
//                                                                           					//
//	Quad only saves everythig to the VBO and does not make use of a VAO or EBO					//
//                                                                           					//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _QUAD_H_
#define _QUAD_H_

#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>

#include <vector>
#include <string>
#include <fstream>

//!	initialize maximum amount of sprites
const int MAXSPRITES = 30;

//!	gloabal variables for widndow width and height
extern int width, height;

//!	global variable for GLFW window
extern GLFWwindow* window;

//!	global matrix of a matrix  of size 4x4 for orhtographic projection calculation
extern glm::mat4 Ortho;

//!	holds data for each vertex of the quad
struct Vertex
{
	float fPositions[4];	//!<	x,y,z,w
	float fColours[4];		//!<	r,g,b,a
	float fUVs[2];			//!<	u,v
};

/*!
*	\brief		initilizes and creates glfw window with error checking
*	\param		takes in the name of window
*	\param		window width
*	\param		window height
*/
void Initialize(const char* windowTitle, int windowWidth, int windowHeight);

/*!
*	\brief		returns if the window should close
*/
bool FrameworkUpdate();


/*!
*	\brief		changes data of vertex points to an orthographic projection
*	\param		takes left, right, top, bottom, near, and far position and saves to mat
*/
void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, glm::mat4 & mat);


//////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------Quad Class--------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////
//! creates verticies and shaders for quad and stores them in the VBO
class Quad
{
public:
	Quad();
	GLuint VBO;				//!<	Vertex Buffer Object to store quad data
	Vertex rect[4];			//!<	vertex array that holds vertex data
	GLuint uiTextureId;		//!<	quad's texture id

	glm::mat4 MVP, Model, View;					//!<	matricies for matrix math
	glm::vec3 m_transate, m_scale, m_rotate;	//!<	vectors for transform math

	/*!
	*	\brief		enables shader program, vertex data, and texture to draw quad.
	*/
	void Draw();			
	
	~Quad(){};
private:
	//Vertex* myShape;

	//!	Shader Program Variables
	GLuint uiProgramFlat, MatrixIDFlat, uiProgramTextured;

	//!	pointer for orthographic projection
	float *orthographicProjection;	

	/*!
	*	\brief	creates shader from file
	*	\param	what type of shader
	*	\param	name of shader
	*/
	GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);

	/*!
	*	\breif		creates shader program
	*	\param	vertex shader
	*	\param	fragment shader
	*/
	GLuint CreateProgram(const char *a_vertex, const char *a_frag);

	/*!
	*	\brief		returns orthographic projection in an array
	*	\param		takes left, right, top, bottom, near, and far position and saves to mat
	*/
	float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);
};

#endif // !_QUAD_H_
