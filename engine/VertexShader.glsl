#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec2 vertexUV;

uniform mat4 MVP;

smooth out vec4 vertColour;
out vec2 UV;

void main()
{
	vertColour = colour;
	UV = vertexUV;

	//vec4 scaledPosition = MVP * position;

	gl_Position = MVP *(vec4 (position, 1.0));
}