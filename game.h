#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
#include <vector>

class Wall {
public:
    int x, y;           // Tọa độ của tường
    SDL_Rect rect;      // Hình chữ nhật SDL để vẽ và phát hiện va chạm
    bool active;        // Trạng thái hoạt động của tường
    SDL_Color color;    // Màu sắc của tường (để vẽ)

    Wall(int posX, int posY, int width, int height);
    void render(SDL_Renderer* renderer);
    void setActive(bool isActive);
    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
};

class Game {
public:
    Game();   // Constructor
    ~Game();  // Destructor
    void run();
    void initMap(); // Thêm khai báo hàm initMap

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    std::vector<Wall> walls; // Vector để lưu các bức tường
    int map[15][20];         // Mảng bản đồ (15x20)
};

#endif // GAME_H
