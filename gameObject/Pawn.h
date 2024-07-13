#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
    private:
        PieceType type = PieceType::Pawn;
        
    public:
        Pawn(Color color, Position pos);
        ~Pawn();

        std::vector<Position> get_possible_moves() const override;
        std::string display() const override;
        virtual void draw(SDL_Renderer* renderer, int cellSize) const;
};




#endif