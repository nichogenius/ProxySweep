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
#define HISTORY_DEPTH 3
#define NEW_STATE -1
#define ANIMATION_START 32000
#define ANIMATION_STEPS 10

typedef struct buffer_node_t {
    int hist[HISTORY_DEPTH];
} buffer_node;

buffer_node** render_buffer;
int** render_state;
int** board;
int col_s;
int row_s;



void freeRenderBuffer() {
    for (int i = 0; i < col_s; i++) {
        free(render_buffer[i]);
        free(render_state[i]);
    }
    free(render_buffer);
    free(render_state);
}


void initRenderBuffer() {
    render_buffer = (buffer_node**)malloc(sizeof(buffer_node*) * col_s);
    render_state = (int**)malloc(sizeof(int*) * col_s);
    for (int i = 0; i < col_s; i++) {
        render_buffer[i] = (buffer_node*)malloc(sizeof(buffer_node) * row_s);
        render_state[i] = (int*)malloc(sizeof(int) * row_s);
        for (int j = 0; j < row_s; j++) {
            for (int k = 0; k < HISTORY_DEPTH; k++) {
                render_buffer[i][j].hist[k] = 0;
            }
            render_state[i][j] = 0;
        }
    }
}

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

void drawTextureWithRotateSizeAlpha(int x, int y, SDL_Texture* tex, double degrees, int size) {
    SDL_Rect pos;
    float s = size/100.0;
    pos.x = x + (16 - 16 * s);
    pos.y = y + (16 - 16 * s);
    pos.w = 32 * s;
    pos.h = 32 * s;
    SDL_RenderCopyEx(ren, tex, NULL, &pos, degrees, NULL, SDL_FLIP_NONE);
}

SDL_Texture* mapStateToTexture(int state) {
 switch (state) {
        case UNVISITED:
            return unpressed;
        case FLAG:
            return flag;
        case QUESTION:
            return question;
        case DETONATE:
            return mine;
        case MINE:
            return mine;
        case BAD_FLAG:
            return flag_wrong;
        case BAD_QUESTION:
            return question_wrong;
        case 0:
            return pressed;
        default:
            if (state <= 8)
                return numbers[state-1];
            else {
                printf("Invalid tile state.\n");
                exit(1);
            }
    }
}

void drawAnimation(int row, int col, int state) {
    int x = col * 32;
    int y = row * 32;
    int* r_state = &(render_state[col][row]);
    if (*r_state == NEW_STATE) {
        *r_state = ANIMATION_START + 10;
    }
    if (*r_state != 0) {
        (*r_state)--;
        if (*r_state < ANIMATION_START - ANIMATION_STEPS)
            *r_state = 0;
    }
    if (*r_state == 0) {
        drawTexture(x, y, mapStateToTexture(state));
    }
    else if (*r_state > ANIMATION_START) {
        drawTexture(x, y, mapStateToTexture(render_buffer[col][row].hist[1]));
    }
    else {
        drawTexture(x, y, mapStateToTexture(render_buffer[col][row].hist[1]));
        int step = ((ANIMATION_START - *r_state));
        double deg = 90 - step * 9;
        drawTextureWithRotateSizeAlpha(x, y, mapStateToTexture(state), deg, step * 10);
    }
}

void updateRenderBuffer(int row, int col, int state) {
    if (render_buffer[col][row].hist[0] != state) {
        for (int i = HISTORY_DEPTH-1; i > 0; i--) {
            render_buffer[col][row].hist[i] = render_buffer[col][row].hist[i-1];
        }
        render_buffer[col][row].hist[0] = state;
        render_state[col][row] = NEW_STATE;
    }
}

int drawTile(int row, int col, int state) {
    updateRenderBuffer(row, col, state);
    drawAnimation(row,col,state);
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
    SDL_SetTextureAlphaMod(pressed, 127);
    SDL_SetTextureBlendMode(pressed, SDL_BLENDMODE_BLEND);
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
}

void gameLoop() {
    col_s = getColumns();
    row_s = getRows();
    initRenderBuffer();
    int sx = col_s * 32;
    int sy = row_s * 32;
    win = SDL_CreateWindow("ProxySweep", 100, 100, sx, sy, SDL_WINDOW_SHOWN);
    SDL_PTR_ERR(__LINE__, win);
    ren = NULL;
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_PTR_ERR(__LINE__, ren);
    SDL_SetRenderDrawColor(ren, 0, 127, 127, 255);
    initTextures();
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
                int col = x/32;
                int row = y/32;
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
    while (SDL_PollEvent(&e));
    freeRenderBuffer();
    SDL_DestroyWindow(win);
}
