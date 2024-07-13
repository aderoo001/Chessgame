#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


typedef std::pair<int, int> Position;

enum class Color {
    White,
    Black
};

enum class PieceType {
    None,
    Undefined,
    Knight,
    Pawn,
    Rook,
    Bishop,
    King,
    Queen
};


class Piece {
    protected:
        const PieceType type = PieceType::Undefined;
        const Color color;
        Position position;
    
    public:
        Piece(Color color, Position pos);
        virtual ~Piece();

        Position getPosition() const { return position; }
        Color getColor() const {return color; }
        
        virtual std::vector<Position> get_possible_moves() const;
        virtual std::string display() const;
        virtual void draw(SDL_Renderer* renderer, int cellSize) const;

        void move(Position next);
};

# endif