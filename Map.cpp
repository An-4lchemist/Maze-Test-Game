#include "Map.h"
#include <SDL2/SDL.h>

bool Map::is_wall(int i, int j) const {
    if (layout[i][j])
        return false;
    return true;
}

DS_List Map::get_moves(int x, int y) const {
    DS_List moves;

    if (!is_wall(y, x)) {
        if (x >= 0 && y + 1 >= 0 && !is_wall(y + 1, x)) {
            moves.ins_end(x, y + 1);
        }
        if (x + 1 >= 0 && y >= 0 && !is_wall(y, x + 1)) {
            moves.ins_end(x + 1, y);
        }
        if (x >= 0 && y - 1 >= 0 && !is_wall(y - 1, x)) {
            moves.ins_end(x, y - 1);
        }
        if (x - 1 >= 0 && y >= 0 && !is_wall(y, x - 1)) {
            moves.ins_end(x - 1, y);
        }
    }

    return moves;
}

void Map::create_rectangles() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!is_wall(i, j)) {
                auto *rect = new SDL_Rect;
                rect->x = j * cell_width;
                rect->y = i * cell_height;
                rect->h = cell_height;
                rect->w = cell_width;
                rectangles.push_back(rect);
            }
        }
    }
}

void Map::free_rectangles() {
    for (auto &rectangle: rectangles) {
        delete rectangle;
    }
}