#include "Bishop.h"

Bishop::Bishop(Color color, Position position) : Piece(color, position, PieceType::Bishop) {}

Bishop::~Bishop() {}

void Bishop::get_moves_in_direction(std::vector<Position>& moves, const std::vector<Piece*>& pieces, int dx, int dy) const {
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
};

std::vector<Position> Bishop::get_possible_moves(std::vector<Piece*> pieces) const {
    std::vector<Position> moves;

    get_moves_in_direction(moves, pieces, -1, -1);
    get_moves_in_direction(moves, pieces, 1, -1);
    get_moves_in_direction(moves, pieces, -1, 1);
    get_moves_in_direction(moves, pieces, 1, 1);

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