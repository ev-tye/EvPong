#include "gfx.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

#define WINDOW_TITLE        "EvPong"
#define COLOUR_RGB(r, g, b)  (0xFF000000 | ((r) << 16) | ((g) << 8) | (b))

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;       // Software rendered in my code, but this is needed to copy the framebuffer to (quirk of SDL)
static SDL_Texture* frame_buffer = NULL;    // "Framebuffer" to write the pixel data to
static uint32_t* fb_data = NULL;            // The pixels for the framebuffer

// Basic 3x5 font map for numbers
static const uint8_t font_map[10][8] = 
{
    { 0b111, 0b101, 0b101, 0b101, 0b111 }, // 0
    { 0b010, 0b110, 0b010, 0b010, 0b111 }, // 1
    { 0b111, 0b001, 0b111, 0b100, 0b111 }, // 2
    { 0b111, 0b001, 0b111, 0b001, 0b111 }, // 3
    { 0b101, 0b101, 0b111, 0b001, 0b001 }, // 4
    { 0b111, 0b100, 0b111, 0b001, 0b111 }, // 5
    { 0b111, 0b100, 0b111, 0b101, 0b111 }, // 6
    { 0b111, 0b001, 0b001, 0b010, 0b010 }, // 7
    { 0b111, 0b101, 0b111, 0b101, 0b111 }, // 8
    { 0b111, 0b101, 0b111, 0b001, 0b111 }  // 9
};

static void DrawDigit(int digit, int x, int y, int scale)
{
    if(digit < 0 || digit > 9) return;

    for(int row = 0; row < 5; ++row)
    {
        uint8_t row_bits = font_map[digit][row];
        for(int col = 0; col < 3; ++col)
        {
            if((row_bits >> (2 - col)) & 1)
            {
                for(int sy = 0; sy < scale; ++sy)
                {
                    for(int sx = 0; sx < scale; ++sx)
                    {
                        int px = x + col * scale + sx;
                        int py = y + row * scale + sy;
                        if(px >= 0 && px < G_SCREEN_WIDTH && py >= 0 && py < G_SCREEN_HEIGHT)
                        {
                            fb_data[py * G_SCREEN_WIDTH + px] = COLOUR_RGB(255, 255, 255);
                        }
                    }
                }
            }
        }
    }
}

bool G_Init()
{
    if(!SDL_InitSubSystem(SDL_INIT_VIDEO)) return false;

    window = SDL_CreateWindow(WINDOW_TITLE, G_SCREEN_WIDTH, G_SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
    if(!window)
    {
        G_Stop();
        return false;
    }

    renderer = SDL_CreateRenderer(window, SDL_SOFTWARE_RENDERER);
    if(!renderer)
    {
        G_Stop();
        return false;
    }

    frame_buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, G_SCREEN_WIDTH, G_SCREEN_HEIGHT);
    if(!frame_buffer)
    {
        G_Stop();
        return false;
    }

    fb_data = malloc(G_SCREEN_WIDTH * G_SCREEN_HEIGHT * sizeof(uint32_t));
    if(!fb_data)
    {
        G_Stop();
        return false;
    }

    SDL_CaptureMouse(true);
    SDL_HideCursor();
    return true;
}

void G_Stop()
{
    SDL_ShowCursor();
    SDL_CaptureMouse(false);
    if(fb_data) free(fb_data);
    if(frame_buffer) SDL_DestroyTexture(frame_buffer);
    if(renderer) SDL_DestroyRenderer(renderer);
    if(window) SDL_DestroyWindow(window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void G_ClearBackBuffer()
{
    SDL_memset(fb_data, 0, G_SCREEN_WIDTH * G_SCREEN_HEIGHT * sizeof(uint32_t));
}

void G_SwapBuffers()
{
    SDL_UpdateTexture(frame_buffer, NULL, fb_data, G_SCREEN_WIDTH * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, frame_buffer, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void G_DrawPaddle(int pos_x, int pos_y)
{
    for(int j = 0; j < 50; ++j)
    {
        int py = pos_y + j;
        if(py < 0 || py >= G_SCREEN_HEIGHT) continue;

        for(int i = 0; i < 10; ++i)
        {
            int px = pos_x + i;
            if(px < 0 || px >= G_SCREEN_WIDTH) continue;

            fb_data[py * G_SCREEN_WIDTH + px] = COLOUR_RGB(255, 255, 255);
        }
    }
}

void G_DrawBall(int pos_x, int pos_y)
{
    for(int j = 0; j < 10; ++j)
    {
        int py = pos_y + j;
        if(py < 0 || py >= G_SCREEN_HEIGHT) continue;

        for(int i = 0; i < 10; ++i)
        {
            int px = pos_x + i;
            if(px < 0 || px >= G_SCREEN_WIDTH) continue;

            fb_data[py * G_SCREEN_WIDTH + px] = COLOUR_RGB(255, 255, 255);
        }
    }
}

void G_DrawScore(int score, int pos_x, int pos_y, int scale)
{
    char buffer[12];
    snprintf(buffer, sizeof(buffer), "%d", score);

    for(int i = 0; buffer[i]; ++i)
    {
        int digit = buffer[i] - '0';
        DrawDigit(digit, pos_x + i * (3 * scale + scale), pos_y, scale);
    }
}