#include "Piece.h"

Piece::Piece(Color color, Position position): color{color}, position{position} {}

Piece::~Piece() {}

void Piece::get_moves_in_direction(std::vector<Position>& moves, const std::vector<Piece*>& pieces, int dx, int dy) const {
    Position pos = position;
    pos.first += dx;
    pos.second += dy;

    if (pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8) {
        for (const Piece* piece : pieces) {
            if (piece->isInPosition(pos)) {
                return;
            }
        }
        moves.push_back(pos);
    }
};

std::vector<Position> Piece::get_possible_moves(std::vector<Piece *> pieces) const {
    std::vector<Position> moves;

    get_moves_in_direction(moves, pieces, 0, -1);
    get_moves_in_direction(moves, pieces, 0, 1);
    get_moves_in_direction(moves, pieces, -1, 0);
    get_moves_in_direction(moves, pieces, 1, 0);

    return moves;
}

void Piece::move(Position next) { position = next; nb_moves++; };

std::string Piece::display() const { 
    std::string ret = "O";
    if (color == Color::Black) ret = "X";
    return ret; 
}

void Piece::draw(SDL_Renderer* renderer, int cellSize) const {
    SDL_Rect rect1 = {position.first * cellSize + cellSize/4 - 1, position.second * cellSize + cellSize/4 - 1, cellSize/2 + 2, cellSize/2 + 2};
    SDL_Rect rect2 = {position.first * cellSize + cellSize/4, position.second * cellSize + cellSize/4, cellSize/2, cellSize/2};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &rect1);
    if (color == Color::White) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    SDL_RenderFillRect(renderer, &rect2);
}