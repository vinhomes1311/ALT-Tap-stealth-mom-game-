#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TUAN_WIDTH = 350;
const int TUAN_HEIGHT = 350;
const int MOM_WIDTH = 350;
const int MOM_HEIGHT = 350;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool running = true;
bool altTab = false;
float progress = 0.0f;
bool momLooking = false;
Uint32 momLookStartTime = 0;
const Uint32 MOM_LOOK_DURATION = 1500;
const float PROGRESS_INCREASE_RATE = 0.05f;
bool mousePressed = false;

SDL_Texture* tuanTexture = nullptr;
SDL_Texture* momTexture = nullptr;
SDL_Texture* backgroundTexture = nullptr;

SDL_Texture* LoadTexture(const char* filePath) {
    SDL_Surface* surface = IMG_Load(filePath);
    if (!surface) {
        cerr << "Failed to load image: " << filePath << " SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void InitSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow("Stealth Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    srand(time(0));

    backgroundTexture = LoadTexture("room_background.png");
    tuanTexture = LoadTexture("tuan_back.png");
    momTexture = LoadTexture("mom_stern.png");
}

void HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            mousePressed = true;
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            mousePressed = false;
        }
    }
}

void Update() {
    if (mousePressed) {
        progress += PROGRESS_INCREASE_RATE;
    }
    if (!momLooking && rand() % 500 == 0) {
        momLooking = true;
        momLookStartTime = SDL_GetTicks();
    }
    if (momLooking) {
        if (mousePressed && SDL_GetTicks() - momLookStartTime >= MOM_LOOK_DURATION) {
            cout << "GAME OVER" << endl;
            running = false;
        }
        if (SDL_GetTicks() - momLookStartTime >= MOM_LOOK_DURATION) {
            momLooking = false;
        }
    }
    if (progress >= 100.0f) {
        cout << "NEXT LEVEL" << endl;
        running = false;
    }
}

void Render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    SDL_Rect tuanRect = {SCREEN_WIDTH / 2 - 75 - 40, SCREEN_HEIGHT - 275, TUAN_WIDTH, TUAN_HEIGHT};
    SDL_RenderCopy(renderer, tuanTexture, NULL, &tuanRect);

    if (momLooking) {
        SDL_Rect momRect = {SCREEN_WIDTH - 180 - 40, SCREEN_HEIGHT - 275, MOM_WIDTH, MOM_HEIGHT};
        SDL_RenderCopy(renderer, momTexture, NULL, &momRect);
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect progressBar = {50, 550, (int)(progress * 7), 20};
    SDL_RenderFillRect(renderer, &progressBar);

    SDL_RenderPresent(renderer);
}

void CleanUp() {
    SDL_DestroyTexture(tuanTexture);
    SDL_DestroyTexture(momTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    InitSDL();
    while (running) {
        HandleEvents();
        Update();
        Render();
        SDL_Delay(16);
    }
    CleanUp();
    return 0;
}
