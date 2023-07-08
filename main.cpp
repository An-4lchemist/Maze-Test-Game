#include <iostream>
#include "Character.h"
#include <SDL2/SDL.h>
#include <cmath>

using namespace std;

#define TITLE "Game"
#define SCREEN_HEIGHT 675
#define SCREEN_WIDTH 675
#define RADIUS 125

void init_System(SDL_Window **window, SDL_Renderer **renderer) {
    SDL_Init(SDL_INIT_VIDEO);
    *window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    *renderer = SDL_CreateRenderer(*window, -1, render_flags);
    SDL_SetRenderDrawBlendMode(*renderer, SDL_BLENDMODE_BLEND);
}

void del_System(SDL_Window **window, SDL_Renderer **renderer) {
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);
    SDL_Quit();
}

void handle_events(bool &close, Player &p) {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            close = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    p.move_up = true;
                    break;
                case SDL_SCANCODE_A:
                    p.move_left = true;
                    break;
                case SDL_SCANCODE_S:
                    p.move_down = true;
                    break;
                case SDL_SCANCODE_D:
                    p.move_right = true;
                    break;
                case SDL_SCANCODE_ESCAPE:
                    close = true;
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    p.move_up = false;
                    break;
                case SDL_SCANCODE_A:
                    p.move_left = false;
                    break;
                case SDL_SCANCODE_S:
                    p.move_down = false;
                    break;
                case SDL_SCANCODE_D:
                    p.move_right = false;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

bool check_field(const SDL_Rect *rect1, const SDL_Rect *rect2) {
    int x1 = rect1->x;
    int y1 = rect1->y;
    int x2 = rect2->x;
    int y2 = rect2->y;
    if ((sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) <= RADIUS)) {
        return true;
    } else {
        return false;
    }
}

void draw_win(SDL_Renderer *renderer, const Map &map, const Player &p, const Entity &e) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (auto rectangle: map.rectangles) {
        if (check_field(rectangle, &p.rect)) {
            SDL_RenderFillRect(renderer, rectangle);
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &p.rect);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    if (check_field(&e.rect, &p.rect))
        SDL_RenderFillRect(renderer, &e.rect);

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[]) {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    init_System(&window, &renderer);

    Map map;
    Player Suhas(13 * 25 + 7, 13 * 25 + 7, 15, 15);
    Entity Ankush(13 * 25 + 7, 25 * 25 + 7, 15, 15);
    bool close = false;
    while (!close && !Suhas.has_lost(Ankush) && !Suhas.has_won()) {
        draw_win(renderer, map, Suhas, Ankush);
        handle_events(close, Suhas);
        Suhas.move(map);
        Ankush.move(map, Suhas);
    }

    del_System(&window, &renderer);
    return 0;
}
