#include "Block.h"
#include <cstdlib>
#include <SDL2/SDL_ttf.h>
#include <iostream>

// 텍스트 렌더링 함수
void renderText(SDL_Renderer* renderer, const char* text, int x, int y, SDL_Color color) {
	TTF_Font* font = TTF_OpenFont("font.ttf", 24);
	if (!font) {
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect rect = {x, y, surface->w, surface->h};
	SDL_RenderCopy(renderer, texture, nullptr, &rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}

// 블록 초기화
void initializeBlock(Block block[2]) {
	for (int i = 0; i < 2; i++) {
		int randomIndex = rand() % 8;
		block[i].value = randomIndex;
		block[i].color = COLORS[randomIndex];
	}
}

// 블록 렌더링
void renderBlock(SDL_Renderer* renderer, Block block[2], int x, int y) {
	const int BLOCK_SIZE = 30;
	for (int i = 0; i < 2; i++) {
			SDL_Color color = block[i].color;
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

			SDL_Rect rect = {
				x * BLOCK_SIZE,
				(y + i) * BLOCK_SIZE,
				BLOCK_SIZE,
				BLOCK_SIZE
			};
			SDL_RenderFillRect(renderer, &rect);

			// 숫자를 텍스트로 렌더링
			char text[2];
			sprintf(text, "%d", block[i].value);
			renderText(renderer, text, rect.x + 10, rect.y + 5, {255,255,255,255});
	}
}
