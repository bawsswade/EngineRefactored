#ifndef _QUAD_H_
#define _QUAD_H_

#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>
#include <iostream>

#include <vector>
#include <string>
#include <fstream>

struct Vertex
{
	float fPositions[4];
	float fColours[4];
	float fUVs[2];
};

const int MAXSPRITES = 30;

class Quad
{
public:
	Quad();
	GLuint VBO;
	Vertex myShape[4];
	GLuint uiTextureId;

	void Draw();
	
	~Quad(){};
private:
	//Vertex* myShape;
	GLuint uiProgramFlat, MatrixIDFlat, uiProgramTextured;

	
	float *orthographicProjection;
	GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
	GLuint CreateProgram(const char *a_vertex, const char *a_frag);
	float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);
	
};

#endif // !_QUAD_H_
