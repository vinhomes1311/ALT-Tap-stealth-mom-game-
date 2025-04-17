#include "roleOfSon.h"
#include <algorithm>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TUAN_WIDTH = 350;
const int TUAN_HEIGHT = 350;
const int MOM_WIDTH = 450;
const int MOM_HEIGHT = 450;
const int MAX_MOM_APPEARANCES = 5;
const int TOTAL_PHASES = 20;
const Uint32 PHASE_DURATION = 5000;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool running = true;
bool isplayinggame = true;
SDL_Texture* tuanChoi = nullptr;
SDL_Texture* momTexture = nullptr;
SDL_Texture* backgroundTexture = nullptr;
SDL_Texture* tuanHoc = nullptr;
Mix_Music* studyMusic = nullptr;
Mix_Music* gameMusic = nullptr;
bool studyMusicPlaying = false;

bool momAppearing = false;
bool momChecking = false;
Uint32 momCheckStartTime = 0;
const Uint32 MOM_CHECK_DURATION = 3000;
float momX = SCREEN_WIDTH;
const float MOM_SPEED = 4.0f;
int momAppearancesLeft = MAX_MOM_APPEARANCES;

int gamePhases[TOTAL_PHASES];
int currentPhase = 0;
Uint32 lastPhaseChangeTime = 0;

float GetEscapeChance2(int appearanceCount) {
    if (appearanceCount == 1 || appearanceCount == 2) return 1.0f;
    if (appearanceCount == 3) return 0.75f;
    if (appearanceCount == 4) return 0.5f;
    return 0.25f;
}

void ShufflePhases2() {
    for (int i = 0; i < 12; i++) gamePhases[i] = 1;
    for (int i = 12; i < 20; i++) gamePhases[i] = 0;
    random_shuffle(gamePhases, gamePhases + TOTAL_PHASES);
}

SDL_Texture* LoadTexture2(const char* filePath) {
    SDL_Surface* surface = IMG_Load(filePath);
    if (!surface) {
        cerr << "Failed to load image: " << filePath << " SDL_Error: " << SDL_GetError() << endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void InitSDL2() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    window = SDL_CreateWindow("Stealth Game - Mom Mode", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    srand(time(0));

    backgroundTexture = LoadTexture2("room_background.png");
    momTexture = LoadTexture2("mom_stern.png");
    tuanChoi = LoadTexture2("TuanChoiGame.png");
    tuanHoc = LoadTexture2("TuanHocBai.png");
    studyMusic = Mix_LoadMUS("study.wav");
    gameMusic = Mix_LoadMUS("choigame.mp3");

    ShufflePhases2();
}

void HandleEvents2() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (!momAppearing && !momChecking && momAppearancesLeft > 0) {
                momAppearing = true;
                momX = SCREEN_WIDTH;
                momAppearancesLeft--;
            }
        }
    }
}

void Update2() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastPhaseChangeTime >= PHASE_DURATION) {
        lastPhaseChangeTime = currentTime;
        if (currentPhase < TOTAL_PHASES - 1) currentPhase++;
    }

    isplayinggame = gamePhases[currentPhase];

    if (momAppearing) {
        momX -= MOM_SPEED;
        if (momX <= SCREEN_WIDTH - 500) {
            momAppearing = false;
            momChecking = true;
            momCheckStartTime = SDL_GetTicks();
        }
    }

    if (momChecking) {
        float escapeChance2 = GetEscapeChance2(5 - momAppearancesLeft);
        if (isplayinggame) {
            if ((rand() % 100) / 100.0f <= escapeChance2) {
                // Tuấn trốn được → Chuyển sang học bài
                isplayinggame = false;
            } else {
                cout << "Me bat qua tang!" << endl;
                running = false;
            }
        }
        if (SDL_GetTicks() - momCheckStartTime >= MOM_CHECK_DURATION) {
            momChecking = false;
            momX = SCREEN_WIDTH;
        }
    }

    if (momAppearancesLeft == 0) {
        cout << "Game Over!" << endl;
        running = false;
    }
}

void Render2() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    SDL_Rect tuanRect = {SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT - 350, TUAN_WIDTH, TUAN_HEIGHT};
    if (isplayinggame)
        SDL_RenderCopy(renderer, tuanChoi, NULL, &tuanRect);
    else
        SDL_RenderCopy(renderer, tuanHoc, NULL, &tuanRect);

    if (momAppearing || momChecking) {
        SDL_Rect momRect = {(int)momX, SCREEN_HEIGHT - 400, MOM_WIDTH, MOM_HEIGHT};
        SDL_RenderCopy(renderer, momTexture, NULL, &momRect);
    }

    for (int i = 0; i < momAppearancesLeft; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect circle = {50 + i * 30, SCREEN_HEIGHT - 50, 20, 20};
        SDL_RenderFillRect(renderer, &circle);
    }

    SDL_RenderPresent(renderer);
}

void CleanUp2() {
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


