#include "system.h"


void Render::render()
{
    SDL_SetRenderDrawColor(sys.getRenderer(), 0xAA, 0xAA, 0xAA, 255);
    SDL_RenderClear(sys.getRenderer());

    draw_map();
    debug();
    game.player.render();
    draw_overlay();

    

    SDL_RenderPresent(sys.getRenderer());
}

void Render::draw_overlay()
{
    if (!game.world.currentMap->grassEffect.empty())
    {
        for (std::vector<Position>::iterator it = game.world.currentMap->grassEffect.begin(); it != game.world.currentMap->grassEffect.end(); ++it)
        {
            if (it->y > PLAYER_OFFSET_Y + 4)
            {
                Texture* grass = res.getTexture(game.world.currentMap->tileset->grassName);
                grass->render(it->x, it->y);
            }
            else if (it->y > PLAYER_OFFSET_Y)
            {
                Texture* grass = res.getTexture(game.world.currentMap->tileset->grassName);
                grass->render_grass(it->x, it->y);
            }
        }
    }

    if (game.player.warpIndex < 32 && game.player.warpIndex >= 24)
    {
        SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 0, 255);
        SDL_Rect screen = { 0,0,GAME_WIDTH,GAME_HEIGHT };
        SDL_RenderFillRect(sys.getRenderer(), &screen);
    }
    else if (game.player.warpIndex < 40 && game.player.warpIndex >= 24)
    {
        SDL_SetRenderDrawColor(sys.getRenderer(), 255, 255, 255, 255);
        SDL_Rect screen = { 0,0,GAME_WIDTH,GAME_HEIGHT };
        SDL_RenderFillRect(sys.getRenderer(), &screen);
    }
    else if (game.player.warpIndex < 47 && game.player.warpIndex >= 24)
    {
        SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 0, 255);
        SDL_Rect screen = { 0,0,GAME_WIDTH,GAME_HEIGHT };
        SDL_RenderFillRect(sys.getRenderer(), &screen);
    }
}

void Render::draw_map()
{

    if (game.world.currentMap == nullptr)
        sys.error("Current map is a null pointer");

    game.world.currentMap->grassEffect.clear();

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

    if (west == nullptr)
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

    if (east == nullptr)
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

    if (north == nullptr)
    {
        for (int i = -3; i < game.world.currentMap->width + 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int bkg = game.world.currentMap->background;
                game.world.currentMap->blockset->blocks[bkg].render(i, -1 - j);
            }
        }
    }

    if (south == nullptr)
    {
        for (int i = -3; i < game.world.currentMap->width + 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int bkg = game.world.currentMap->background;
                game.world.currentMap->blockset->blocks[bkg].render(i, j + game.world.currentMap->height);
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
    if (game.debug.drawPlayer)
    {
        SDL_SetRenderDrawColor(sys.getRenderer(), 255, 0, 0, 255);
        SDL_Rect rect = { PLAYER_OFFSET_X, PLAYER_OFFSET_Y,16,16 };
        SDL_RenderFillRect(sys.getRenderer(), &rect);
    }

    if (game.debug.drawSquare)
    {
        SDL_SetRenderDrawColor(sys.getRenderer(), 255, 0, 255, 255);
        SDL_Rect rect1 = { PLAYER_OFFSET_X, PLAYER_OFFSET_Y + 4,16,16 };
        SDL_RenderFillRect(sys.getRenderer(), &rect1);
    }
}

void Sprite::render_static(int x, int y, Direction dir)
{
    int offset = 0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    switch (dir)
    {
    case Direction::DOWN:
    {
        if (animIndex % 36 < 9)
        {
            offset = 0;
        }
        else if (animIndex % 36 < 18)
        {
            offset = 48;
        }
        else if (animIndex % 36 < 27)
        {
            offset = 0;
        }
        else
        {
            offset = 48;
            flip = SDL_FLIP_HORIZONTAL;
        }
        break;
    }
    case Direction::LEFT:
    {
        if (animIndex % 18 < 9)
        {
            offset = 32;
        }
        else
        {
            offset = 80;
        }
        break;
    }
    case Direction::RIGHT:
    {
        if (animIndex % 18 < 9)
        {
            offset = 32;
        }
        else
        {
            offset = 80;
        }
        flip = SDL_FLIP_HORIZONTAL;
        break;
    }
    case Direction::UP:
    {
        if (animIndex % 36 < 9)
        {
            offset = 16;
        }
        else if (animIndex % 36 < 18)
        {
            offset = 64;
        }
        else if (animIndex % 36 < 27)
        {
            offset = 16;
        }
        else
        {
            offset = 64;
            flip = SDL_FLIP_HORIZONTAL;
        }
        break;
    }
    }

    SDL_Rect rectSrc = { 0,offset,16,16 };
    SDL_Rect rectDest = { x,y,16,16 };

    if (game.player.warpIndex < 8)
    {
        SDL_SetTextureColorMod(texture, 255, 255, 255);
    }
    else if (game.player.warpIndex < 16)
    {
        SDL_SetTextureColorMod(texture, 128, 128, 128);
    }
    else if (game.player.warpIndex < 24)
    {
        SDL_SetTextureColorMod(texture, 16, 16, 16);
    }

    SDL_RenderCopyEx(sys.getRenderer(), texture, &rectSrc, &rectDest, 0.0f, NULL, flip);

}