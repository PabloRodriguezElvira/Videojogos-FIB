#include "ShaderCtrl.h"

// Game
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Player
#define JUMP_HEIGHT 50
#define JUMP_ANGLE_STEP 6

#define FALL_STEP 5
#define MOVE_STEP 2

#define HITBOX_SIZE glm::ivec2(16, 32)
#define PLAYER_HITBOX_X 17
#define PLAYER_HITBOX_Y 26
#define PLAYER_HITBOX glm::ivec2(PLAYER_HITBOX_X, PLAYER_HITBOX_Y)

// Scene & TileMap
#define SCREEN_X 32
#define SCREEN_Y 16

// ShaderCtrl
#define RENDER_SHADERS ShaderCtrl::instance().render()
#define TEX_PROGRAM ShaderCtrl::instance().getTexProgram()
