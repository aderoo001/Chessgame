#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece{
    private:
        PieceType type = PieceType::Bishop;

    public:
        Queen(Color color, Position position);
        ~Queen();

        std::vector<Position> get_possible_moves() const;
        std::string display() const override;
        virtual void draw(SDL_Renderer* renderer, int cellSize) const;
};

#endif