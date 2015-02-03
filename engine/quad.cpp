#include "quad.h"

Quad::Quad()
{
	glGenBuffers(1, &VBO);

	Vertex* myShape = new Vertex[4];
	myShape[0].fPositions[0] = 1024 / 2.0 + 100;
	myShape[0].fPositions[1] = 720 / 2.0 + 100;
	myShape[1].fPositions[0] = 1024 / 2.0 + 100.0;
	myShape[1].fPositions[1] = 720 / 2.0 - 100.0f;
	myShape[2].fPositions[0] = 1024 / 2.0 - 100.0f;
	myShape[2].fPositions[1] = 720 / 2.0 - 100.0f;
	myShape[3].fPositions[0] = 1024 / 2.0 - 100.0f;
	myShape[3].fPositions[1] = 720 / 2.0 + 100.0f;
	for (int i = 0; i < 4; i++)
	{
		myShape[i].fPositions[2] = 0.0f;
		myShape[i].fPositions[3] = 1.0f;
		myShape[i].fColours[0] = 1.0f;
		myShape[i].fColours[1] = 1.0f;
		myShape[i].fColours[2] = 1.0f;
		myShape[i].fColours[3] = 1.0f;
	}
	//set up the UVs
	myShape[0].fUVs[0] = 1.0f; //top right
	myShape[0].fUVs[1] = 1.0f;
	myShape[1].fUVs[0] = 1.0f; //bottom right
	myShape[1].fUVs[1] = 0.0f;
	myShape[2].fUVs[0] = 0.0f; //bottom left
	myShape[2].fUVs[1] = 0.0f;
	myShape[3].fUVs[0] = 0.0f; //top left
	myShape[3].fUVs[1] = 1.0f;
	if (VBO != 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 4, NULL, GL_STATIC_DRAW);

		//allocate space on graphics card
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		// copy data to graphics card
		memcpy(vBuffer, myShape, sizeof(Vertex)* 4);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	//create shader program
	uiProgramFlat = CreateProgram("VertexShader.glsl", "FlatFragmentShader.glsl");

	//create texture program
	uiProgramTextured = CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");

	//find the position of the matrix variable in the shader so we can send info there later
	MatrixIDFlat = glGetUniformLocation(uiProgramFlat, "MVP");

	//set up the mapping of the screen to pixel co-ordinates.
	orthographicProjection = getOrtho(0, 1024, 0, 720, 0, 100);

	

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Quad::Draw()
{
	//enable shaders
	//glUseProgram(uiProgramFlat);
	glUseProgram(uiProgramTextured);

	//send our orthographic projection info to the shader
	glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

	//enable the vertex array state, since we're sending in an array of vertices
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// bindings: vbo, ibo, texture
	glBindTexture(GL_TEXTURE_2D, uiTextureId);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	//specify where our vertex array is, how many components each vertex has, 
	//the data type of each component and whether the data is normalised or not
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);  // position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));  // color
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 8));  // texture UVs

	glDrawArrays(GL_QUADS, 0, 4);
	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


GLuint Quad::CreateShader(GLenum a_eShaderType, const char *a_strShaderFile)
{
	std::string strShaderCode;
	//open shader file
	std::ifstream shaderStream(a_strShaderFile);
	//if that worked ok, load file line by line
	if (shaderStream.is_open())
	{
		std::string Line = "";
		while (std::getline(shaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();

	//create shader ID
	GLuint uiShader = glCreateShader(a_eShaderType);
	//load source code
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);

	//compile shader
	glCompileShader(uiShader);

	//check for compilation errors and output them
	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);
	if (iStatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (a_eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return uiShader;
}

GLuint Quad::CreateProgram(const char *a_vertex, const char *a_frag)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint uiProgram = glCreateProgram();

	//attach shaders
	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);

	//link program
	glLinkProgram(uiProgram);

	//check for link errors and output them
	GLint status;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	return uiProgram;
}

float* Quad::getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar)
{
	//to correspond with mat4 in the shader
	//ideally this function would be part of your matrix class
	//however I wasn't willing to write your matrix class for you just to show you this
	//so here we are in array format!
	//add this to your matrix class as a challenge if you like!
	float* toReturn = new float[12];
	toReturn[0] = 2.0 / (right - left);;
	toReturn[1] = toReturn[2] = toReturn[3] = toReturn[4] = 0;
	toReturn[5] = 2.0 / (top - bottom);
	toReturn[6] = toReturn[7] = toReturn[8] = toReturn[9] = 0;
	toReturn[10] = 2.0 / (a_fFar - a_fNear);
	toReturn[11] = 0;
	toReturn[12] = -1 * ((right + left) / (right - left));
	toReturn[13] = -1 * ((top + bottom) / (top - bottom));
	toReturn[14] = -1 * ((a_fFar + a_fNear) / (a_fFar - a_fNear));
	toReturn[15] = 1;
	return toReturn;
}

void Quad::CreateSprite(const char* filename)
{
	int width = 50, height = 50, bpp = 4;  //default size
	this->uiTextureId = this->loadTexture(filename, width, height, bpp);
}

unsigned int Quad::loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP)
{
	unsigned int uiTextureID = 0;
	//check file exists
	if (a_pFilename != nullptr)
	{
		//read in image data from file
		unsigned char* pImageData = SOIL_load_image(a_pFilename, &a_iWidth, &a_iHeight, &a_iBPP, SOIL_LOAD_AUTO);

		//check for successful read
		if (pImageData)
		{
			//create opengl texture handle
			uiTextureID = SOIL_create_OGL_texture(pImageData, a_iWidth, a_iHeight, a_iBPP,
				SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
			//clear what was read in from file now that it is stored in the handle
			SOIL_free_image_data(pImageData);
		}

		//check for errors
		if (uiTextureID == 0)
		{
			std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
		}
		return uiTextureID;
	}
}