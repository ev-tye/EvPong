#ifndef BALL_H
#define BALL_H

#include <stdbool.h>

void B_Update();
void B_Reset();
bool B_OverPlayerLine();
bool B_OverCpuLine();
int B_GetPosX();
int B_GetPosY();
bool B_HitWall();
void B_FlipX();
void B_FlipY();

#endif