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

        void get_moves_in_direction(std::vector<Position>& moves, const std::vector<Piece*>& pieces, int dx, int dy) const override;
        std::vector<Position> get_possible_moves(std::vector<Piece*> pieces) const override;
        std::string display() const override;
        virtual void draw(SDL_Renderer* renderer, int cellSize) const override;
};

#endif