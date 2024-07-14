#include <Knight.h>

Knight::Knight(Color color, Position pos) : Piece(color, pos, PieceType::Knight) {}

Knight::~Knight() {}

void Knight::get_moves_in_direction(std::vector<Position>& moves, const std::vector<Piece*>& pieces, int dx, int dy) const {
    Position pos = position;
    pos.first += dx;
    pos.second += dy;

    if (pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8) {
        for (const Piece* piece : pieces) {
            if (piece->isInPosition(pos)) {
                if (piece->getColor() != color) moves.push_back(pos);
                return;
            }
        }
        moves.push_back(pos);
    }
}

std::vector<Position> Knight::get_possible_moves(std::vector<Piece*> pieces) const {
    std::vector<Position> moves;

    int di = 2;
    int dj = 1;

    get_moves_in_direction(moves, pieces, di, dj);
    get_moves_in_direction(moves, pieces, -di, dj);
    get_moves_in_direction(moves, pieces, di, -dj);
    get_moves_in_direction(moves, pieces, -di, -dj);
    get_moves_in_direction(moves, pieces, dj, di);
    get_moves_in_direction(moves, pieces, -dj, di);
    get_moves_in_direction(moves, pieces, dj, -di);
    get_moves_in_direction(moves, pieces, -dj, -di);

    return moves;
}

std::string Knight::display() const { 
    return (color == Color::Black) ? "C*" : "C"; 
}

void Knight::draw(SDL_Renderer* renderer, int cellSize) const {
    const char* imagePath;
    if (color == Color::White) {
        imagePath = "ressources/LightKnight.png";
    } else {
        imagePath = "ressources/DarkKnight.png";
    }

    SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath);
    if (texture == nullptr) {
        std::cerr << "LoadTexture Error: " << SDL_GetError() << std::endl;
        return;
    }

    Position pos = getPosition();
    SDL_Rect destRect = { pos.first * cellSize, pos.second * cellSize, cellSize, cellSize };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);
}