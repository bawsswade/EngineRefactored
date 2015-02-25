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
	this->sheetW = childElement->IntAttribute("scaleW");
	this->sheetH = childElement->IntAttribute("scaleH");
	
	currentNode = rootNode; //reset pointer
	childElement = currentNode->FirstChildElement("pages")->FirstChildElement("page"); //percuate chain
	this->filename = childElement->Attribute("file");


	currentNode = rootNode;  //reset pointer
	childElement = currentNode->FirstChildElement("chars")->FirstChildElement("char");
	int i;
	//extract data
	while (childElement != NULL)
	{
		i = (int)childElement->IntAttribute("id");
		this->sheet[i].width = (float)childElement->IntAttribute("width");
		this->sheet[i].height = (float)childElement->IntAttribute("height");
		this->sheet[i].x = (float)childElement->IntAttribute("x");
		this->sheet[i].y = (float)childElement->IntAttribute("y");
		childElement = childElement->NextSiblingElement();
	}
	//this->textSprite.CreateSprite(filename);
}

void TextFont::CreateString(string letters, float x, float y)
{

	filename = "testFont_0.png";  //because for some reason filename gets corrupted after LoadDoc
	strcpy_s(c, letters.c_str());
	strsize = letters.length();

	for (int i = 0; i < strsize; i++)
	{
		ascii[i] = (int)c[i];
		this->textSprite[i].CreateSprite(filename);
		this->textSprite[i].SetUVs(this->textSprite[i].SpriteQuad.uiTextureId, sheet[ascii[i]].x / sheetW, (sheetH - sheet[ascii[i]].y) / sheetH, ((sheet[ascii[i]].x + sheet[ascii[i]].width)) / sheetW, ((sheetH - sheet[ascii[i]].y) - sheet[ascii[i]].height) / sheetH);
		this->textSprite[i].ScaleSprite(this->sheet[ascii[i]].width * 0.1f, this->sheet[ascii[i]].height * 0.1f);
		if (i == 1) //because the offset is fucked up for the first one
		{
			//offset += 12.0f;
		}
		
		if (i > 0) //offset is fucked up so FIX THIS too
		{
			offset += this->sheet[ascii[i]].width + (this->sheet[ascii[i - 1]].width);
		}
		this->textSprite[i].MoveSprite(offset + x, y);
		
	}
	
	//optimize for mult letters
	//int asciiNum = (int)letters;
	//this->textSprite.SetUVs(this->textSprite.SpriteQuad.uiTextureId, sheet[asciiNum].x / sheetW, (sheetH - sheet[asciiNum].y) / sheetH, ((sheet[asciiNum].x + sheet[asciiNum].width)) / sheetW, ((sheetH - sheet[asciiNum].y) - sheet[asciiNum].height) / sheetH);
	//this->textSprite.SpriteQuad.Draw();
}

void TextFont::DrawString()
{
	glEnable(GL_BLEND);
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, .5);
	glEnable(GL_ALPHA);
	//glEnable(GL_CULL_FACE); // cull face
	//glCullFace(GL_BACK); // cull back face
	//glFrontFace(GL_CW); // GL_CCW for counter clock-wise
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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