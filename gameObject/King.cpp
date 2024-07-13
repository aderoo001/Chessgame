#include <King.h>

King::King(Color color, Position pos) : Piece(color, pos) {}

King::~King() {}

std::vector<Position> King::get_possible_moves() const {
    std::vector<Position> moves;
    return moves;
}

std::string King::display() const { 
    return (color == Color::Black) ? "R*" : "R"; 
}

void King::draw(SDL_Renderer* renderer, int cellSize) const {
    const char* imagePath;
    if (color == Color::White) {
        imagePath = "ressources/LightKing.png";
    } else {
        imagePath = "ressources/DarkKing.png";
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