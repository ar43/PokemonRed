#include "../sys/system.h"


Textbox::Textbox()
{
    canInput = true;
}

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

        if(!scrollAnim)
        { 
            if(lineText[0].texture != nullptr)
                lineText[0].render(8, GAME_HEIGHT - TEXTBOX_HEIGHT+16);
            if(lineText[1].texture != nullptr)
                lineText[1].render(8+1, GAME_HEIGHT - TEXTBOX_HEIGHT + 31);
        }
        else
        {
            int y_offset = 0;
            if (animIndex > 1)
            {
                y_offset = 7;
            }

            if (lineText[0].texture != nullptr)
                lineText[0].render(8, GAME_HEIGHT - TEXTBOX_HEIGHT + 16-y_offset);
            if (lineText[1].texture != nullptr)
                lineText[1].render(8 + 1, GAME_HEIGHT - TEXTBOX_HEIGHT + 31- y_offset);
            animIndex++;
            if (animIndex == 8)
                scrollAnim = false;
        }
    }
}

void Textbox::update()
{
    if (currText == nullptr)
        return;
    /*
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
    */
    if (currText->type == TYPE_TEXT)
    {
        if (!cleared)
        {
            clear();
            //input.keyDown[KEY_A] = false;
        }
        if(index < strlen(currText->text) && game.frame.getFrame() % 3 == 0) //add a char
        { 
            if (index == 0)
            {
                //todo: call a function that replaces <PLAYER> etc with proper strings, reference: charmap.asm
            }
            SDL_snprintf(line[0], sizeof(line[0]), "%s%c", line[0], currText->text[index]);
            index++;
            updateRenderer(0);
        }
        if (index >= strlen(currText->text)) //go next
        {
            transition();
            return;
        }
    }
    else if (currText->type == TYPE_LINE)
    {
        if (index < strlen(currText->text) && game.frame.getFrame() % 3 == 0)
        {
            if (index == 0)
            {
                //todo: call a function that replaces <PLAYER> etc with proper strings, reference: charmap.asm
            }
            SDL_snprintf(line[1], sizeof(line[1]), "%s%c", line[1], currText->text[index]);
            index++;
            updateRenderer(1);
        }
        if (index >= strlen(currText->text))
        {
            transition();
            return;
        }
    }
    else if (currText->type == TYPE_CONT)
    {
        if (!activated && input.keyDown[KEY_A] && canInput)
        {
            activated = true;
            scrollAnim = true;
        }
        if (activated && !scrollAnim)
        {
            if (index < strlen(currText->text) && game.frame.getFrame() % 3 == 0)
            {
                if (index == 0)
                {
                    //todo: call a function that replaces <PLAYER> etc with proper strings, reference: charmap.asm
                    SDL_strlcpy(line[0], line[1], sizeof(line[0]));
                    updateRenderer(0);
                    lineText[1].texture = nullptr;
                    memset(line[1], 0, sizeof(line[1]));
                }
                SDL_snprintf(line[1], sizeof(line[1]), "%s%c", line[1], currText->text[index]);
                index++;
                updateRenderer(1);
            }
            if (index >= strlen(currText->text))
            {
                transition();
                return;
            }
        }
    }
    else if (currText->type == TYPE_DONE || currText->type == TYPE_TEXT_END)
    {
        if (input.keyDown[KEY_A] && canInput)
        {
            input.keycatchers = KEYCATCHERS_NORMAL;
            currText = nullptr;
            input.clear();
            return;
        }
    }
}

void Textbox::transition()
{
    currText = currText->next;
    index = 0;
    animIndex = 0;
    activated = false;
    if (input.keyDown[KEY_A] == false)
    {
        canInput = true;
    }
    else
    {
        canInput = false;
    }
}

void Textbox::updateRenderer(int num)
{
    if (num < 0 || num > 1)
        return;

    SDL_Surface* textSurface = TTF_RenderText_Solid(Constants::font, line[num], { 0,0,0,0xff });
    lineText[num].surface = textSurface;
    lineText[num].w = textSurface->w;
    lineText[num].h = textSurface->h;
    if (textSurface != NULL)
    {
        //Create texture from surface pixels
        lineText[num].texture = SDL_CreateTextureFromSurface(sys.getRenderer(), textSurface);
        if (lineText[num].texture == NULL)
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


void Textbox::clear()
{
    lineText[0].texture = nullptr;
    lineText[1].texture = nullptr;
    memset(line[0], 0, sizeof(line[0]));
    memset(line[1], 0, sizeof(line[1]));
    cleared = true;
}