#include "Game.h"

Game::Game() {
    board.init_board();
}

Game::~Game() {}

void Game::draw_board(SDL_Renderer* renderer, int cellsize) const {
    board.draw(renderer, cellsize);
}

void Game::draw_pieces(SDL_Renderer* renderer, int cellsize) const {
    board.draw_pieces(renderer, cellsize);
}

void draw_filled_circle(SDL_Renderer *renderer, int centerX, int centerY, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    for (int y = -radius; y <= radius; y++) {
        int x = (int)std::round(std::sqrt(radius * radius - y * y));
        SDL_SetRenderDrawColor(renderer, r, g, b, a);

        SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
    }
}


void Game::draw_selected_piece(SDL_Renderer* renderer, int cellsize) const {
    if (selectedPiece != nullptr) {
        Position cell = selectedPiece->getPosition();

        SDL_Rect rect = {cell.first * cellsize, cell.second * cellsize, cellsize, cellsize};
        SDL_SetRenderDrawColor(renderer, 51, 51, 255, 100);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Game::draw_moves(SDL_Renderer* renderer, int cellsize) const {
    for (Position move : moves) {
        SDL_Rect rect = {move.first * cellsize, move.second * cellsize, cellsize, cellsize};
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 255, 80, 80, 100);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Game::switchPlayer() {
    switch (activePlayer)
    {
    case Color::White:
        activePlayer = Color::Black;
        break;
    default:
        activePlayer = Color::White;
        break;
    }
}

void Game::switchPlayer(Color color) {
    activePlayer = color;
}

bool Game::move(Position pos) {
    auto it = std::find(moves.begin(), moves.end(), pos);

    if (it != moves.end()) {
        Piece* piece = board.get_piece(pos);
        if (piece) board.delete_piece(piece);
        selectedPiece->move(pos);
        
        remove_selected_piece();
        remove_moves();
        switchPlayer();
        return true;
    }

    remove_selected_piece();
    remove_moves();
    return false;
}

void Game::get_possible_moves(Position pos) {
    remove_moves();
    selectedPiece = board.get_piece(pos);
    if (selectedPiece && selectedPiece->getColor() == activePlayer) {
        moves = board.get_possible_moves(selectedPiece);
    } else remove_selected_piece();
}

Color Game::is_over() {
    std::vector<Piece *> kings;
    board.get_pieces_by_type(kings, PieceType::King);
    if (kings.size() == 1) {
        switchPlayer(Color::None);
        return kings.front()->getColor();
    }
    return Color::None;
}