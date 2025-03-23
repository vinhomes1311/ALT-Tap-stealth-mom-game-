#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TUAN_WIDTH = 350;
const int TUAN_HEIGHT = 350;
const int MOM_WIDTH = 450;
const int MOM_HEIGHT = 450;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool running = true;
float progress = 0.0f;
bool mousePressed = false;
bool isplayinggame;
SDL_Texture* tuanChoi = nullptr;
SDL_Texture* momTexture = nullptr;
SDL_Texture* backgroundTexture = nullptr;
SDL_Texture* tuanHoc = nullptr;
Mix_Music* studyMusic = nullptr;
Mix_Music* gameMusic = nullptr;
bool studyMusicPlaying = false;

// Mẹ animation
bool momComingIn = false;
bool momLooking = false;
bool momGoingOut = false;
Uint32 momLookStartTime = 0;
const Uint32 MOM_LOOK_DURATION = 3000; // mẹ nhìn 3s
float momX = SCREEN_WIDTH; // bắt đầu ngoài màn hình
const float MOM_SPEED = 2.0f; // Di chuyển chậm hơn

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
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    window = SDL_CreateWindow("Stealth Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    srand(time(0));

    backgroundTexture = LoadTexture("room_background.png");
    momTexture = LoadTexture("mom_stern.png");
    tuanChoi = LoadTexture("TuanChoiGame.png");
    tuanHoc = LoadTexture("TuanHocBai.png");
    studyMusic = Mix_LoadMUS("study.wav");
    gameMusic = Mix_LoadMUS("choigame.mp3");
    if (!studyMusic) cerr << "Failed to load study.wav: " << Mix_GetError() << endl;
    if (!gameMusic) cerr << "Failed to load choigame.mp3: " << Mix_GetError() << endl;
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
    isplayinggame = false;
    if (mousePressed) {
        progress += 0.05f;
        isplayinggame = true;
    }

    if (isplayinggame) {
        if (Mix_PlayingMusic() == 0 || studyMusicPlaying) {
            Mix_HaltMusic();
            Mix_PlayMusic(gameMusic, -1);
            studyMusicPlaying = false;
        }
    } else {
        if (Mix_PlayingMusic() == 0 || !studyMusicPlaying) {
            Mix_HaltMusic();
            Mix_PlayMusic(studyMusic, -1);
            studyMusicPlaying = true;
        }
    }

    // Mẹ thò đầu vào thường xuyên hơn
    if (!momComingIn && !momLooking && !momGoingOut && rand() % 250 == 0) {
        momComingIn = true;
        momX = SCREEN_WIDTH;
    }

    if (momComingIn) {
        momX -= MOM_SPEED;
        if (momX <= SCREEN_WIDTH - 500) { // vị trí cố định
            momComingIn = false;
            momLooking = true;
            momLookStartTime = SDL_GetTicks();
        }
    }

    if (momLooking) {
        if (isplayinggame) {
            cout << "GAME OVER" << endl;
            running = false;
        }
        if (SDL_GetTicks() - momLookStartTime >= MOM_LOOK_DURATION) {
            momLooking = false;
            momGoingOut = true;
        }
    }

    if (momGoingOut) {
        momX += MOM_SPEED;
        if (momX >= SCREEN_WIDTH) {
            momGoingOut = false;
        }
    }

    if (progress >= 100.0f) {
        cout << "Well done!" << endl;
        running = false;
    }
}

void Render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    SDL_Rect tuanRect = {SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT - 350, TUAN_WIDTH, TUAN_HEIGHT};
    if (isplayinggame)
        SDL_RenderCopy(renderer, tuanChoi, NULL, &tuanRect);
    else
        SDL_RenderCopy(renderer, tuanHoc, NULL, &tuanRect);

    if (momComingIn || momLooking || momGoingOut) {
        SDL_Rect momRect = {(int)momX, SCREEN_HEIGHT - 400, MOM_WIDTH, MOM_HEIGHT};
        SDL_RenderCopy(renderer, momTexture, NULL, &momRect);
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect progressBar = {50, 550, (int)(progress * 7), 20};
    SDL_RenderFillRect(renderer, &progressBar);

    SDL_RenderPresent(renderer);
}

void CleanUp() {
    SDL_DestroyTexture(momTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(tuanChoi);
    SDL_DestroyTexture(tuanHoc);
    Mix_FreeMusic(studyMusic);
    Mix_FreeMusic(gameMusic);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
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
