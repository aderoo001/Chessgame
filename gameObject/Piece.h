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
        int nb_moves = 0;
    
    public:
        Piece(Color color, Position pos);
        virtual ~Piece();

        Position getPosition() const { return position; }
        bool isInPosition(Position pos) const { return position == pos; }
        Color getColor() const { return color; }
        
        virtual void get_moves_in_direction(std::vector<Position>& moves, const std::vector<Piece*>& pieces, int dx, int dy) const;
        virtual std::vector<Position> get_possible_moves(std::vector<Piece *> pieces) const ;
        void move(Position next);

        virtual std::string display() const;
        virtual void draw(SDL_Renderer* renderer, int cellSize) const;
};

# endif