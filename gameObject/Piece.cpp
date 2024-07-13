#include "Piece.h"

Piece::Piece(Color color, Position position): color{color}, position{position} {}

Piece::~Piece() {}

std::vector<Position> Piece::get_possible_moves() const {
    std::vector<Position> res;

    switch (color)
    {
    case Color::White :
        res.push_back(std::make_pair(position.first, position.second + 1));
        break;
    default:
        res.push_back(std::make_pair(position.first, position.second - 1));
        break;
    }

    return res;
}

void Piece::move(Position next) { position = next; };

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