#ifndef BOARD_H
#define BOARD_H

#include <utility>
#include <vector>
#include <string>

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
        void draw(SDL_Renderer* renderer) const;

        void add_piece(Piece* piece) {
            pieces.push_back(
                piece
            );
        }
};

#endif