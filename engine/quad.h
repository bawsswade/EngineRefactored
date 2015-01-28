#ifndef _QUAD_H_
#define _QUAD_H_

#include <glew.h>
#include <wglew.h>
#include <glfw3.h>
#include <SOIL.h>
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

class Quad
{
public:
	Quad();
	GLuint uiProgramFlat, MatrixIDFlat;
	GLuint VBO;
	void Draw();
	float *orthographicProjection;

	~Quad(){};
private:
	GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
	GLuint CreateProgram(const char *a_vertex, const char *a_frag);
	float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);
};

#endif // !_QUAD_H_
