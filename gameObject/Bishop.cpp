#include "Bishop.h"

Bishop::Bishop(Color color, Position position) : Piece(color, position) {}

Bishop::~Bishop() {}

std::vector<Position> Bishop::get_possible_moves() const {
    std::vector<Position> moves;
    return moves;
}

std::string Bishop::display() const { 
    return (color == Color::Black) ? "F*" : "F"; 
}

void Bishop::draw(SDL_Renderer* renderer, int cellSize) const {
    const char* imagePath;
    if (color == Color::White) {
        imagePath = "ressources/LightBishop.png";
    } else {
        imagePath = "ressources/DarkBishop.png";
    }

    SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath);
    if (texture == nullptr) {
        std::cerr << "LoadTexture Error: " << SDL_GetError() << std::endl;
        return;
    }

    Position pos = getPosition();
    SDL_Rect destRect = { pos.first * cellSize, pos.second * cellSize, cellSize, cellSize };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);
}