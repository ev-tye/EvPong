#include "ball.h"
#include "cpu.h"
#include "gfx.h"
#include "input.h"
#include "player.h"
#include "sound.h"

#define P_SCORE_POS_X       50
#define C_SCORE_POS_X       590
#define SCORE_POS_Y         10
#define SCORE_FONT_SCALE    6

int p_score = 0;
int c_score = 0;

int main(int argc, char* argv[])
{
    if(!I_Init()) return -1;
    if(!G_Init())
    {
        I_Stop();
        return -1;
    }

    if(!S_Init())
    {
        G_Stop();
        I_Stop();
        return -1;
    }

    while(!I_QuitCalled())
    {
        I_Update();
        P_Update();
        C_Update();
        B_Update();

        if(B_HitWall())
        {
            B_FlipY();
            S_PlayBoop();
        }

        if(P_CheckCollision(B_GetPosX(), B_GetPosY()) || C_CheckCollision())
        {
            B_FlipX();
            S_PlayBeep();
        }

        if(B_OverCpuLine())
        {
            S_PlayBeep();
            S_PlayBoop();
            S_PlayBeep();
            S_PlayBoop();
            P_Reset();
            C_Reset();
            B_Reset();
            p_score++;
        }
        
        if(B_OverPlayerLine())
        {
            S_PlayBeep();
            S_PlayBoop();
            S_PlayBeep();
            S_PlayBoop();
            P_Reset();
            C_Reset();
            B_Reset();
            c_score++;
        }


        G_ClearBackBuffer();
        G_DrawPaddle(P_GetPosX(), P_GetPosY());
        G_DrawPaddle(C_GetPosX(), C_GetPosY());
        G_DrawBall(B_GetPosX(), B_GetPosY());
        G_DrawScore(p_score, P_SCORE_POS_X, SCORE_POS_Y, SCORE_FONT_SCALE);
        G_DrawScore(c_score, C_SCORE_POS_X, SCORE_POS_Y, SCORE_FONT_SCALE);
        G_SwapBuffers();
    }

    S_Stop();
    G_Stop();
    I_Stop();

    return 0;
}