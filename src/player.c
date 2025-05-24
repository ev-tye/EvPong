#include "player.h"

#include "input.h"

#define START_X         0
#define START_Y         240
#define BOUNDS_UP       10
#define BOUNDS_DOWN     420
#define BOUNDS_PADDING  10
#define PADDLE_WIDTH    10
#define PADDLE_HEIGHT   50

static int pos_x = START_X;
static int pos_y = START_Y;

void P_Update()
{
    if(I_MoveUp())          pos_y -= 10;
    if(I_MoveDown())        pos_y += 10;
    if(pos_y < BOUNDS_UP)   pos_y += BOUNDS_PADDING;
    if(pos_y > BOUNDS_DOWN) pos_y -= BOUNDS_PADDING;
}

bool P_CheckCollision(int ball_pos_x, int ball_pos_y)
{
    int paddle_right = pos_x + PADDLE_WIDTH;
    int paddle_bottom = pos_y + PADDLE_HEIGHT;
    int ball_right = ball_pos_x + 10;
    int ball_bottom = ball_pos_y + 10;
    return ball_pos_x < paddle_right && ball_right > pos_x && ball_pos_y < paddle_bottom && ball_bottom > pos_y;
}

int P_GetPosX() { return pos_x; }
int P_GetPosY() { return pos_y; }
void P_Reset()  { pos_x = START_X; pos_y = START_Y; }