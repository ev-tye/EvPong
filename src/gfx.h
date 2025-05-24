#ifndef GFX_H
#define GFX_H

#include <stdbool.h>

#define G_SCREEN_WIDTH      640
#define G_SCREEN_HEIGHT     480

bool G_Init();
void G_Stop();
void G_ClearBackBuffer();
void G_SwapBuffers();
void G_DrawPaddle(int pos_x, int pos_y);
void G_DrawBall(int pos_x, int pos_y);
void G_DrawScore(int score, int pos_x, int pos_y, int scale);

#endif