#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece{
    private:
        PieceType type = PieceType::Bishop;

    public:
        Bishop(Color color, Position position);
        ~Bishop();

        std::vector<Position> get_possible_moves() const;
        std::string display() const override;
        virtual void draw(SDL_Renderer* renderer, int cellSize) const;
};

#endif