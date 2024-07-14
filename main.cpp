#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "./gameEngine/Game.h"
#include "./gameObject/Piece.h"

#define SIZE 640

void renderText(SDL_Renderer* renderer, const char* text, int w, int h, SDL_Color color, TTF_Font* font) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);

    SDL_Rect dstrect = { (w - (surface->w + 12))/2 , (h - (surface->h + 12))/2, surface->w + 12, surface->h + 12 };
    SDL_SetRenderDrawColor(renderer, 76, 98, 112, 200); 
    SDL_RenderFillRect(renderer, &dstrect);
    dstrect = { (w - (surface->w + 10))/2 , (h - (surface->h + 10))/2, surface->w + 10, surface->h + 10 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200); 
    SDL_RenderFillRect(renderer, &dstrect);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    dstrect = { (w - surface->w)/2 , (h - surface->h)/2, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
        return -1;
    }

    SDL_Window* win = SDL_CreateWindow("Chess Board", 100, 100, SIZE, SIZE, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("ressources/Platinum Sign.ttf", SIZE/16);
    if (font == NULL) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        return -1;
    }

    bool running = true;
    int cellsize = SIZE/8;
    SDL_Event event;
    SDL_Color c = {76, 98, 112};

    Game game;
    Color winner;

    while (running) {
         while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);

                        Position pos = Position(mouseX/cellsize, mouseY/cellsize);
                        if (!game.move(pos)) {
                            game.get_possible_moves(Position(mouseX/cellsize, mouseY/cellsize));
                        } else {
                            winner = game.is_over();
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
    
        game.draw_board(renderer, cellsize);
        game.draw_selected_piece(renderer, cellsize);
        game.draw_moves(renderer, cellsize);
        game.draw_pieces(renderer, cellsize);

        switch (winner)
        {
        case Color::White:
            renderText(renderer, "LIGHT WINS", SIZE, SIZE, c, font);
            break;
        case Color::Black:
            renderText(renderer, "DARK WINS", SIZE, SIZE, c, font);
            break;
        default:
            break;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}