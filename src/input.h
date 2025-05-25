#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

bool I_Init();
void I_Stop();
void I_Update();
bool I_MoveUp();
bool I_MoveDown();
bool I_QuitCalled();

#endif