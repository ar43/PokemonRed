#include "../sys/system.h"

void Textbox::render()
{
    if (input.keycatchers == KEYCATCHERS_TEXTBOX)
    {
        SDL_SetRenderDrawColor(sys.getRenderer(), 255, 255, 255, 255);
        SDL_Rect screen = { 0,GAME_HEIGHT - TEXTBOX_HEIGHT,TEXTBOX_WIDTH,TEXTBOX_HEIGHT };
        SDL_RenderFillRect(sys.getRenderer(), &screen);

        Texture* pnt = res.getTexture("tb1");
        pnt->render(0, GAME_HEIGHT - TEXTBOX_HEIGHT);
        pnt = res.getTexture("tb2");
        for (int i = 0; i < 18; i++)
            pnt->render(8 + i * 8, GAME_HEIGHT - TEXTBOX_HEIGHT);
        for (int i = 0; i < 18; i++)
            pnt->render(8 + i * 8, GAME_HEIGHT - 8);
        pnt = res.getTexture("tb3");
        pnt->render(152, GAME_HEIGHT - TEXTBOX_HEIGHT);
        pnt = res.getTexture("tb4");
        for (int i = 0; i < 6; i++)
            pnt->render(0, GAME_HEIGHT - TEXTBOX_HEIGHT + 8 + i * 8);
        for (int i = 0; i < 6; i++)
            pnt->render(GAME_WIDTH - 8, GAME_HEIGHT - TEXTBOX_HEIGHT + 8 + i * 8);
        pnt = res.getTexture("tb5");
        pnt->render(0, GAME_HEIGHT - 8);
        pnt = res.getTexture("tb6");
        pnt->render(GAME_WIDTH - 8, GAME_HEIGHT - 8);

        lineText[0].render(8, GAME_HEIGHT - TEXTBOX_HEIGHT+16);
        lineText[1].render(8, GAME_HEIGHT - TEXTBOX_HEIGHT + 32);
    }
}

void Textbox::update()
{
    if (refresh)
    {
        for(int i = 0; i < 2;i++)
        { 
            SDL_Surface* textSurface = TTF_RenderText_Solid(Constants::font, line[i], { 0,0,0,0xff });
            lineText[i].surface = textSurface;
            lineText[i].w = textSurface->w;
            lineText[i].h = textSurface->h;
            if (textSurface != NULL)
            {
                //Create texture from surface pixels
                lineText[i].texture = SDL_CreateTextureFromSurface(sys.getRenderer(), textSurface);
                if (lineText[i].texture == NULL)
                {
                    printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
                }

                //Get rid of old surface
                SDL_FreeSurface(textSurface);
            }
            else
            {
                printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
            }
        }
        refresh = false;
    }
}