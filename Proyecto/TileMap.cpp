#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "TileMap.h"
#include "ShaderCtrl.h"
#include "Player.h"


using namespace std;



TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if(map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * nTiles);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;
	
	fin.open(levelFile.c_str());
	if(!fin.is_open())
		return false;
	getline(fin, line);																// TILEMAP
	if(line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);																// Size of tile map in tiles
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);																// Tile size (físico) & block size (gráfico)
	sstream.str(line);
	sstream >> tileSize.x >> tileSize.y >> blockSize.x >> blockSize.y;
	getline(fin, line);																// Tilesheet
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);																// Number of tiles in tilesheet
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	getline(fin, line);																// Initial player tile (la que quieras + (-1, -2))
	sstream.str(line);
	sstream >> initPlayerTile.x >> initPlayerTile.y;
	
	map = new int[mapSize.x * mapSize.y];
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			fin.get(tile);
			if(tile == ' ' || tile == '0')
				map[j*mapSize.x+i] = 0;
			else if('1' <= tile && tile <= '9')
				map[j*mapSize.x+i] = (tile - int('0'));
			else
				map[j * mapSize.x + i] = 10 + (tile - int('A'));
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();

	return true;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	int tile;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	nTiles = 0;
	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if(tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize.x, minCoords.y + j * tileSize.y);
				texCoordTile[0] = glm::vec2(float((tile-1)%tilesheetSize.x) / tilesheetSize.x, float((tile-1)/tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize.x); vertices.push_back(posTile.y + blockSize.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize.x); vertices.push_back(posTile.y + blockSize.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = (pos.x + PLAYER_HITBOX_X) / tileSize.x;
	y0 = (pos.y + PLAYER_HITBOX_Y) / tileSize.y;
	y1 = (pos.y + size.y - 1 + PLAYER_HITBOX_Y) / tileSize.y;
	int posTile;
	for(int y=y0; y<=y1; y++)
	{
		posTile = y * mapSize.x + x;
		if(map[posTile] > 8)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = (pos.x + size.x - 1 + PLAYER_HITBOX_X) / tileSize.x;
	y0 = (pos.y + PLAYER_HITBOX_Y) / tileSize.y;
	y1 = (pos.y + size.y - 1 + PLAYER_HITBOX_Y) / tileSize.y;
	int posTile;
	for(int y=y0; y<=y1; y++)
	{
		posTile = y * mapSize.x + x;
		if(map[posTile] > 8)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
	int x0, x1, y;
	
	x0 = (pos.x + PLAYER_HITBOX_X) / tileSize.x;
	x1 = (pos.x + size.x - 1 + PLAYER_HITBOX_X) / tileSize.x;
	y = (pos.y + size.y - 1 + PLAYER_HITBOX_Y) / tileSize.y;
	int posTile;
	for (int x = x0; x <= x1; x++)
	{
		posTile = y * mapSize.x + x;
		if(map[posTile] != 0)
		{
			//Actualizar posición de Y.
			if(*posY + PLAYER_HITBOX_Y + size.y - tileSize.y * y <= FALL_STEP)
			{
				*posY = tileSize.y * y - size.y - PLAYER_HITBOX_Y;
				return true;
			}
		}
	}
	return false;
}

bool TileMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY)
{
	int x0, x1, y;

	x0 = (pos.x + PLAYER_HITBOX_X) / tileSize.x;
	x1 = (pos.x + size.x - 1 + PLAYER_HITBOX_X) / tileSize.x;
	y = (pos.y + PLAYER_HITBOX_Y) / tileSize.y;
	for (int x = x0; x <= x1; x++)
	{
		int posTile = y * mapSize.x + x;
		if (map[posTile] > 8)
		{
			//Actualizar posición de Y.
			if (tileSize.y * (y + 1) - (*posY + PLAYER_HITBOX_Y) <= FALL_STEP + 1)
			{
				*posY = tileSize.y * (y + 1) - PLAYER_HITBOX_Y;
				return true;
			}
		}
	}
	return false;
}

void TileMap::paintTiles(const glm::ivec2 &pos, const glm::ivec2 &size) 
{
	int x0, x1, y;
	
	x0 = (pos.x + PLAYER_HITBOX_X) / tileSize.x;
	x1 = (pos.x + size.x - 1 + PLAYER_HITBOX_X) / tileSize.x;
	y = (pos.y + size.y - 1 + PLAYER_HITBOX_Y) / tileSize.y;
	int posTile;
	for(int x=x0; x<=x1; x++)
	{
		posTile = (y+1) * mapSize.x + x;
		if(0 < map[posTile] && map[posTile] < 5)
		{
			//Pintar tile: (si es diferente del 0 - aire).
			map[posTile] += 4;
			prepareArrays(glm::vec2(SCREEN_X, SCREEN_Y), TEX_PROGRAM);
		}
	}	
}

