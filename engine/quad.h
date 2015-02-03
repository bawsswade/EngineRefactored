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

class Quad
{
public:
	Quad();
	void Draw();
	void CreateSprite(const char* filename);
	void SetUVs(unsigned int spriteId, float topX, float topY, float bottomX, float bottomY);
	~Quad(){};
private:
	Vertex* myShape;
	GLuint uiProgramFlat, MatrixIDFlat, uiProgramTextured;
	GLuint uiTextureId;
	GLuint VBO;
	float *orthographicProjection;
	GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
	GLuint CreateProgram(const char *a_vertex, const char *a_frag);
	float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);
	unsigned int loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP);
};

#endif // !_QUAD_H_
