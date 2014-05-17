#include <SDL2/SDL.h>
#include <string.h>
#include "interface.h"

SDL_Window* win;
SDL_Texture* mine;
SDL_Texture* pressed;
SDL_Texture* unpressed;
SDL_Texture* flag;
SDL_Texture* flag_wrong;
SDL_Texture* question;
SDL_Texture* question_wrong;
SDL_Texture* numbers[8];
SDL_Renderer*  ren;

#define CLICK_DELAY 250
#define SDL_PTR_ERR(line, name) if (name == NULL) {printf("Line %u: %s: %s\n", line, #name, SDL_GetError()); exit(1);}

int** board;
int col_s;
int row_s;

void showMessage(char * msg, char * title)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, msg, win);
}

void drawTexture(int x, int y, SDL_Texture* tex) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    pos.w = 32;
    pos.h = 32;
    SDL_RenderCopy(ren, tex, NULL, &pos);
}

int drawTile(int row, int col, int state) {
    int x = row * 32;
    int y = col * 32;
    //printf("Render\n");
    switch (state) {
        case UNVISITED:
            drawTexture(x, y, unpressed);
            break;
        case UNVISITED_MINE:
            drawTexture(x, y, unpressed);
            break;
        case FLAG:
            drawTexture(x, y, flag);
            break;
        case QUESTION:
            drawTexture(x, y, question);
            break;
        case FLAG_MINE:
            drawTexture(x, y, flag);
            break;
        case QUESTION_MINE:
            drawTexture(x, y, question);
            break;
        case DETONATE:
            //drawTexture(x, y, mine);_
            break;
        case MINE:
            drawTexture(x, y, mine);
            break;
        case BAD_FLAG:
            drawTexture(x, y, flag_wrong);
            break;
        case BAD_QUESTION:
            drawTexture(x, y, question_wrong);
            break;
        case 0:
            drawTexture(x, y, pressed);
            break;
        default:
            if (state <= 8)
                drawTexture(x, y, numbers[state-1]);
            else {
                printf("Invalid tile state.\n");
                exit(1);
            }
    }
}

void renderBoard() {
    SDL_RenderClear(ren);
    for (int col = 0; col < col_s; col++)  {
        for (int row = 0; row < row_s; row++) {
            drawTile(row, col , board[col][row]);
        }
    }
    SDL_RenderPresent(ren);
}


void initTextures() {
    SDL_Surface* s = SDL_LoadBMP("textures/bomb.bmp");
    SDL_PTR_ERR(__LINE__, s);
    mine = SDL_CreateTextureFromSurface(ren, s);
    SDL_PTR_ERR(__LINE__, mine);
    SDL_FreeSurface(s);
    s = SDL_LoadBMP("textures/base_unpressed.bmp");
    SDL_PTR_ERR(__LINE__, s);
    unpressed = SDL_CreateTextureFromSurface(ren, s);
    SDL_PTR_ERR(__LINE__, unpressed);
    SDL_FreeSurface(s);
    s = SDL_LoadBMP("textures/base_pressed.bmp");
    SDL_PTR_ERR(__LINE__, s);
    pressed = SDL_CreateTextureFromSurface(ren, s);
    SDL_PTR_ERR(__LINE__, pressed);
    SDL_FreeSurface(s);
    s = SDL_LoadBMP("textures/flag.bmp");
    SDL_PTR_ERR(__LINE__, s);
    flag = SDL_CreateTextureFromSurface(ren, s);
    SDL_PTR_ERR(__LINE__, flag);
    SDL_FreeSurface(s);
    s = SDL_LoadBMP("textures/flag_wrong.bmp");
    SDL_PTR_ERR(__LINE__, s);
    flag_wrong = SDL_CreateTextureFromSurface(ren, s);
    SDL_PTR_ERR(__LINE__, flag_wrong);
    SDL_FreeSurface(s);
    s = SDL_LoadBMP("textures/question.bmp");
    SDL_PTR_ERR(__LINE__, s);
    question = SDL_CreateTextureFromSurface(ren, s);
    SDL_PTR_ERR(__LINE__, question);
    SDL_FreeSurface(s);
    s = SDL_LoadBMP("textures/question_wrong.bmp");

    SDL_PTR_ERR(__LINE__, s);
    question_wrong = SDL_CreateTextureFromSurface(ren, s);
    SDL_PTR_ERR(__LINE__, question_wrong);
    SDL_FreeSurface(s);
    for(int i = 1; i < 9; i++) {
        char filename[100];
        sprintf(filename, "textures/%u.bmp", i);
        s = SDL_LoadBMP(filename);
        SDL_PTR_ERR(__LINE__, s);
        numbers[i-1] = SDL_CreateTextureFromSurface(ren, s);
        SDL_PTR_ERR(__LINE__, numbers[i-1]);
        SDL_FreeSurface(s);
    }
}

void initVideo() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        printf("%s\n", SDL_GetError());
        exit(1);
    }
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_PTR_ERR(__LINE__, win);
    ren = NULL;
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_PTR_ERR(__LINE__, ren);
    initTextures();
}

void video_loop() {
    col_s = getColumns();
    row_s = getRows();
    int sx = row_s * 32;
    int sy = col_s * 32;
    win = SDL_CreateWindow("ProxySweep", 100, 100, sx, sy, SDL_WINDOW_SHOWN);
    SDL_Event e;
    int quit = 0;
    Uint32 ticks = 0;
    int game_state = ONGOING;
    board = getPointer();
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                Uint32 s = SDL_GetMouseState(&x, &y);
                int col = y/32;
                int row = x/32;
                if (s & SDL_BUTTON(1)) {
                    if (SDL_GetTicks() - ticks < CLICK_DELAY)
                        game_state = doubleClick(col, row);
                    else {
                        game_state = buttonPressed(col, row, LEFT);
                    }
                    ticks = SDL_GetTicks();
                }
                else if (s & SDL_BUTTON(3)) {
                    //right button
                    game_state = buttonPressed(col, row, RIGHT);
                }
            }
        }
        board = getPointer();
        renderBoard();
        switch (game_state) {
            case GAME_END_SUCCESS:
                printf("You won :)\n");
                showMessage("YOU WIN!!!", "Congratulations");
                quit = 1;
                break;
            case GAME_END_FAIL:
                printf("You lost :(\n");
                showMessage("YOU LOSE!!!", "I'm Sorry...");
                quit = 1;
                break;
            case ONGOING:
                //printf("Ongoing..\n");
                break;
        }
    }
    SDL_DestroyWindow(win);
}
