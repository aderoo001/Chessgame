#ifndef TOWER_H
#define TOWER_H

#include "Piece.h"

class Rook : public Piece
{
    private:
        PieceType type = PieceType::Rook;
        
    public:
        Rook(Color color, Position position);
        ~Rook();

        std::vector<Position> get_possible_moves() const;
        std::string display() const override;
        virtual void draw(SDL_Renderer* renderer, int cellSize) const;
};

#endif