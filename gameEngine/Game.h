#ifndef GAME_H
#define GAME_H

#include "../gameObject/Piece.h"
#include "Board.h"

class Game {
private:
    Color activePlayer = Color::White;    
    Board board;
    Piece* selectedPiece = nullptr;
    std::vector<Position> moves;

    void switchPlayer();

public:
    Game();
    ~Game();

    void draw_board(SDL_Renderer* renderer, int cellsize);
    void draw_pieces(SDL_Renderer* renderer, int cellsize);
    void draw_selected_piece(SDL_Renderer* renderer, int cellsize);
    void draw_moves(SDL_Renderer* renderer, int cellsize);

    void get_possible_moves(Position pos);
    bool move(Position pos);
    void remove_selected_piece() {selectedPiece = nullptr;}
    void remove_moves() {moves.clear();}
};

#endif