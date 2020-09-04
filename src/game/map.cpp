#include "../sys/system.h"


void Block::render(int x, int y)
{
    x = x * 32;
    y = y * 32;
    SDL_Rect rected = { x + GAME_WIDTH / 2 - game.player.x - WORLD_OFFSET_X,y + GAME_HEIGHT / 2 - game.player.y - WORLD_OFFSET_Y,32,32 };
    SDL_RenderCopyEx(sys.getRenderer(), texture, NULL, &rected, 0.0f, NULL, SDL_FLIP_NONE);
}


void Map::render()
{
    //todo: render connected maps

    for (int Y = 0; Y < height; Y++)
    {
        for (int X = 0; X < width; X++)
        {
            blockset->blocks[this->blocks[Y*width + X]].render(X, Y);
        }
    }
}