#ifndef ROLEOFSON_H
#define ROLEOFSON_H

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function declarations
SDL_Texture* LoadTexture(const char* filePath, SDL_Renderer* renderer); // Loads a texture from a file
void InitSDL();  // Initializes SDL, image, and audio subsystems
void HandleEvents(); // Handles user input events
void Update(); // Updates game logic
void Render(); // Renders game visuals
void CleanUp(); // Cleans up resources when the game is over

// Game variables (move to header for access in multiple files)
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern bool running;
extern bool mousePressed;
extern bool isplayinggame;
extern float progress;
extern SDL_Texture* tuanChoi;
extern SDL_Texture* momTexture;
extern SDL_Texture* backgroundTexture;
extern SDL_Texture* tuanHoc;
extern Mix_Music* studyMusic;
extern Mix_Music* gameMusic;
extern bool studyMusicPlaying;

// Mẹ animation variables
extern bool momComingIn;
extern bool momLooking;
extern bool momGoingOut;
extern Uint32 momLookStartTime;
extern const Uint32 MOM_LOOK_DURATION;
extern float momX;
extern const float MOM_SPEED;

#endif // ROLEOFSON_H
