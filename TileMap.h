#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "map.h"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& fname, Map cmap)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(fname))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(cmap.nWidth * cmap.nHeight * 4);

        for (unsigned int i = 0; i < cmap.nWidth; ++i)
            for (unsigned int j = 0; j < cmap.nHeight; ++j)
            {
                // get the current tile number
                int tileNumber = cmap.GetIndex(i, j);

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / 16);
                int tv = tileNumber / (m_tileset.getSize().x / 16);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * cmap.nWidth) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * 16, j * 16);
                quad[1].position = sf::Vector2f((i + 1) * 16, j * 16);
                quad[2].position = sf::Vector2f((i + 1) * 16, (j + 1) * 16);
                quad[3].position = sf::Vector2f(i * 16, (j + 1) * 16);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * 16, tv * 16);
                quad[1].texCoords = sf::Vector2f((tu + 1) * 16, tv * 16);
                quad[2].texCoords = sf::Vector2f((tu + 1) * 16, (tv + 1) * 16);
                quad[3].texCoords = sf::Vector2f(tu * 16, (tv + 1) * 16);
            }

        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};
