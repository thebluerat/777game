#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Block.h"

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 600;

void update(int& blockY) {
    static Uint32 lastUpdate = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();

    // 500ms마다 블록 한 칸 아래로 이동
    if (currentTime - lastUpdate > 500) {
        blockY++;
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

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        update(blockY); // 블록 위치 업데이트

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderBlock(renderer, currentBlock, blockX, blockY); // 블록 렌더링
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

