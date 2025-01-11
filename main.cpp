#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 600;
const int BLOCK_SIZE = 30;

// 게임보드 배열
int board[20][10] = {0};

// 블록 좌표
int blockX = 4; // x좌표 (보드 기준)
int blockY = 0; // y좌표 (보드 기준)

// 게임 루프 실행
bool running = true;

void update() {
    blockY++; // 블록 한 칸 아래로 이동

    // 블록이 바닥에 닿으면 멈춤
    if (blockY >= 19 || board[blockY + 1][blockX] != 0) {
	board[blockY][blockX] = 1;
        blockY = 0; // 테스트: 블록 위치 리셋
        blockX = 4;
    }
}

void render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 배경 검정
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // 블록 파랑
    for (int y = 0; y < 20; y++) {
	for (int x = 0; x < 10; x++) {
	    if (board[y][x] != 0) {
	    SDL_Rect block = {x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
	    SDL_RenderFillRect(renderer, &block);
	    }
	}
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);    

    SDL_Rect currentBlock = {blockX * BLOCK_SIZE, blockY * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
    SDL_RenderFillRect(renderer, &currentBlock);

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("블록 낙하", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    Uint32 lastUpdate = SDL_GetTicks();

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        Uint32 current = SDL_GetTicks();
        if (current - lastUpdate > 500) { // 500ms마다 업데이트
            update();
            lastUpdate = current;
        }

        render(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

