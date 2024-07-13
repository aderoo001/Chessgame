#include "Pawn.h"


Pawn::Pawn(Color color, Position pos) : Piece(color, pos) {}

Pawn::~Pawn() {}

std::vector<Position> Pawn::get_possible_moves() const {
    std::vector<Position> moves;

    if (color == Color::White) {
        moves.push_back({position.first, position.second - 1});
    } else if (color == Color::Black) {
        moves.push_back({position.first, position.second + 1});
    }

    return moves;
}

std::string Pawn::display() const { 
    return (color == Color::Black) ? "P*" : "P"; 
}

void Pawn::draw(SDL_Renderer* renderer, int cellSize) const {
    const char* imagePath;
    if (color == Color::White) {
        imagePath = "ressources/LightPawn.png";
    } else {
        imagePath = "ressources/DarkPawn.png";
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