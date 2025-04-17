#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "roleOfSon.h"
#include "roleOfMom.h"

using namespace std;

SDL_Texture* menuBackground = nullptr;
SDL_Texture* buttonCon = nullptr;
SDL_Texture* buttonMe = nullptr;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TUAN_WIDTH = 350;
const int TUAN_HEIGHT = 350;
const int MOM_WIDTH = 450;
const int MOM_HEIGHT = 450;

const int RONG_MAN_HINH = 800;
const int CAO_MAN_HINH = 600;
const int RONG_TUAN = 350;
const int CAO_TUAN = 350;
const int RONG_ME = 450;
const int CAO_ME = 450;
const int SO_LAN_ME_KIEM_TRA = 5;
const int TONG_GIAI_DOAN = 20;
const Uint32 THOI_GIAN_MOI_GIAI_DOAN = 5000;

void RunGameAsChild() {
    cout << "Chạy game ở chế độ con..." << endl;
    InitSDL();
    while (running) {
        HandleEvents();
        Update();
        Render();
        SDL_Delay(16);
    }
    CleanUp();
}

SDL_Window* cua_so = nullptr;
SDL_Renderer* ve_hinh = nullptr;
bool dang_chay = true;
bool dang_choi_game = true;
SDL_Texture* anh_tuan_choi = nullptr;
SDL_Texture* anh_me = nullptr;
SDL_Texture* anh_nen = nullptr;
SDL_Texture* anh_tuan_hoc = nullptr;
Mix_Music* nhac_hoc_bai = nullptr;
Mix_Music* nhac_game = nullptr;

bool me_dang_xuat_hien = false;
bool me_dang_kiem_tra = false;
Uint32 thoi_gian_bat_dau_kiem_tra = 0;
const Uint32 THOI_GIAN_ME_KIEM_TRA = 3000;
float vi_tri_meX = RONG_MAN_HINH;
const float TOC_DO_ME = 4.0f;
int so_lan_con_lai = SO_LAN_ME_KIEM_TRA;

int giai_doan_choi[TONG_GIAI_DOAN];
int giai_doan_hien_tai = 0;
Uint32 thoi_gian_chuyen_giai_doan = 0;

float XacSuatTron(int lan_xuat_hien) {
    if (lan_xuat_hien == 1 || lan_xuat_hien == 2) return 1.0f;
    if (lan_xuat_hien == 3) return 0.75f;
    if (lan_xuat_hien == 4) return 0.5f;
    return 0.25f;
}

void TronGiaiDoan() {
    for (int i = 0; i < 12; i++) giai_doan_choi[i] = 1;
    for (int i = 12; i < 20; i++) giai_doan_choi[i] = 0;
    random_shuffle(giai_doan_choi, giai_doan_choi + TONG_GIAI_DOAN);
}

SDL_Texture* TaiAnh(const char* duong_dan) {
    SDL_Surface* tam = IMG_Load(duong_dan);
    if (!tam) {
        cerr << "Khong tai duoc anh: " << duong_dan << " SDL_Error: " << SDL_GetError() << endl;
        return nullptr;
    }
    SDL_Texture* anh = SDL_CreateTextureFromSurface(ve_hinh, tam);
    SDL_FreeSurface(tam);
    return anh;
}

void KhoiTaoSDL() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    cua_so = SDL_CreateWindow("Game Tron Me", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RONG_MAN_HINH, CAO_MAN_HINH, SDL_WINDOW_SHOWN);
    ve_hinh = SDL_CreateRenderer(cua_so, -1, SDL_RENDERER_ACCELERATED);
    srand(time(0));

    anh_nen = TaiAnh("room_background.png");
    anh_me = TaiAnh("mom_stern.png");
    anh_tuan_choi = TaiAnh("TuanChoiGame.png");
    anh_tuan_hoc = TaiAnh("TuanHocBai.png");
    nhac_hoc_bai = Mix_LoadMUS("study.wav");
    nhac_game = Mix_LoadMUS("choigame.mp3");

    TronGiaiDoan();
}

void XuLySuKien() {
    SDL_Event su_kien;
    while (SDL_PollEvent(&su_kien)) {
        if (su_kien.type == SDL_QUIT) {
            dang_chay = false;
        }
        if (su_kien.type == SDL_MOUSEBUTTONDOWN) {
            if (!me_dang_xuat_hien && !me_dang_kiem_tra && so_lan_con_lai > 0) {
                me_dang_xuat_hien = true;
                vi_tri_meX = RONG_MAN_HINH;
                so_lan_con_lai--;
            }
        }
    }
}

