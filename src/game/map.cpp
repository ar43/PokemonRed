#include "../sys/system.h"


void Block::render(int x, int y)
{
    if (!valid)
    {
        sys.error("Trying to render an invalid block");
    }

    x = x * 32;
    y = y * 32;
    int final_x = x + GAME_WIDTH / 2 - game.player.getPosition()->x - WORLD_OFFSET_X;
    int final_y = y + GAME_HEIGHT / 2 - game.player.getPosition()->y - WORLD_OFFSET_Y;
    size_t brightness = BRIGHTNESS_NORMAL;
    static bool ascend = true;

    //check if we can see the block (save our CPU)
    if (!(final_x > -64 && final_x < GAME_WIDTH + 64 && final_y > -64 && final_y < GAME_HEIGHT + 64))
        return;

    if (game.player.warpIndex >= 24)
    {
        brightness = BRIGHTNESS_DARK3;
    }
    else if (game.player.warpIndex >= 16)
    {
        brightness = BRIGHTNESS_DARK2;
    }
    else if (game.player.warpIndex >= 8)
    {
        brightness = BRIGHTNESS_DARK1;
    }
    else if (game.battle.starting)
    {
        brightness = game.battle.brightness;
    }

    SDL_Rect rected = { final_x,final_y,32,32 };
    SDL_RenderCopyEx(sys.getRenderer(), texture[brightness], NULL, &rected, 0.0f, NULL, SDL_FLIP_NONE);

    //handle animation & grass
    for (int i = 0; i < 16; i++)
    {
        if (animation[i] == ANIMATION_FLOWER)
        {

            Texture* flower;
            if (game.frame.getFrame() % 84 < 42)
            {
                flower = res.getTexture("flower1");
            }
            else if (game.frame.getFrame() % 84 < 63)
            {
                flower = res.getTexture("flower2");
            }
            else
            {
                flower = res.getTexture("flower3");
            }
            flower->render(final_x + i % 4 * 8, final_y + i / 4 * 8);
        }
        else if (animation[i] == ANIMATION_WATER)
        {
            Texture* water;
            if (game.frame.getFrame() % 168 < 21)
            {
                water = res.getTexture("water0");
            }
            else if (game.frame.getFrame() % 168 < 42)
            {
                water = res.getTexture("water1");
            }
            else if (game.frame.getFrame() % 168 < 63)
            {
                water = res.getTexture("water2");
            }
            else if (game.frame.getFrame() % 168 < 84)
            {
                water = res.getTexture("water3");
            }
            else if (game.frame.getFrame() % 168 < 105)
            {
                water = res.getTexture("water4");
            }
            else if (game.frame.getFrame() % 168 < 126)
            {
                water = res.getTexture("water3");
            }
            else if (game.frame.getFrame() % 168 < 147)
            {
                water = res.getTexture("water2");
            }
            else
            {
                water = res.getTexture("water1");
            }
            water->render(final_x + i % 4 * 8, final_y + i / 4 * 8);
        }
        if (grassTile[i])
        {
            Position effect = { final_x + i % 4 * 8,final_y + i / 4 * 8 };
            game.world.currentMap->grassEffect.push_back(effect);
        }
    }

    if(game.debug.drawColl)
    { 
        SDL_Rect rect0 = { final_x,final_y,8,8 };
        SDL_Rect rect1 = { final_x+8,final_y,8,8 };
        SDL_Rect rect2 = { final_x+16,final_y,8,8 };
        SDL_Rect rect3 = { final_x+24,final_y,8,8 };
        SDL_Rect rect4 = { final_x+0,final_y+8,8,8 };
        SDL_Rect rect5 = { final_x+8,final_y+8,8,8 };
        SDL_Rect rect6 = { final_x+16,final_y+8,8,8 };
        SDL_Rect rect7 = { final_x+24,final_y+8,8,8 };
        SDL_Rect rect8 = { final_x+0,final_y+16,8,8 };
        SDL_Rect rect9 = { final_x+8,final_y+16,8,8 };
        SDL_Rect rectA = { final_x+16,final_y+16,8,8 };
        SDL_Rect rectB = { final_x+24,final_y+16,8,8 };
        SDL_Rect rectC = { final_x+0,final_y+24,8,8 };
        SDL_Rect rectD = { final_x+8,final_y+24,8,8 };
        SDL_Rect rectE = { final_x+16,final_y+24,8,8 };
        SDL_Rect rectF = { final_x+24,final_y+24,8,8 };

        if (solid[0][0])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rect0);
        }
        if (solid[0][1])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rect1);
        }
        if (solid[0][2])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rect4);
        }
        if (solid[0][3])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rect5);
        }

        if (solid[1][0])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rect2);
        }
        if (solid[1][1])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rect3);
        }
        if (solid[1][2])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rect6);
        }
        if (solid[1][3])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rect7);
        }

        if (solid[2][0])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rect8);
        }
        if (solid[2][1])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rect9);
        }
        if (solid[2][2])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rectC);
        }
        if (solid[2][3])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rectD);
        }

        if (solid[3][0])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rectA);
        }
        if (solid[3][1])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rectB);
        }
        if (solid[3][2])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rectE);
        }
        if (solid[3][3])
        {
            SDL_SetRenderDrawColor(sys.getRenderer(), 0, 0, 255, 255);
            SDL_RenderFillRect(sys.getRenderer(), &rectF);
        }
    }

}

