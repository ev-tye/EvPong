#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

void P_Update();
bool P_CheckCollision(int ball_pos_x, int ball_pos_y);
int P_GetPosX();
int P_GetPosY();
void P_Reset();

#endif