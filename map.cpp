#include "map.h"

Map::Map() {
	nHeight = 0;
	nWidth = 0;
	sName = nullptr;
	pSprite = nullptr;
	m_indicies = nullptr;
	m_solids = nullptr;
}

Map::~Map() {
	//delete[] m_indicies;
	//delete[] m_solids;
}

int Map::GetIndex(int x, int y) {
	if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
		return m_indicies[x + y * nWidth];
	else
		return 0;
}

bool Map::GetSolid(int x, int y) {
	if (x >= 0 && x < nWidth*16 && y >= 0 && y < nHeight*16)
		return m_solids[x + y * nWidth];
	else
		return 0;
}

bool Map::Create(const char* fileName, sf::Sprite* sprite, const char* name) {
	sName = name;
	pSprite = sprite;
	ifstream data(fileName, ios::in | ios::binary);
	if (data.is_open()) {
		data >> nWidth >> nHeight;
		m_indicies = new int[nWidth * nHeight];
		m_solids = new bool[nWidth * nHeight];
		for (int i = 0; i < nWidth * nHeight; i++)
		{
			data >> m_indicies[i];
			data >> m_solids[i];
		}

		return true;
	}

	return false;
}

