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

const int MAXSPRITES = 30;
extern int width, height;
extern GLFWwindow* window;
extern glm::mat4 Ortho;

struct Vertex
{
	float fPositions[4];
	float fColours[4];
	float fUVs[2];
};


void Initialize(const char* windowTitle, int windowWidth, int windowHeight);

bool FrameworkUpdate();

void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, glm::mat4 & mat);

class Quad
{
public:
	Quad();
	GLuint VBO;
	Vertex rect[4];
	GLuint uiTextureId;

	glm::mat4 MVP, Model, View;
	glm::vec3 m_transate, m_scale, m_rotate;
	

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
