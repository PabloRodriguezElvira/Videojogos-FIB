#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE

#include "Definitions.h"


#include <glm/glm.hpp>

#include "Texture.h"
#include "ShaderProgram.h"
#include "Sprite.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

private:
	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	~TileMap();

	void render() const;
	void free();
	
	int getTileSizeX() const { return tileSize.x; }
	int getTileSizeY() const { return tileSize.y; }

	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& hitSize, const glm::ivec2& hitPos) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& hitSize, const glm::ivec2& hitPos) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& hitSize, const glm::ivec2& hitPos, int* posY, int fallStep);
	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& hitSize, const glm::ivec2& hitPos, int* posY, int fallStep);
	void paintTiles(const glm::ivec2& pos, const glm::ivec2& hitSize, const glm::ivec2& hitPos);
	bool fallMoveLeft(const glm::ivec2& pos, const glm::ivec2& hitSize, const glm::ivec2& hitPos) const;
	bool fallMoveRight(const glm::ivec2& pos, const glm::ivec2& hitSize, const glm::ivec2& hitPos) const;
	
private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	int nTiles;
	glm::ivec2 position, mapSize, tilesheetSize, tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int *map;
};


#endif // _TILE_MAP_INCLUDE


