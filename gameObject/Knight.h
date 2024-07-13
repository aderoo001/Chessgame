#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece
{
    private:
        PieceType type = PieceType::Knight;
        
    public:
        Knight(Color color, Position position);
        ~Knight();

        std::vector<Position> get_possible_moves() const;
        std::string display() const override;
        virtual void draw(SDL_Renderer* renderer, int cellSize) const;
};

#endif