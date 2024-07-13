#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece{
    private:
        PieceType type = PieceType::King;

    public:
        King(Color color, Position position);
        ~King();

        std::vector<Position> get_possible_moves() const;
        std::string display() const override;
        virtual void draw(SDL_Renderer* renderer, int cellSize) const;
};

#endif