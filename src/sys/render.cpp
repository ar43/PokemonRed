#include "system.h"


void Render::render()
{
    SDL_SetRenderDrawColor(sys.getRenderer(), 0xFF, 0xFF, 0xFF, 255);
    SDL_RenderClear(sys.getRenderer());

    static int colors[9][10][3];
    if(game.frame.getFrame() == 0)
    { 
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                colors[i][j][0] = rand() % 256;
                colors[i][j][1] = rand() % 256;
                colors[i][j][2] = rand() % 256;
            }
        }
    }
    
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            SDL_Rect rect = { j*32 + GAME_WIDTH / 2 - (int)game.player.x,i*32 + GAME_HEIGHT / 2 - (int)game.player.y,32,32 };
            SDL_SetRenderDrawColor(sys.getRenderer(), colors[i][j][0], colors[i][j][1], colors[i][j][2], 255);
            SDL_RenderFillRect(sys.getRenderer(), &rect);
        }
    }

    SDL_SetRenderDrawColor(sys.getRenderer(), 255, 0, 0, 255);
    SDL_Rect rect = { 64,60,16,16 };
    SDL_RenderFillRect(sys.getRenderer(), &rect);

    /* Up until now everything was drawn behind the scenes.
       This will show the new, red contents of the window. */
    SDL_RenderPresent(sys.getRenderer());

}