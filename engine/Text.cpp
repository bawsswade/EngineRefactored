#include "Text.h"

void TextFont::LoadDoc(const char* a_filename)
{
	tinyxml2::XMLDocument doc;  
	tinyxml2::XMLNode *rootNode, *currentNode;  //perculating pointers
	tinyxml2::XMLElement *childElement;  //pointer data
	doc.LoadFile(a_filename); // load the document
	rootNode = doc.FirstChildElement("font");// set the root node
	currentNode = rootNode;

	childElement = currentNode->FirstChildElement("common"); //perculate
	sheetW = childElement->IntAttribute("scaleW");
	sheetH = childElement->IntAttribute("scaleH");
	
	currentNode = rootNode; //reset pointer
	childElement = currentNode->FirstChildElement("pages")->FirstChildElement("page"); //percuate chain
	filename = (const char*)childElement->Attribute("file");

	currentNode = rootNode;  //reset pointer
	childElement = currentNode->FirstChildElement("chars")->FirstChildElement("char");
	int i;
	//extract data
	while (childElement != NULL)
	{
		i = (int)childElement->IntAttribute("id");
		sheet[i].width = (float)childElement->IntAttribute("width");
		sheet[i].height = (float)childElement->IntAttribute("height");
		sheet[i].x = (float)childElement->IntAttribute("x");
		sheet[i].y = (float)childElement->IntAttribute("y");
		childElement = childElement->NextSiblingElement();
	}
	this->textSprite.CreateSprite(filename);
}

void TextFont::DrawString(char letters, float x, float y)
{
	//optimize for mult letters
	//char let = '9';
	int asciiNum = (int)letters;
	this->textSprite.SetUVs(this->textSprite.SpriteQuad.uiTextureId, sheet[asciiNum].x / sheetW, (sheetH - sheet[asciiNum].y) / sheetH, ((sheet[asciiNum].x + sheet[asciiNum].width)) / sheetW, ((sheetH - sheet[asciiNum].y) - sheet[asciiNum].height) / sheetH);
	this->textSprite.SpriteQuad.Draw();
}