#include "system.h"


void Render::render()
{
    SDL_SetRenderDrawColor(sys.getRenderer(), 0xAA, 0xAA, 0xAA, 255);
    SDL_RenderClear(sys.getRenderer());

    draw_map();
    debug();
    draw_objects();
    game.player.render();
    draw_overlay();
    
    game.battle.pre_render();
    game.textbox.render();
    game.battle.render();
    

    SDL_RenderPresent(sys.getRenderer());
}

void Render::draw_objects()
{
    for (auto it : game.world.currentMap->objects)
    {
        it->render();
    }
}


void Render::draw_overlay()
{
    if (!game.world.currentMap->grassEffect.empty())
    {
        bool obj_nearby = false;
        for (std::vector<Position>::iterator it = game.world.currentMap->grassEffect.begin(); it != game.world.currentMap->grassEffect.end(); ++it)
        {
            
            for (auto obj : game.world.currentMap->objects)
            {
                if (!obj->active || !obj->spriteDraw)
                    continue;

                Position obj_pos;
                obj->get_screen_pos(&obj_pos);

                if (obj_pos.y == PLAYER_OFFSET_Y + 16 || obj_pos.y == PLAYER_OFFSET_Y - 16)
                    obj_nearby = true;

                if (it->y > obj_pos.y + 4 && it->y < obj_pos.y + 20 && it->x >= obj_pos.x && it->x < obj_pos.x + 16)
                {
                    
                    Texture* grass = res.getTexture(game.world.currentMap->tileset->grassName);
                    if (obj_nearby)
                        grass->render_grass(it->x, it->y, false);
                    else
                        grass->render(it->x, it->y);
                    //printf("x: %i y: %i\n", obj_pos.x, obj_pos.y);
                }
                else if (it->y > obj_pos.y && it->y < obj_pos.y + 16 && it->x >= obj_pos.x && it->x < obj_pos.x + 16)
                {
                    Texture* grass = res.getTexture(game.world.currentMap->tileset->grassName);
                    grass->render_grass(it->x, it->y,true);
                }

            }

            if (it->y > PLAYER_OFFSET_Y + 4 && it->y < PLAYER_OFFSET_Y + 20 && it->x >= PLAYER_OFFSET_X && it->x < PLAYER_OFFSET_X + 16)
            {
                Texture* grass = res.getTexture(game.world.currentMap->tileset->grassName);
                if (obj_nearby)
                    grass->render_grass(it->x, it->y, false);
                else
                    grass->render(it->x, it->y);
            }
            else if (it->y > PLAYER_OFFSET_Y && it->y < PLAYER_OFFSET_Y + 16 && it->x >= PLAYER_OFFSET_X && it->x < PLAYER_OFFSET_X+16)
            {
                Texture* grass = res.getTexture(game.world.currentMap->tileset->grassName);
                grass->render_grass(it->x, it->y,true);
            }

            //npc grass effect TODO: fix graphical error when player is above or below npc (prolly done after collision)
            //if player is above, turn off grass for player's feet
            //if npc is above, turn off grass for npc feet
            
            
        }
    }

    if (game.player.warpIndex < 38 && game.player.warpIndex >= 30)
    {
        SDL_SetRenderDrawColor(sys.getRenderer(), 255, 255, 255, 255);
        SDL_Rect screen = { 0,0,GAME_WIDTH,GAME_HEIGHT };
        SDL_RenderFillRect(sys.getRenderer(), &screen);
    }

    if (game.battle.battleIndex >= 106 && game.battle.starting)
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

        for (auto it : game.world.currentMap->objects)
        {
            if (it->active && it->spriteDraw)
            {
                Position loc;
                it->get_screen_pos(&loc);
                SDL_SetRenderDrawColor(sys.getRenderer(), 255, 0, 0, 255);
                SDL_Rect rect = { loc.x, loc.y,16,16 };
                SDL_RenderFillRect(sys.getRenderer(), &rect);
            }
        }
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
    static int y_offset = 0;
    if (game.player.jumping)
    {
        if (game.player.jumpIndex < 16 && game.player.jumpIndex > 1)
        {
            if (game.player.jumpIndex % 2 == 1)
                y_offset -= 2;
        }
        else if(game.player.jumpIndex > 1 && game.player.jumpIndex < 31)
        {
            if (game.player.jumpIndex % 2 == 1)
                y_offset += 2;
        }
        res.getTexture("shadow")->render(x, y+8, SDL_FLIP_NONE);
        res.getTexture("shadow")->render(x+8, y+8, SDL_FLIP_HORIZONTAL);
        res.getTexture("shadow")->render(x, y+8+8, SDL_FLIP_VERTICAL);
        res.getTexture("shadow")->render(x+8, y + 8+8, (SDL_RendererFlip)(SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL));
    }
    else
    {
        y_offset = 0;
    }

    SDL_Rect rectSrc = { 0,offset,16,16 };
    SDL_Rect rectDest = { x,y+y_offset,16,16 };

    size_t brightness = BRIGHTNESS_NORMAL;

    if (game.player.warpIndex >= 24)
    {
        brightness = BRIGHTNESS_DARK3;
    }
    else if (game.player.warpIndex >= 16)
    {
        brightness = BRIGHTNESS_DARK3;
    }
    else if (game.player.warpIndex >= 8)
    {
        brightness = BRIGHTNESS_DARK1;
    }

    SDL_RenderCopyEx(sys.getRenderer(), texture[brightness], &rectSrc, &rectDest, 0.0f, NULL, flip);

}

bool Sprite::is_on_screen(Position *pos)
{
    if (!(pos->x >= 0 && pos->x <= GAME_WIDTH - 16 && pos->y >= -4 && pos->y <= GAME_HEIGHT - 12))
        return false;
    else
        return true;
}

bool Sprite::is_on_screen_strict(Position* pos)
{
    if (!(pos->x >= -15 && pos->x <= GAME_WIDTH - 1 && pos->y >= -15 && pos->y <= GAME_HEIGHT - 5))
        return false;
    else
        return true;
}

void Sprite::render(Position *pos, Direction dir, bool speedup)
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

    if (size == 1)
    { 
        flip = SDL_FLIP_NONE;
        offset = 0;
    }

    
    int offset_x = 0;
    int offset_y = 0;
    //if(game.player.moving) //the weird effect of the game in emulator, emulated
    //{
    //    if (game.player.moveIndex % 2 == 1)
    //    {
    //        switch (game.player.dir)
    //        {
    //        case Direction::UP:
    //        {
    //            offset_y -= 2;
    //            break;
    //        }
    //        case Direction::DOWN:
    //        {
    //            offset_y += 2;
    //            break;
    //        }
    //        case Direction::LEFT:
    //        {
    //            offset_x -= 2;
    //            break;
    //        }
    //        case Direction::RIGHT:
    //        {
    //            offset_x += 2;
    //            break;
    //        }
    //        }
    //    }
    //}

    SDL_Rect rectSrc = { 0,offset,16,16 };
    SDL_Rect rectDest = { pos->x-offset_x,pos->y-offset_y,16,16 };

    size_t brightness = BRIGHTNESS_NORMAL;

    if (game.player.warpIndex >= 24)
    {
        brightness = BRIGHTNESS_DARK3;
    }
    else if (game.player.warpIndex >= 16)
    {
        brightness = BRIGHTNESS_DARK3;
    }
    else if (game.player.warpIndex >= 8)
    {
        brightness = BRIGHTNESS_DARK1;
    }

    SDL_RenderCopyEx(sys.getRenderer(), texture[brightness], &rectSrc, &rectDest, 0.0f, NULL, flip);

}