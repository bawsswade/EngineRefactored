#include "Text.h"

void TextFont::LoadDoc(const char* a_filename)
{
	filename = a_filename;
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	//std::string str;
	doc.LoadFile(filename); // load the document
	rootNode = doc.FirstChildElement("font");// set the root node
	currentNode = rootNode;

	//currentNode = rootNode->FirstChild(); // set the current node to the root nodes first child
	childElement = currentNode->FirstChildElement();
	int i = 0;
	while (childElement != NULL)
	{
		sheet[i].width = (float)childElement->IntAttribute("width");
		sheet[i].height = (float)childElement->IntAttribute("height");
		sheet[i].x = (int)childElement->Attribute("x");
		sheet[i].y = (int)childElement->Attribute("y");
		sheet[i].cID = (int)childElement->Attribute("char id");
		childElement = childElement->NextSiblingElement();
		i++;
	}
	test.CreateSprite("textfont_0.png");
	test.SetUVs(test.Shape.uiTextureId, 164.0f / 170.0f, (84.0f) / 170.0f, (164.0f + 4.0f) / 170.0f, ((84.0f - 20.0f)) / 170.0f);
}

void TextFont::DrawString(char letters, float x, float y)
{
	
	test.Shape.Draw();
}