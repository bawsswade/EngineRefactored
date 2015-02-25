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
	this->startFrame = startIndex;
	this->endFrame = endIndex;
	this->frame = startFrame;
	this->frameSwitch = 0.0f;
	/*for (int i = startFrame; i <= endFrame; i++)
	{
	AniSprites.ScaleSprite((spriteList[i].x1 - spriteList[i].x0)*0.1f, (spriteList[i].y1 - spriteList[i].y0)* 0.1f);
	}*/
}

void Animator::Draw()
{
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, .5);
	glEnable(GL_ALPHA);

	this->previousTime = elapsedTime;
	this->elapsedTime = glfwGetTime();
	this->deltaTime = elapsedTime - previousTime;
	this->frameSwitch += deltaTime;
	this->AniSprites.SetUVs(spriteList[frame].id, spriteList[frame].x0 / 512.0f, (512.0f - spriteList[frame].y0) / 512.0f, spriteList[frame].x1 / 512.0f, (512.0f - spriteList[frame].y1) / 512.0f);
	
	this->AniSprites.SpriteQuad.Draw();

	if (this->frameSwitch > .075f) //fps: controls speed
	{
 		this->frame++;
		this->AniSprites.AdjustSprite();  //sets size back to start so it doesnt scale every frame FIX THIS!!
		this->AniSprites.ScaleSprite((spriteList[frame].x1 - spriteList[frame].x0)*0.1f, (spriteList[frame].y1 - spriteList[frame].y0)* 0.1f);
		this->frameSwitch = 0;
	}
	if (this->frame > this->endFrame)  //loops sprites
		this->frame = this->startFrame;	
}

void Animator::MoveSprite(int x, int y)
{
	this->AniSprites.MoveSprite(x, y);
}