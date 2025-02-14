#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include "Grid.h"

// 블록 구조체
struct Block {
	int value;	// 블록 숫자
	SDL_Color color;// 블록 색깔
};

// 블록 색상 배열
const SDL_Color COLORS[] = {
	{0x54, 0xB5, 0xF9, 0xFF}, // 0
	{0x60, 0xCE, 0xEC, 0xFF}, // 1
	{0x81, 0xD6, 0x81, 0xFF}, // 2
	{0x57, 0x91, 0xF6, 0xFF}, // 3
	{0xCC, 0x97, 0xF6, 0xFF}, // 4
	{0xD7, 0x72, 0xD7, 0xFF}, // 5
	{0xD5, 0x66, 0x91, 0xFF}, // 6
	{0xD8, 0x36, 0x3F, 0xFF}  // 7
};

// 함수 선언
void initializeBlock(Block block[2]);
void renderBlock(SDL_Renderer* renderer, Block block[2], int x, int y);

#endif