void Map::runScript()
{
    if (!game.canRunScript)
        return;
    char filename[128] = { 0 };
    SDL_snprintf(filename, sizeof(filename), "assets/scripts/maps/%s/main.lua", fileName.c_str());
    if (!util::file_exists(filename))
        return;

    if(lua::L == nullptr)
    { 
        lua::L = luaL_newstate();
        luaL_openlibs(lua::L);
        luabridge::getGlobalNamespace(lua::L)
            .beginNamespace("pkm")
                .beginClass <Position>("pos")
                    .addProperty("x", &Position::x)
                    .addProperty("y", &Position::y)
                .endClass()
                .addFunction("set_active", lua::set_active)
                .addFunction("get_player_pos", lua::get_player_pos)
                .addFunction("set_object_dir", lua::set_object_dir)
                .addFunction("set_event", lua::set_event)
                .addFunction("check_event", lua::check_event)
                .addFunction("display_text", lua::display_text)
                .addFunction("close_text", lua::close_text)
                .addFunction("text_auto_scroll", lua::text_auto_scroll)
                .addFunction("get_script",lua::get_current_script)
                .addFunction("set_script", lua::set_current_script)
                .addFunction("set_emote", lua::set_emote)
                .addFunction("get_emote_time", lua::get_emote_time)
                .addFunction("set_freeze", lua::set_freeze)
                .addFunction("add_movement", lua::add_movement)
                .addFunction("is_mq_empty", lua::is_mq_empty)
                .addFunction("get_keycatchers",lua::get_keycatchers)
                .addFunction("speedup",lua::speedup)
                .addFunction("give_pokemon", lua::give_pokemon)
            .endNamespace();
        luaL_dostring(lua::L, "time = 0\n");
        luaL_dostring(lua::L, "delay = 0\n");
    }

    
    
    int ret = luaL_dofile(lua::L, filename);
    lua::print_error(ret);
       
}

void Block::render_static(int x, int y)
{
    if (!valid)
    {
        sys.error("Trying to render an invalid block");
    }

    x = x * 32;
    y = y * 32;
    SDL_Rect rected = { x ,y ,32,32 };
    SDL_RenderCopyEx(sys.getRenderer(), texture[BRIGHTNESS_NORMAL], NULL, &rected, 0.0f, NULL, SDL_FLIP_NONE);
}


Blockset* Map::blockset()
{
    if (p_blockset == nullptr)
        loadBlockset();
    return p_blockset;
}

void Map::render(int x, int y)
{
    for (int Y = 0; Y < height; Y++)
    {
        for (int X = 0; X < width; X++)
        {
            blockset()->blocks[this->blocks[Y*width + X]].render(X + x, Y + y);
        }
    }
}

void Map::loadBlockset()
{
    this->p_blockset = res.getBlockset(this->blocksetName);
}

void Texture::render_scale(int x, int y, int new_w, int new_h, SDL_RendererFlip flip)
{
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

    SDL_Rect rectedDest = { x,y,new_w,new_h };
    SDL_Rect rectedSrc = { 0,0,w,h };
    SDL_RenderCopyEx(sys.getRenderer(), texture, &rectedSrc, &rectedDest, 0.0f, NULL, flip);
}

