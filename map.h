#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

class Map
{
public:
	Map();
	~Map();

public:
	int nWidth;
	int nHeight;
	const char* sName;
	sf::Sprite* pSprite;

	int GetIndex(int x, int y);
	bool GetSolid(int x, int y);
	bool Create(const char* fileName, sf::Sprite* sprite, const char* name);

private:
	int *m_indicies = nullptr;
	bool *m_solids = nullptr;
};

