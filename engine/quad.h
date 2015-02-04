#ifndef _QUAD_H_
#define _QUAD_H_

#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>

#include <vector>
#include <string>
#include <fstream>

extern glm::mat4 Ortho;

struct Vertex
{
	float fPositions[4];
	float fColours[4];
	float fUVs[2];
};

void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, glm::mat4 & mat);



class Quad
{
public:
	Quad();
	void Draw();
	void CreateSprite(const char* filename);
	void SetUVs(unsigned int spriteId, float topX, float topY, float bottomX, float bottomY);
	void DrawSprite();
	GLuint uiProgramFlat, MatrixIDFlat, uiProgramTextured; //shader programs
	~Quad(){};
private:
	Vertex* myShape;
	
	//GLuint uiTextureId;
	//GLuint texLoc;
	GLuint VBO;  //Vertex Buffer
	GLuint EBO;  // Element Buffer
	GLuint VAO;  // Vertex Attr
	float *orthographicProjection;
	
	GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
	GLuint CreateProgram(const char *a_vertex, const char *a_frag);
	float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);
	unsigned int loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP);

	glm::mat4 MVP;
};

#endif // !_QUAD_H_
