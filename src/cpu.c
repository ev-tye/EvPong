#include "cpu.h"

#include <stdlib.h>
#include "ball.h"

#define START_X             630
#define START_Y             240
#define BOUNDS_UP           10
#define BOUNDS_DOWN         420
#define BOUNDS_PADDING      5
#define PADDLE_WIDTH        10
#define PADDLE_HEIGHT       50
#define REACTION_THRESHOLD  25
#define MAX_SPEED           8

static int pos_x = START_X;
static int pos_y = START_Y;
static int frame_count = 0;
static int move_speed = 10;

void C_Update()
{
    if(B_GetPosX() > 320)
    {
        int ball_y = B_GetPosY();
        int center_y = pos_y + (PADDLE_HEIGHT / 2);
        int diff = ball_y - center_y;

        if(abs(diff) > REACTION_THRESHOLD)
        {
            if(diff > 0) pos_y += MAX_SPEED;
            else pos_y -= MAX_SPEED;
        }
    }
}

bool C_CheckCollision()
{
    int ball_x = B_GetPosX();
    int ball_y = B_GetPosY();
    int paddle_right = pos_x + PADDLE_WIDTH;
    int paddle_bottom = pos_y + PADDLE_HEIGHT;
    int ball_right = ball_x + 10;
    int ball_bottom = ball_y + 10;
    return ball_x < paddle_right && ball_right > pos_x && ball_y < paddle_bottom && ball_bottom > pos_y;
}

void C_Reset()
{
    pos_x = START_X;
    pos_y = START_Y;
}

int C_GetPosX() { return pos_x; }
int C_GetPosY() { return pos_y; }