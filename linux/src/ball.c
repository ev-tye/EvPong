#include "ball.h"

#include <stdlib.h>
#include <time.h>

#define BALL_RADIUS     10
#define START_X         310
#define START_Y         230
#define BALL_SPEED      5

static int pos_x = START_X;
static int pos_y = START_Y;
static int velocity_x = 5;
static int velocity_y = 5;

void B_Update()
{
    pos_x += velocity_x;
    pos_y += velocity_y;
}

void B_Reset()
{
    srand(time(NULL));

    bool cpu_serves = rand() > 10000 ? true : false;

    pos_x = START_X;
    pos_y = START_Y;

    if(!cpu_serves)
    {
        velocity_x = BALL_SPEED;
        velocity_y = BALL_SPEED;
    }
    else
    {
        velocity_x = -BALL_SPEED;
        velocity_y = -BALL_SPEED;
    }
}

bool B_OverPlayerLine()     { return pos_x < -BALL_RADIUS - 60 ? true : false; }
bool B_OverCpuLine()        { return pos_x > 700 + BALL_RADIUS ? true : false; }
bool B_HitWall()            { return (pos_y - BALL_RADIUS < 0) || (pos_y + BALL_RADIUS > 480) ? true : false; }
int B_GetPosX()             { return pos_x; }
int B_GetPosY()             { return pos_y; }
void B_FlipX()              { velocity_x = -velocity_x; }
void B_FlipY()              { velocity_y = -velocity_y; }