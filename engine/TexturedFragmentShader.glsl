#version 330

smooth in vec4 vertColour;
in vec2 UV;

out vec4 outputColour;

//uniform sampler2D myTextureSampler;

void main()
{
	UV;
	//outputColour = texture(myTextureSampler, UV).rgba * vertColour;
	outputColour = vertColour;
}