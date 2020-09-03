#include "system.h"


void Render::render()
{
    SDL_SetRenderDrawColor(sys.getRenderer(), 0xAA, 0xAA, 0xAA, 255);
    SDL_RenderClear(sys.getRenderer());

    test();

    SDL_RenderPresent(sys.getRenderer());
}


void Render::test()
{
    static Uint8 colors[9][10][4];
    Block *test_b = res.getBlockset("overworld");
    if (game.frame.getFrame() == 0)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                colors[i][j][0] = rand() % 256;
                colors[i][j][1] = rand() % 256;
                colors[i][j][2] = rand() % 256;
                colors[i][j][3] = rand() % 128;
            }
        }
    }

    /*
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            SDL_Rect rect = { j * 32 + GAME_WIDTH / 2 - game.player.x - WORLD_OFFSET_X,i * 32 + GAME_HEIGHT / 2 - game.player.y - WORLD_OFFSET_Y,32,32 };
            SDL_SetRenderDrawColor(sys.getRenderer(), colors[i][j][0], colors[i][j][1], colors[i][j][2], 255);
            SDL_RenderFillRect(sys.getRenderer(), &rect);
        }
    }
    */
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            test_b[colors[i][j][3]].render(j * 32 + GAME_WIDTH / 2 - game.player.x - WORLD_OFFSET_X, i * 32 + GAME_HEIGHT / 2 - game.player.y - WORLD_OFFSET_Y);
        }
    }

    //Tileset* test_t = res.getTileset("overworld");
    //SDL_Rect rected = { GAME_WIDTH / 2 - game.player.x - WORLD_OFFSET_X,GAME_HEIGHT / 2 - game.player.y - WORLD_OFFSET_Y,test_t->surface->w,test_t->surface->h };
    //SDL_RenderCopyEx(sys.getRenderer(), test_t->texture, NULL, &rected, 0.0f, NULL, SDL_FLIP_NONE);


    SDL_SetRenderDrawColor(sys.getRenderer(), 255, 0, 0, 255);
    SDL_Rect rect = { PLAYER_OFFSET_X, PLAYER_OFFSET_Y,16,16 };
    SDL_RenderFillRect(sys.getRenderer(), &rect);
}

void Block::render(int x, int y)
{
    SDL_Rect rected = { x,y,32,32 };
    SDL_RenderCopyEx(sys.getRenderer(), texture, NULL, &rected, 0.0f, NULL, SDL_FLIP_NONE);
}