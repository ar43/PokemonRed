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
    SDL_Rect rected = { final_x,final_y,32,32 };
    SDL_RenderCopyEx(sys.getRenderer(), texture, NULL, &rected, 0.0f, NULL, SDL_FLIP_NONE);

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

void Block::render_static(int x, int y)
{
    if (!valid)
    {
        sys.error("Trying to render an invalid block");
    }

    x = x * 32;
    y = y * 32;
    SDL_Rect rected = { x ,y ,32,32 };
    SDL_RenderCopyEx(sys.getRenderer(), texture, NULL, &rected, 0.0f, NULL, SDL_FLIP_NONE);
}


void Map::render(int x, int y)
{
    for (int Y = 0; Y < height; Y++)
    {
        for (int X = 0; X < width; X++)
        {
            blockset->blocks[this->blocks[Y*width + X]].render(X + x, Y + y);
        }
    }
}