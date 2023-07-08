#include <SDL2/SDL.h>
#include "Map.h"

class Character {
protected:
    SDL_Rect rect{};
    int x_pos;
    int y_pos;
    bool move_up = false;
    bool move_down = false;
    bool move_left = false;
    bool move_right = false;
    int speed = 2;

    virtual bool check_corners(const Map &map) = 0;

    virtual void move(const Map &map);

public:

    Character(int x, int y, int w, int h) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        x_pos = x;
        y_pos = y;
    }
};

class Player : public Character {
public:
    Player(int x, int y, int w, int h) : Character(x, y, w, h) {}

    friend class Entity;

    friend void handle_events(bool &close, Player &p);

    friend void draw_win(SDL_Renderer *renderer, const Map &map, const Player &p, const class Entity &e);

    friend int main(int argc, char *argv[]);

    void move(const Map &map) override;

    bool check_corners(const Map &map) override;

    bool has_won();

    bool has_lost(const class Entity &e);
};

class Entity : public Character {
public:
    Entity(int x, int y, int w, int h) : Character(x, y, w, h) {}

    friend Player;

    friend void draw_win(SDL_Renderer *renderer, const Map &map, const Player &p, const class Entity &e);

    friend int main(int argc, char *argv[]);

    void move(const Map &map, const Player &p);

    bool check_corners(const Map &map) override;

    void pathfind(const Map &map, const Player &p);
};