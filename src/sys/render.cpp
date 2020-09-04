#include "system.h"


void Render::render()
{
    SDL_SetRenderDrawColor(sys.getRenderer(), 0xAA, 0xAA, 0xAA, 255);
    SDL_RenderClear(sys.getRenderer());

    draw_map();
    test();

    SDL_RenderPresent(sys.getRenderer());
}

void Render::draw_map()
{
    //static rendering is a bad idea
    /*
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int bkg = game.world.currentMap->background;
            game.world.currentMap->blockset->blocks[bkg].render_static(j,i);
        }
    }
    */

    Map* north = res.getMap(game.world.currentMap->connection.north);
    Map* west = res.getMap(game.world.currentMap->connection.west);
    Map* east = res.getMap(game.world.currentMap->connection.east);
    Map* south = res.getMap(game.world.currentMap->connection.south);

    //todo: north and south background blocks

    if (north != nullptr)
    {
        north->render(0, -north->height);
    }

    if (west != nullptr)
    {
        west->render(-west->width, 0);
    }
    else
    {
        for (int i = -3; i < game.world.currentMap->height + 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int bkg = game.world.currentMap->background;
                game.world.currentMap->blockset->blocks[bkg].render(-1 -j, i);
            }
        }
    }

    if (east != nullptr)
    {
        east->render(game.world.currentMap->width, 0);
    }
    else
    {
        for (int i = -3; i < game.world.currentMap->height + 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int bkg = game.world.currentMap->background;
                game.world.currentMap->blockset->blocks[bkg].render(j+game.world.currentMap->width, i);
            }
        }
    }

    if (south != nullptr)
    {
        south->render(0, game.world.currentMap->height);
    }

    game.world.currentMap->render(0, 0);
}


void Render::test()
{
    /*
    static Uint8 colors[9][10][4];
    Blockset *test_b = res.getBlockset("overworld");
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

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            test_b->blocks[colors[i][j][3]].render(j, i);
        }
    }
    */


    //Tileset* test_t = res.getTileset("overworld");
    //SDL_Rect rected = { GAME_WIDTH / 2 - game.player.x - WORLD_OFFSET_X,GAME_HEIGHT / 2 - game.player.y - WORLD_OFFSET_Y,test_t->surface->w,test_t->surface->h };
    //SDL_RenderCopyEx(sys.getRenderer(), test_t->texture, NULL, &rected, 0.0f, NULL, SDL_FLIP_NONE);


    SDL_SetRenderDrawColor(sys.getRenderer(), 255, 0, 0, 255);
    SDL_Rect rect = { PLAYER_OFFSET_X, PLAYER_OFFSET_Y,16,16 };
    SDL_RenderFillRect(sys.getRenderer(), &rect);
}