#include <iostream>
#include <SDL.h>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

void DrawMomIcon(SDL_Renderer* renderer, int timesAppeared) {
    // Vẽ 5 hình tròn nhỏ biểu tượng số lần mẹ đã xuất hiện
    for (int i = 0; i < timesAppeared; ++i) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Đỏ
        SDL_Rect circle = {20 + i * 30, 20, 20, 20}; // Gần góc trái dưới
        SDL_RenderFillRect(renderer, &circle);
    }
}

bool TuanReaction(int momAppearCount) {
    if (momAppearCount == 0 || momAppearCount == 1)
        return true;
    if (momAppearCount == 2)
        return rand() % 100 < 75;
    if (momAppearCount == 3)
        return rand() % 100 < 50;
    return rand() % 100 < 25;
}

void RunGameAsMom() {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Mẹ kiểm tra!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    bool running = true;
    SDL_Event event;

    int momAppearCount = 0;
    srand(time(NULL));

    while (running && momAppearCount < 5) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                // Mẹ xuất hiện!
                bool tuanTronDuoc = TuanReaction(momAppearCount);
                cout << "Lần kiểm tra #" << momAppearCount + 1 << ": ";
                if (tuanTronDuoc)
                    cout << "Tuấn đã kịp chuyển tab!" << endl;
                else
                    cout << "Bị mẹ phát hiện đang chơi game!" << endl;
                momAppearCount++;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Trắng nền
        SDL_RenderClear(renderer);

        DrawMomIcon(renderer, momAppearCount);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60fps
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

