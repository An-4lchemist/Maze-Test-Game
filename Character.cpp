#include "Character.h"

void Character::move(const Map &map) {
    rect.x = x_pos;
    rect.y = y_pos;
}

bool Player::check_corners(const Map &map) {
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;
    x1 = x_pos;
    y1 = y_pos;

    x2 = x_pos + rect.w;
    y2 = y_pos;

    x3 = x_pos;
    y3 = y_pos + rect.h;

    x4 = x_pos + rect.w;
    y4 = y_pos + rect.h;

    if ((map.is_wall((int) y1 / map.cell_height, (int) x1 / map.cell_width)) ||
        (map.is_wall((int) y2 / map.cell_height, (int) x2 / map.cell_width)) ||
        (map.is_wall((int) y3 / map.cell_height, (int) x3 / map.cell_width)) ||
        (map.is_wall((int) y4 / map.cell_height, (int) x4 / map.cell_width))) {
        return true;
    }
    return false;
}

bool Player::has_won() {
    if (rect.y < -20)
        return true;
    return false;
}

bool Player::has_lost(const class Entity &e) {
    return SDL_HasIntersection(&(this->rect), &(e.rect));
}

void Player::move(const Map &map) {
    if (move_up) {
        y_pos -= speed;
        if (check_corners(map)) {
            y_pos = rect.y;
        }
    }
    if (move_down) {
        y_pos += speed;
        if (check_corners(map)) {
            y_pos = rect.y;
        }
    }
    if (move_left) {
        x_pos -= speed;
        if (check_corners(map)) {
            x_pos = rect.x;
        }
    }
    if (move_right) {
        x_pos += speed;
        if (check_corners(map)) {
            x_pos = rect.x;
        }
    }
    rect.x = x_pos;
    rect.y = y_pos;
}

void Entity::pathfind(const Map &map, const Player &p) {

    Node *parents[map.height][map.width];
    bool visited[map.height][map.width];
    for (int i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            parents[i][j] = nullptr;
            visited[i][j] = false;
        }
    }

    DS_List queue;
    int sx = (int) x_pos / map.cell_width;
    int sy = (int) y_pos / map.cell_height;
    int gx = (int) p.x_pos / map.cell_width;
    int gy = (int) p.y_pos / map.cell_height;

    queue.ins_end(sx, sy);
    visited[sy][sx] = true;
    while (!queue.empty()) {
//        queue.test_print();
        Node node = queue.peek_head();
        queue.del_head();
        if (node.x == gx && node.y == gy) {
            int i = gy;
            int j = gx;
            int a, b;
            while (!(parents[i][j]->x == sx && parents[i][j]->y == sy)) {
                a = parents[i][j]->y;
                b = parents[i][j]->x;
                i = a;
                j = b;
            }
            move_right = false;
            move_left = false;
            move_up = false;
            move_down = false;
            if (i == sy + 1) {
                move_down = true;
            }
            if (i == sy - 1) {
                move_up = true;
            }
            if (j == sx + 1) {
                move_right = true;
            }
            if (j == sx - 1) {
                move_left = true;
            }

            for (a = 0; a < map.height; a++) {
                for (b = 0; b < map.width; b++) {
                    delete parents[a][b];
                }
            }

            break;
        }
        DS_List neighbours = map.get_moves(node.x, node.y);
        for (auto child: neighbours.List) {
            if (!visited[child.y][child.x]) {
                queue.ins_end(child.x, child.y);
                visited[child.y][child.x] = true;
                parents[child.y][child.x] = new Node(node.x, node.y);
            }
        }
    }
}

bool Entity::check_corners(const Map &map) {
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;
    x1 = x_pos / map.cell_width;
    y1 = y_pos / map.cell_height;

    x2 = (x_pos + rect.w) / map.cell_width;
    y2 = y_pos / map.cell_height;

    x3 = x_pos / map.cell_width;
    y3 = (y_pos + rect.h) / map.cell_height;

    x4 = (x_pos + rect.w) / map.cell_width;
    y4 = (y_pos + rect.h) / map.cell_height;

    if (x1 == x2 && x2 == x3 && x3 == x4 && y1 == y2 && y2 == y3 && y3 == y4)
        return true;

    return false;
}

void Entity::move(const Map &map, const Player &p) {

    if (check_corners(map) &&
        !(x_pos / map.cell_width == p.x_pos / map.cell_width && y_pos / map.cell_height == p.y_pos / map.cell_height)) {
        pathfind(map, p);
    }

    if (move_up) {
        y_pos -= speed;
    }
    if (move_down) {
        y_pos += speed;
    }
    if (move_left) {
        x_pos -= speed;
    }
    if (move_right) {
        x_pos += speed;
    }
    rect.x = x_pos;
    rect.y = y_pos;
}
