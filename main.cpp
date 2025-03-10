#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>

class Game {
public:
    Game();   // Constructor
    ~Game();  // Destructor
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
};

#endif // GAME_H
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TILE_SIZE = 40;
const int MAP_WIDTH = SCREEN_WIDTH / TILE_SIZE;
const int MAP_HEIGHT = SCREEN_HEIGHT / TILE_SIZE;
const char* WINDOW_TITLE = "Battle City";

// Constructor
Game::Game() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        isRunning = false;
    } else {
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            isRunning = false;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!renderer) {
                std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                isRunning = false;
            } else {
                isRunning = true;
            }
        }
    }
}

// Destructor
Game::~Game() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

// Render game
void Game::run() {
    SDL_Event event;
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        // Vẽ màn hình
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);

        // Thiết lập màu đen để vẽ các ô vuông
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int i = 0; i < MAP_HEIGHT; ++i) {
            for (int j = 0; j < MAP_WIDTH; ++j) {
                SDL_Rect tile = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                SDL_RenderFillRect(renderer, &tile);
            }
        }

        // Vẽ lưới trắng để dễ nhìn bản đồ
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i <= MAP_HEIGHT; ++i) {
            SDL_RenderDrawLine(renderer, 0, i * TILE_SIZE, SCREEN_WIDTH, i * TILE_SIZE);
        }
        for (int j = 0; j <= MAP_WIDTH; ++j) {
            SDL_RenderDrawLine(renderer, j * TILE_SIZE, 0, j * TILE_SIZE, SCREEN_HEIGHT);
        }

        SDL_RenderPresent(renderer);

        // Giới hạn tốc độ khung hình (FPS)
        SDL_Delay(16);
    }
}
int main(int argc, char* argv[]) {
    Game game;
    game.run();

    return 0;
}
