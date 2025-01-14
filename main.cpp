#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Block.h"
#include "Grid.h"

const int SCREEN_WIDTH = GRID_WIDTH * 30;
const int SCREEN_HEIGHT = GRID_HEIGHT * 30;
const int BLOCK_SIZE = 30;

// 게임판 배열 초기화
int gameGrid[GRID_HEIGHT][GRID_WIDTH] = {0};

// 충돌 감지 함수
bool checkCollision(int blockX, int blockY, Block block[2], int gameGrid[GRID_HEIGHT][GRID_WIDTH]) {
	for (int i = 0; i < 2; i++) {
		int x = blockX;
		int y = blockY + i;

		// 바닥이나 다른 블록과 충돌 감지
		if (y >= GRID_HEIGHT || gameGrid[y][x] != 0) {
			return true;
		}
	}
	return false;
}

// 게임판에 블록 추가
void addBlockToGrid(int blockX, int blockY, Block block[2], int gameGrid[GRID_HEIGHT][GRID_WIDTH]) {
	for (int i = 0; i < 2; i++) {
		int x = blockX;
		int y = blockY + i;
		if (y < GRID_HEIGHT) {
			gameGrid[y][x] = block[i].value;
		}
	}
}

void update(int& blockY, int blockX, Block block[2], int gameGrid[GRID_HEIGHT][GRID_WIDTH], bool& newBlockNeeded) {
    static Uint32 lastUpdate = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();

    // 500ms마다 블록 한 칸 아래로 이동
    if (currentTime - lastUpdate > 500) {
	    if (checkCollision(blockX, blockY + 1, block, gameGrid)) {
		    newBlockNeeded = true;
	    } else {
        	blockY++;
	    }
       		lastUpdate = currentTime;
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "777 Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Block currentBlock[2];
    initializeBlock(currentBlock);

    bool running = true;
    SDL_Event event;

    int blockX = 4, blockY = 0;
    bool newBlockNeeded = false;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        update(blockY, blockX, currentBlock, gameGrid, newBlockNeeded); // 블록 위치 업데이트

	// 새로운 블록 생성 처리
	if (newBlockNeeded) {
		addBlockToGrid(blockX, blockY, currentBlock, gameGrid);
		blockX = 4; // 새 블록의 초기 위치
		blockY = 0;
		initializeBlock(currentBlock);
		newBlockNeeded = false;
	}

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

	// 게임판의 블록 렌더링
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			if (gameGrid[y][x] != 0) {
				SDL_Color color = COLORS[gameGrid[y][x]];
				SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

				SDL_Rect rect = {
					x * BLOCK_SIZE,
					y * BLOCK_SIZE,
					BLOCK_SIZE,
					BLOCK_SIZE
				};
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}
	
	// 현재 떨어지는 블록 렌더링
        renderBlock(renderer, currentBlock, blockX, blockY); 
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

