#include "Rook.h"

Rook::Rook(Color color, Position pos) : Piece(color, pos) {}

Rook::~Rook() {}


void Rook::get_moves_in_direction(std::vector<Position>& moves, const std::vector<Piece*>& pieces, int dx, int dy) const {
    Position pos = position;
    pos.first += dx;
    pos.second += dy;

    while (pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8) {
        bool isBlocked = false;
        for (const Piece* piece : pieces) {
            if (piece->isInPosition(pos)) {
                if (piece->getColor() != color) {
                    moves.push_back(pos);
                }
                isBlocked = true;
                break;
            }
        }
        if (isBlocked) break;
        moves.push_back(pos);
        pos.first += dx;
        pos.second += dy;
    }
}

std::vector<Position> Rook::get_possible_moves(std::vector<Piece*> pieces) const {
    std::vector<Position> moves;

    get_moves_in_direction(moves, pieces, 0, -1);
    get_moves_in_direction(moves, pieces, 0, 1);
    get_moves_in_direction(moves, pieces, -1, 0);
    get_moves_in_direction(moves, pieces, 1, 0);

    return moves;
}

std::string Rook::display() const { 
    return (color == Color::Black) ? "T*" : "T"; 
}

void Rook::draw(SDL_Renderer* renderer, int cellSize) const {
    const char* imagePath;
    if (color == Color::White) {
        imagePath = "ressources/LightRook.png";
    } else {
        imagePath = "ressources/DarkRook.png";
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