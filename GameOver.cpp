#include "GameOver.h"
#include <iostream>

void renderGameOver(SDL_Renderer* renderer, TTF_Font* font) {
	const char* gameOverText = "GAME OVER";
	SDL_Color white = {255,255,255,255};

	SDL_Surface* surface = TTF_RenderText_Solid(font, gameOverText, white);
	if (!surface) {
		std::cerr << "Failed to create surface: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture) {
		std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
		return;
	}

	int textWidth, textHeight;
	TTF_SizeText(font, gameOverText, &textWidth, &textHeight);

	SDL_Rect dstRect = {
		(300 - textWidth) / 2, // 화면 중앙에 텍스트 배치
		(600 - textHeight) / 2,
		textWidth,
		textHeight
	};

	SDL_RenderCopy(renderer, texture, NULL, &dstRect);
	SDL_DestroyTexture(texture);
}

