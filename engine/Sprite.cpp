#include "Sprite.h"
//Sprite::Sprite()
//{
//
//	std::string vString = textFileReader("../resources/exampleVert.glsl");
//	std::string fString = textFileReader("../resources/exampleFrag.glsl");
//
//	const char* vs = vString.c_str();
//	const char* fs = fString.c_str();
//
//	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(VertexShader, 1, &vs, NULL);
//	glCompileShader(VertexShader);
//	printShaderInfoLog(VertexShader);
//
//	// Compile Fragment Shader
//	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(FragmentShader, 1, &fs, NULL);
//	glCompileShader(FragmentShader);
//	printShaderInfoLog(FragmentShader);
//
//
//	// Link Shaders into Shader Program
//	GLuint ShaderProgram = glCreateProgram();
//
//	glAttachShader(ShaderProgram, FragmentShader);
//	glAttachShader(ShaderProgram, VertexShader);
//
//	glLinkProgram(ShaderProgram);
//	printProgramInfoLog(ShaderProgram);
//	m_Quad.m_ShaderProgram = ShaderProgram;
//	glUseProgram(m_Quad.m_ShaderProgram);
//
//	m_UVData[0].U = 0.0f;
//	m_UVData[0].V = 0.0f;
//	m_UVData[1].U = 1.0f;
//	m_UVData[1].V = 0.0f;
//	m_UVData[2].U = 0.0f;
//	m_UVData[2].V = 1.0f;
//	m_UVData[3].U = 1.0f;
//	m_UVData[3].V = 1.0f;
//
//	glBindVertexArray(m_Quad.m_VAO);
//	glGenBuffers(1, &m_UVO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_UVO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(m_UVData), m_UVData, GL_STATIC_DRAW);
//
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_UVO);
//	GLint texAttrib = glGetAttribLocation(m_Quad.m_ShaderProgram, "texcoord");
//	glEnableVertexAttribArray(texAttrib);
//	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 2 * (sizeof(float)), 0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//}
Sprite::~Sprite()
{
}

void Sprite::Update(float a_DeltaTime)
{

}

void Sprite::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexId);
	glUniform1i(tex_location, 0);
	this->Draw();
}

void Sprite::LoadTexture(const char* a_pTexture)
{
	m_TexId = 0;


	glGenTextures(1, &m_TexId);
	glActiveTexture(GL_TEXTURE0);

	int width, height;
	unsigned char* image = SOIL_load_image(a_pTexture, &width, &height, 0, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, m_TexId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	tex_location = glGetUniformLocation(m_Quad.uiProgramTextured, "diffuseTexture");
}