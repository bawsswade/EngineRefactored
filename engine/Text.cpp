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
	filename = childElement->Attribute("file");


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
	//this->textSprite.CreateSprite(filename);
}

void TextFont::CreateString(string letters, float x, float y)
{
	filename = "textfont_0.png";
	strcpy_s(c, letters.c_str());
	strsize = letters.length();

	for (int i = 0; i < strsize; i++)
	{
		ascii[i] = (int)c[i];
		this->textSprite[i].CreateSprite(filename);
		this->textSprite[i].SetUVs(this->textSprite[i].SpriteQuad.uiTextureId, sheet[ascii[i]].x / sheetW, (sheetH - sheet[ascii[i]].y) / sheetH, ((sheet[ascii[i]].x + sheet[ascii[i]].width)) / sheetW, ((sheetH - sheet[ascii[i]].y) - sheet[ascii[i]].height) / sheetH);
		if (i > 0)
		{
			//offset += 50.0f;
			offset += this->sheet[ascii[i]].width + (this->sheet[ascii[i - 1]].width /2);
			this->textSprite[i].MoveSprite(offset, 0);
		}
	}
	//optimize for mult letters
	//int asciiNum = (int)letters;
	//this->textSprite.SetUVs(this->textSprite.SpriteQuad.uiTextureId, sheet[asciiNum].x / sheetW, (sheetH - sheet[asciiNum].y) / sheetH, ((sheet[asciiNum].x + sheet[asciiNum].width)) / sheetW, ((sheetH - sheet[asciiNum].y) - sheet[asciiNum].height) / sheetH);
	//this->textSprite.SpriteQuad.Draw();
}

void TextFont::DrawString()
{
	for (int i = 0; i < strsize; i++)
	{
		this->textSprite[i].SpriteQuad.Draw();
	}
}

void TextFont::MoveSprite(float x, float y)
{
	for (int i = 0; i < 15; i++)
		this->textSprite[i].MoveSprite(x, y);
}