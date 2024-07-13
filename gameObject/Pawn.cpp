#include "Pawn.h"


Pawn::Pawn(Color color, Position pos) : Piece(color, pos) {}

Pawn::~Pawn() {}

void Pawn::get_moves_in_direction(std::vector<Position>& moves, const std::vector<Piece*>& pieces, int dx, int dy) const {
    Position pos = position;
    pos.first += dx;
    pos.second += dy;

    std::vector<Position> tmp = {
        Position(pos.first - 1,pos.second), 
        Position(pos.first + 1,pos.second)
    };

    for(Position pos : tmp) {
        for(Piece* piece: pieces) {
            if (piece->isInPosition(pos) && piece->getColor() != color) {
                moves.push_back(pos);
                break;
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        if (pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8) {
            for (const Piece* piece : pieces) {
                if (piece->isInPosition(pos)) {
                    break;
                }
            }
            moves.push_back(pos);

            if (nb_moves != 0) break;

            pos.first += dx;
            pos.second += dy;
        }
    }
};


std::vector<Position> Pawn::get_possible_moves(std::vector<Piece*> pieces) const {
    std::vector<Position> moves;

    if (color == Color::White) {
        get_moves_in_direction(moves, pieces, 0, -1);
    } else {
        get_moves_in_direction(moves, pieces, 0, 1);
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