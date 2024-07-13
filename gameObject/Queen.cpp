#include "Queen.h"

Queen::Queen(Color color, Position position) : Piece(color, position) {}

Queen::~Queen() {}

std::vector<Position> Queen::get_possible_moves() const {
    std::vector<Position> moves;
    return moves;
}

std::string Queen::display() const { 
    return (color == Color::Black) ? "Q*" : "Q"; 
}

void Queen::draw(SDL_Renderer* renderer, int cellSize) const {
    const char* imagePath;
    if (color == Color::White) {
        imagePath = "ressources/LightQueen.png";
    } else {
        imagePath = "ressources/DarkQueen.png";
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