void Texture::scale(int new_w, int new_h) //will lose transparency!
{
    //maybe do
    // SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
    //SDL_DestroyTexture(texture);
    SDL_Texture *new_texture =  SDL_CreateTexture(sys.getRenderer(), format, SDL_TEXTUREACCESS_TARGET, new_w, new_h);
    
    if(new_texture == NULL)
        printf("SDL_CreateTexture failed: %s\n", SDL_GetError());

    SDL_SetRenderTarget(sys.getRenderer(), new_texture);

    SDL_SetRenderDrawColor( sys.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( sys.getRenderer() );

    SDL_Rect rectedSrc = { 0,0,w,h };
    SDL_Rect rected = { 0,0,new_w,new_h };
    
    SDL_RenderCopy(sys.getRenderer(), texture, &rectedSrc, &rected);

    SDL_SetRenderTarget(sys.getRenderer(), NULL);
    SDL_DestroyTexture(texture);
    texture = new_texture;
    w = new_w;
    h = new_h;
}

void Texture::generate_tilemaps()
{
    if (w != 64 && h != 64)
        return;

    tilemap_3x3 =  SDL_CreateTexture(sys.getRenderer(), format, SDL_TEXTUREACCESS_TARGET, 3*8, 3*8);
    if(tilemap_3x3 == NULL)
        printf("SDL_CreateTexture failed: %s\n", SDL_GetError());

    SDL_SetRenderTarget(sys.getRenderer(), tilemap_3x3);

    SDL_SetRenderDrawColor( sys.getRenderer(), 0xff, 0xff, 0xff, 0xFF );
    SDL_RenderClear( sys.getRenderer() );

    const int table_3x3[9] = { 305,326,347,
        308,329,350,
        311,332,353 };

    for (int i = 0; i < 9; i++)
    {
        int num = table_3x3[i] - 305;
        int src_x = num / 7;
        int src_y = num % 7;
        int dst_x = i % 3;
        int dst_y = i / 3;
        SDL_Rect rectedSrc = { src_x*8,src_y*8,8,8 };
        SDL_Rect rectedDst = { dst_x*8,dst_y*8,8,8 };
        SDL_RenderCopy(sys.getRenderer(), texture, &rectedSrc, &rectedDst);
    }

    tilemap_5x5 =  SDL_CreateTexture(sys.getRenderer(), format, SDL_TEXTUREACCESS_TARGET, 5*8, 5*8);
    if(tilemap_5x5 == NULL)
        printf("SDL_CreateTexture failed: %s\n", SDL_GetError());

    SDL_SetRenderTarget(sys.getRenderer(), tilemap_5x5);

    SDL_SetRenderDrawColor( sys.getRenderer(), 0xff, 0xff, 0xff, 0xFF );
    SDL_RenderClear( sys.getRenderer() );

    const int table_5x5[25] = { 305,312,326,340,347,
        306,313,327,341,348,
        308,315,329,343,350,
        310,317,331,345,352,
        311,318,332,346,353 };

    for (int i = 0; i < 25; i++)
    {
        int num = table_5x5[i] - 305;
        int src_x = num / 7;
        int src_y = num % 7;
        int dst_x = i % 5;
        int dst_y = i / 5;
        SDL_Rect rectedSrc = { src_x*8,src_y*8,8,8 };
        SDL_Rect rectedDst = { dst_x*8,dst_y*8,8,8 };
        SDL_RenderCopy(sys.getRenderer(), texture, &rectedSrc, &rectedDst);
    }


    SDL_SetRenderTarget(sys.getRenderer(), NULL);
}

void Texture::render(int x, int y, SDL_RendererFlip flip)
{
    if (texture == nullptr)
        return;
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

    SDL_Rect rected = { x,y,w,h };
    SDL_RenderCopyEx(sys.getRenderer(), texture, NULL, &rected, 0.0f, NULL, flip);
}

void Texture::render_tilemap(int x, int y, bool t3)
{
    if (tilemap_3x3 == nullptr || tilemap_5x5 == nullptr)
        sys.error("trying to draw tilemap with no tilemap for the texture");

    int temp_w, temp_h;
    if (t3)
    {
        temp_w = 3*8;
        temp_h = 3*8;
    }
    else
    {
        temp_w = 5*8;
        temp_h = 5*8;
    }
    SDL_Rect rected = { x,y,temp_w,temp_h };
    SDL_Rect rectedSrc = { 0,0,temp_w,temp_h };
    if(t3)
        SDL_RenderCopy(sys.getRenderer(), tilemap_3x3, &rectedSrc, &rected);
    else
        SDL_RenderCopy(sys.getRenderer(), tilemap_5x5, &rectedSrc, &rected);
}

void Texture::render_ex(int x, int y, int x2, int y2, int w, int h, SDL_RendererFlip flip)
{
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

    SDL_Rect rected = { x,y,w,h };
    SDL_Rect rectedSrc = { x2,y2,w,h };
    SDL_RenderCopyEx(sys.getRenderer(), texture, &rectedSrc, &rected, 0.0f, NULL, flip);
}

void Texture::render_special(int x, int y, int num, SDL_RendererFlip flip)
{
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

    int offset = num;

    int y2 = offset / 16;
    y2 = y2 * 8;
    int x2 = (offset % 16)*8;

    SDL_Rect rected = { x,y,8,8 };
    SDL_Rect rectedSrc = { x2,y2,8,8 };
    SDL_RenderCopyEx(sys.getRenderer(), texture, &rectedSrc, &rected, 0.0f, NULL, flip);
}

void Texture::render_grass(int x, int y, bool upper)
{
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

    int a, b, c, d, e, f, g, h;
    if (!upper)
    {
        a = 0;
        b = 0;
        c = w;
        d = 4;
        e = x;
        f = y;
        g = w;
        h = 4;
    }
    else
    {
        a = 0;
        b = 4;
        c = 8;
        d = 4;
        e = x;
        f = y + 4;
        g = 8;
        h = 4;
    }

    SDL_Rect rect1 = { a,b,c,d };
    SDL_Rect rect2 = { e,f,g,h };

    SDL_RenderCopyEx(sys.getRenderer(), texture, &rect1, &rect2, 0.0f, NULL, SDL_FLIP_NONE);
}