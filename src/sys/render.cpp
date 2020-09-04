#include "system.h"


void Render::render()
{
    SDL_SetRenderDrawColor(sys.getRenderer(), 0xAA, 0xAA, 0xAA, 255);
    SDL_RenderClear(sys.getRenderer());

    draw_map();
    debug();

    SDL_RenderPresent(sys.getRenderer());
}

void Render::draw_map()
{

    if (game.world.currentMap == nullptr)
        sys.error("Current map is a null pointer");

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

    if(west == nullptr)
    {
        for (int i = -3; i < game.world.currentMap->height + 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int bkg = game.world.currentMap->background;
                game.world.currentMap->blockset->blocks[bkg].render(-1 - j, i);
            }
        }
    }

    if(east == nullptr)
    {
        for (int i = -3; i < game.world.currentMap->height + 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int bkg = game.world.currentMap->background;
                game.world.currentMap->blockset->blocks[bkg].render(j + game.world.currentMap->width, i);
            }
        }
    }

    if (north != nullptr)
    {
        north->render(game.world.currentMap->connection.northOffset, -north->height);
    }

    if (west != nullptr)
    {
        west->render(-west->width, game.world.currentMap->connection.westOffset);
    }

    if (east != nullptr)
    {
        east->render(game.world.currentMap->width, game.world.currentMap->connection.eastOffset);
    }
    

    if (south != nullptr)
    {
        south->render(game.world.currentMap->connection.southOffset, game.world.currentMap->height);
    }

    game.world.currentMap->render(0, 0);
}


void Render::debug()
{
    if(game.debug.drawPlayer)
    { 
        SDL_SetRenderDrawColor(sys.getRenderer(), 255, 0, 0, 255);
        SDL_Rect rect = { PLAYER_OFFSET_X, PLAYER_OFFSET_Y,16,16 };
        SDL_RenderFillRect(sys.getRenderer(), &rect);
    }

    if(game.debug.drawSquare)
    { 
        SDL_SetRenderDrawColor(sys.getRenderer(), 255, 0, 255, 255);
        SDL_Rect rect1 = { PLAYER_OFFSET_X, PLAYER_OFFSET_Y+4,16,16 };
        SDL_RenderFillRect(sys.getRenderer(), &rect1);
    }
}