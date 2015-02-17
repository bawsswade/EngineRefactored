#include "Animator.h"

void Animator::LoadAtlas(const char* a_filename)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;  //perculating pointers
	tinyxml2::XMLElement *childElement;  //pointer data
	doc.LoadFile(a_filename); // load the document
	rootNode = doc.FirstChildElement("atlas");// set the root node
	currentNode = rootNode;

	childElement = currentNode->ToElement();
	sheetW = childElement->IntAttribute("width");
	sheetH = childElement->IntAttribute("height");
	filename = (const char*)childElement->Attribute("sheet");

	childElement = currentNode->FirstChildElement("sprite");

	int i = 0;
	//extract data
	while (childElement != NULL)
	{
		sheetW = (float)childElement->IntAttribute("width");
		sheetH = (float)childElement->IntAttribute("height");
		spriteList[i].x0 = (float)childElement->IntAttribute("x0");
		spriteList[i].y0 = (float)childElement->IntAttribute("y0");
		spriteList[i].x1 = (float)childElement->IntAttribute("x1");
		spriteList[i].y1 = (float)childElement->IntAttribute("y1");
		spriteList[i].name = (const char*)childElement->Attribute("name");
		childElement = childElement->NextSiblingElement();
		i++;
	}  
	this->AniSprites.CreateSprite(filename);
}

void Animator::SetSprites(int startIndex, int endIndex)
{
	startFrame = startIndex;
	endFrame = endIndex;
	frame = startFrame;
}

void Animator::Draw()
{
	previousTime = elapsedTime;
	elapsedTime = glfwGetTime();
	deltaTime = elapsedTime - previousTime;
	frameSwitch += deltaTime;
	AniSprites.SetUVs(spriteList[frame].id, spriteList[frame].x0 / 512.0f, (512.0f - spriteList[frame].y0) / 512.0f, spriteList[frame].x1 / 512.0f, (512.0f - spriteList[frame].y1) / 512.0f);
	if (frameSwitch > .075f) //fps: controls speed
	{
		frame++;
		frameSwitch = 0;
	}
	if (frame > endFrame)  //loops sprites
		frame = startFrame;

	this->AniSprites.SpriteQuad.Draw();
}