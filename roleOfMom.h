#ifndef ROLEOFMON_H
#define ROLEOFMON_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

const int TOTAL_PHASES = 20;  // Tổng số giai đoạn trong game

// Khai báo các đối tượng SDL cần thiết cho cửa sổ, renderer, và các tài nguyên
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern bool running;           // Trạng thái của trò chơi
extern bool isplayinggame;     // Trạng thái đang chơi game hay không
extern SDL_Texture* tuanChoi;  // Hình ảnh của Tuấn khi chơi game
extern SDL_Texture* momTexture;  // Hình ảnh của mẹ
extern SDL_Texture* backgroundTexture;  // Hình nền
extern SDL_Texture* tuanHoc;   // Hình ảnh của Tuấn khi học bài
extern Mix_Music* studyMusic;  // Nhạc khi học bài
extern Mix_Music* gameMusic;   // Nhạc khi chơi game
extern bool studyMusicPlaying; // Trạng thái của nhạc học bài

// Các biến điều khiển liên quan đến mẹ
extern bool momAppearing;         // Mẹ có xuất hiện không?
extern bool momChecking;          // Mẹ đang kiểm tra không?
extern Uint32 momCheckStartTime;  // Thời gian bắt đầu kiểm tra của mẹ
extern const Uint32 MOM_CHECK_DURATION;  // Thời gian kiểm tra của mẹ
extern float momX;                // Vị trí của mẹ
extern const float MOM_SPEED;     // Tốc độ di chuyển của mẹ
extern int momAppearancesLeft;    // Số lần mẹ còn có thể xuất hiện

// Biến điều khiển giai đoạn game
extern int gamePhases[TOTAL_PHASES];  // Các giai đoạn trong game
extern int currentPhase;              // Giai đoạn hiện tại
extern Uint32 lastPhaseChangeTime;    // Thời gian thay đổi giai đoạn

// Các hàm ngoài để xử lý logic game
extern float GetEscapeChance(int appearanceCount);
extern void ShufflePhases();  // Xáo trộn các giai đoạn game
extern SDL_Texture* LoadTexture(const char* filePath);  // Hàm tải texture từ file
extern void InitSDL();         // Khởi tạo SDL và các tài nguyên cần thiết
extern void HandleEvents();    // Xử lý sự kiện (như chuột, phím, etc)
extern void Update();          // Cập nhật logic game
extern void Render();          // Render hình ảnh game
extern void CleanUp();         // Dọn dẹp tài nguyên sau khi game kết thúc

#endif  // ROLEOFMON_H
