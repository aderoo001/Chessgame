#include <Knight.h>

Knight::Knight(Color color, Position pos) : Piece(color, pos) {}

Knight::~Knight() {}

std::vector<Position> Knight::get_possible_moves() const {
    std::vector<Position> moves;
    return moves;
}

std::string Knight::display() const { 
    return (color == Color::Black) ? "C*" : "C"; 
}

void Knight::draw(SDL_Renderer* renderer, int cellSize) const {
    const char* imagePath;
    if (color == Color::White) {
        imagePath = "ressources/LightKnight.png";
    } else {
        imagePath = "ressources/DarkKnight.png";
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