void CapNhat() {
    Uint32 thoi_gian_hien_tai = SDL_GetTicks();
    if (thoi_gian_hien_tai - thoi_gian_chuyen_giai_doan >= THOI_GIAN_MOI_GIAI_DOAN) {
        thoi_gian_chuyen_giai_doan = thoi_gian_hien_tai;
        if (giai_doan_hien_tai < TONG_GIAI_DOAN - 1) giai_doan_hien_tai++;
    }

    dang_choi_game = giai_doan_choi[giai_doan_hien_tai];

    if (me_dang_xuat_hien) {
        vi_tri_meX -= TOC_DO_ME;
        if (vi_tri_meX <= RONG_MAN_HINH - 500) {
            me_dang_xuat_hien = false;
            me_dang_kiem_tra = true;
            thoi_gian_bat_dau_kiem_tra = SDL_GetTicks();
        }
    }

    if (me_dang_kiem_tra) {
        float xac_suat = XacSuatTron(SO_LAN_ME_KIEM_TRA - so_lan_con_lai);
        if (dang_choi_game) {
            if ((rand() % 100) / 100.0f <= xac_suat) {
                dang_choi_game = false;
            } else {
                cout << "Me bat qua tang!" << endl;
                dang_chay = false;
            }
        }
        if (SDL_GetTicks() - thoi_gian_bat_dau_kiem_tra >= THOI_GIAN_ME_KIEM_TRA) {
            me_dang_kiem_tra = false;
            vi_tri_meX = RONG_MAN_HINH;
        }
    }

    if (so_lan_con_lai == 0) {
        cout << "Ket thuc game!" << endl;
        dang_chay = false;
    }
}

void VeManHinh() {
    SDL_RenderClear(ve_hinh);
    SDL_RenderCopy(ve_hinh, anh_nen, NULL, NULL);

    SDL_Rect tuan = {RONG_MAN_HINH / 2 - 400, CAO_MAN_HINH - 350, RONG_TUAN, CAO_TUAN};
    if (dang_choi_game)
        SDL_RenderCopy(ve_hinh, anh_tuan_choi, NULL, &tuan);
    else
        SDL_RenderCopy(ve_hinh, anh_tuan_hoc, NULL, &tuan);

    if (me_dang_xuat_hien || me_dang_kiem_tra) {
        SDL_Rect me = {(int)vi_tri_meX, CAO_MAN_HINH - 400, RONG_ME, CAO_ME};
        SDL_RenderCopy(ve_hinh, anh_me, NULL, &me);
    }

    for (int i = 0; i < so_lan_con_lai; i++) {
        SDL_SetRenderDrawColor(ve_hinh, 255, 0, 0, 255);
        SDL_Rect tron = {50 + i * 30, CAO_MAN_HINH - 50, 20, 20};
        SDL_RenderFillRect(ve_hinh, &tron);
    }

    SDL_RenderPresent(ve_hinh);
}

void GiaiPhong() {
    SDL_DestroyTexture(anh_me);
    SDL_DestroyTexture(anh_nen);
    SDL_DestroyTexture(anh_tuan_choi);
    SDL_DestroyTexture(anh_tuan_hoc);
    Mix_FreeMusic(nhac_hoc_bai);
    Mix_FreeMusic(nhac_game);
    SDL_DestroyRenderer(ve_hinh);
    SDL_DestroyWindow(cua_so);
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void RunGameAsMom() {
     KhoiTaoSDL();
    while (dang_chay) {
        XuLySuKien();
        CapNhat();
        VeManHinh();
        SDL_Delay(16);
    }
    GiaiPhong();
}



void HandleMenuEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x, y = event.button.y;
            if (x >= 150 && x <= 250 && y >= 370 && y <= 470) {
                RunGameAsChild();
            }
            if (x >= SCREEN_WIDTH - 250 && x <= SCREEN_WIDTH - 150 && y >= 370 && y <= 470) {
                RunGameAsMom();
            }
        }
    }
}

void RenderMenu() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menuBackground, NULL, NULL);

    SDL_Rect buttonConRect = {150, 370, 100, 100};
    SDL_Rect buttonMeRect = {SCREEN_WIDTH - 250, 370, 100, 100};

    SDL_RenderCopy(renderer, buttonCon, NULL, &buttonConRect);
    SDL_RenderCopy(renderer, buttonMe, NULL, &buttonMeRect);
    SDL_RenderPresent(renderer);
}


int main(int argc, char* argv[]) {
    InitSDL();
    menuBackground = LoadTexture("menu_background.png", renderer);
    buttonCon = LoadTexture("button_con.png", renderer);
    buttonMe = LoadTexture("button_me.png", renderer);

    while (running) {
        HandleMenuEvents();
        RenderMenu();
        SDL_Delay(16);
    }

    CleanUp();
    return 0;
}
