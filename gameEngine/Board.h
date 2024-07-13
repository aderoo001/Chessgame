#ifndef BOARD_H
#define BOARD_H

#include <utility>
#include <vector>
#include <string>
#include <algorithm>

#include "../gameObject/Piece.h"
#include "../gameObject/Pawn.h"
#include "../gameObject/Knight.h"
#include "../gameObject/King.h"
#include "../gameObject/Queen.h"
#include "../gameObject/Rook.h"
#include "../gameObject/Bishop.h"

typedef std::pair<int, int> Dimension;

class Board {
    private:
        Dimension dimension = std::make_pair(8, 8);
        std::vector<Piece*> pieces;

    public:
        Board();
        ~Board();

        void init_board();
        
        void display() const;
        void draw(SDL_Renderer* renderer, int cellsize) const;
        void draw_pieces(SDL_Renderer* renderer, int cellsize) const;

        Piece* get_piece(Position pos);
        void add_piece(Piece* piece);
        void delete_piece(Piece* piece);

        std::vector<Position> get_possible_moves(Piece* piece);
};

#endif