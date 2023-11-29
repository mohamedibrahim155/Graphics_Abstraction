#pragma once

#include <string>
#include "Renderer.h"
#include <vector>



#include <iostream>


class Texture
{
public:
	Texture() {}
	Texture(const char* filePath);
	~Texture() {}
	unsigned int id;
	const char* path;
	std::string type;
	void LoadTexture(const char* filePath, std::string _type);

	unsigned int TextureFromFile(const char* path, const std::string& directory);


private:
	unsigned int loadTexture(char const* path);
};