#include "Text.h"

void TextFont::LoadDoc(const char* a_filename)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	//std::string str;
	doc.LoadFile(a_filename); // load the document
	rootNode = doc.FirstChildElement("font");// set the root node
	currentNode = rootNode;

	childElement = currentNode->FirstChildElement("common");
	sheetW = childElement->IntAttribute("scaleW");
	sheetH = childElement->IntAttribute("scaleH");
	
	currentNode = rootNode;
	childElement = currentNode->FirstChildElement("pages")->FirstChildElement("page");
	filename = (const char*)childElement->Attribute("file");

	currentNode = rootNode;
	childElement = currentNode->FirstChildElement("chars")->FirstChildElement("char");
	int i;
	while (childElement != NULL)
	{
		i = (int)childElement->IntAttribute("id");
		sheet[i].width = (float)childElement->IntAttribute("width");
		sheet[i].height = (float)childElement->IntAttribute("height");
		sheet[i].x = (float)childElement->IntAttribute("x");
		sheet[i].y = (float)childElement->IntAttribute("y");
		//sheet[i].cID = (int)childElement->Attribute("char id");
		childElement = childElement->NextSiblingElement();
	}
	test.CreateSprite(filename);
	
}

void TextFont::DrawString(char letters, float x, float y)
{
	char let = '9';
	int asciiNum = (int)let;
	test.SetUVs(test.Shape.uiTextureId, sheet[asciiNum].x / sheetW, (sheetH - sheet[asciiNum].y) / sheetH, ((sheet[asciiNum].x + sheet[asciiNum].width)) / sheetW, ((sheetH - sheet[asciiNum].y) - sheet[asciiNum].height) / sheetH);
	test.Shape.Draw();
}