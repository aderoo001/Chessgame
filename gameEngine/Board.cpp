#include "Board.h"

Board::Board() {
    dimension = std::make_pair(8, 8);
}

Board::~Board() {
    for (Piece* piece : pieces) {
        delete piece;
    }
}

void Board::init_board() {
    std::pair<PieceType, Color> board[8][8] = {
        {{PieceType::Rook, Color::Black}, {PieceType::Pawn, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::Pawn, Color::White}, {PieceType::Rook, Color::White}},
        {{PieceType::Knight, Color::Black}, {PieceType::Pawn, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::Pawn, Color::White}, {PieceType::Knight, Color::White}},
        {{PieceType::Bishop, Color::Black}, {PieceType::Pawn, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::Pawn, Color::White}, {PieceType::Bishop, Color::White}},
        {{PieceType::Queen, Color::Black}, {PieceType::Pawn, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::Pawn, Color::White}, {PieceType::Queen, Color::White}},
        {{PieceType::King, Color::Black}, {PieceType::Pawn, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::Pawn, Color::White}, {PieceType::King, Color::White}},
        {{PieceType::Bishop, Color::Black}, {PieceType::Pawn, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::Pawn, Color::White}, {PieceType::Bishop, Color::White}},
        {{PieceType::Knight, Color::Black}, {PieceType::Pawn, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::Pawn, Color::White}, {PieceType::Knight, Color::White}},
        {{PieceType::Rook, Color::Black}, {PieceType::Pawn, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::None, Color::Black}, {PieceType::Pawn, Color::White}, {PieceType::Rook, Color::White}}
    };

    for (int i = 0; i < dimension.first; i++) {
        for (int j = 0; j < dimension.second; j++)  {
            Piece* piece = nullptr;
            switch (board[i][j].first) {
                case PieceType::Undefined:
                    piece = new Piece(board[i][j].second, Position(i, j));
                    break;
                case PieceType::Pawn:
                    piece = new Pawn(board[i][j].second, Position(i, j));
                    break;
                case PieceType::Rook:
                    piece = new Rook(board[i][j].second, Position(i, j));
                    break;
                case PieceType::Knight:
                    piece = new Knight(board[i][j].second, Position(i, j));
                    break;
                case PieceType::Bishop:
                    piece = new Bishop(board[i][j].second, Position(i, j));
                    break;
                case PieceType::Queen:
                    piece = new Queen(board[i][j].second, Position(i, j));
                    break;
                case PieceType::King:
                    piece = new King(board[i][j].second, Position(i, j));
                    break;
                default:
                    break;
            }

            if (piece != nullptr) {
                add_piece(piece);
            }
        }
    }
}

void Board::display() const {
    std::string board[8][8] = {};

    for (const auto& piece : pieces) {
        Position pos = piece->getPosition();
        std::string symbol = piece->display();
        board[pos.first][pos.second] = symbol;
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (!board[i][j].empty()) {
                printf(" %2s ", board[i][j].c_str());
            } else {
                printf(" -- ");
            }
        }
        printf("\n");
    }
}

void Board::draw(SDL_Renderer* renderer, int cellsize) const {
    for (int i = 0; i < dimension.first; ++i) {
        for (int j = 0; j < dimension.second; ++j) {
            SDL_Rect cellRect = { j * cellsize, i * cellsize, cellsize, cellsize };
            if ((i + j) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for light squares
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color for dark squares
            }
            SDL_RenderFillRect(renderer, &cellRect);
        }
    }

    for (const auto& piece : pieces) {
        piece->draw(renderer, cellsize);
    }
}

void Board::draw_pieces(SDL_Renderer* renderer, int cellsize) const {
    for (const auto& piece : pieces) {
        piece->draw(renderer, cellsize);
    }
}


Piece* Board::get_piece(Position pos) const {
    for (Piece* piece: pieces) {
        if (piece->isInPosition(pos)) return piece;
    } 
    return nullptr;
}

void Board::get_pieces_by_type(std::vector<Piece *> &list, PieceType type) const {
    for (Piece* piece: pieces) {
        if (piece->isPieceType(type)) {
            list.push_back(piece);
        }
    }
}

void Board::add_piece(Piece* piece) {
    pieces.push_back(
        piece
    );
}

void Board::delete_piece(Piece* piece) {
    std::vector<Piece*>::iterator iter = std::find(pieces.begin(), pieces.end(), piece);

    if (iter != pieces.end()) {
        delete *iter;
        pieces.erase(iter);
    }
}

std::vector<Position> Board::get_possible_moves(Piece* piece) const {
    std::vector<Position> ret;
    ret = piece->get_possible_moves(pieces);
    return ret;
}