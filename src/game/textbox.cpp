#include "../sys/system.h"


Textbox::Textbox()
{
    canInput = true;
    drawArrow = false;
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

        render_arrow();

        if(!scrollAnim)
        { 
            if(lineText[0].texture != nullptr)
                lineText[0].render(8, GAME_HEIGHT - TEXTBOX_HEIGHT+16);
            if(lineText[1].texture != nullptr)
                lineText[1].render(8+1, GAME_HEIGHT - TEXTBOX_HEIGHT + 31);
        }
        else
        {
            render_anim();
        }
    }
}

void Textbox::render_arrow()
{
    if (drawArrow)
    {
        if (animIndex % 72 < 36)
        {
            Texture* pnt = res.getTexture("tinput");
            pnt->render(GAME_WIDTH - 16, GAME_HEIGHT - 16);
        }
        animIndex++;
    }
}

void Textbox::render_anim()
{
    int y_offset = 0;
    if (animIndex > 1)
    {
        y_offset = 7;
    }

    if (lineText[0].texture != nullptr)
        lineText[0].render(8, GAME_HEIGHT - TEXTBOX_HEIGHT + 16 - y_offset);
    if (lineText[1].texture != nullptr)
        lineText[1].render(8 + 1, GAME_HEIGHT - TEXTBOX_HEIGHT + 31 - y_offset);
    animIndex++;
    if (animIndex == 8)
        scrollAnim = false;
}

void Textbox::update()
{
    if (currText == nullptr)
        return;
    if (currText->type == TYPE_TEXT)
    {
        if (!cleared)
        {
            clear();
            //input.keyDown[KEY_A] = false;
        }
        if(index < strlen(currText->text) && game.frame.getFrame() % 3 == 0) //add a char
        { 
            update_text(0);
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
            update_text(1);
        }
        if (index >= strlen(currText->text))
        {
            transition();
            return;
        }
    }
    else if (currText->type == TYPE_CONT)
    {
        if (!activated)
        {
            drawArrow = true;
        }
        if (!activated && input.keyDown[KEY_A] && canInput)
        {
            activated = true;
            scrollAnim = true;
            drawArrow = false;
            animIndex = 0;
        }
        if (activated && !scrollAnim)
        {
            if (index < strlen(currText->text) && game.frame.getFrame() % 3 == 0)
            {
                if (index == 0)
                {
                    SDL_strlcpy(line[0], line[1], sizeof(line[0]));
                    updateRenderer(0);
                    memset(line[1], 0, sizeof(line[1]));
                    SDL_DestroyTexture(lineText[1].texture);
                }
                update_text(1);
            }
            if (index >= strlen(currText->text))
            {
                transition();
                return;
            }
        }
    }
    else if (currText->type == TYPE_PARA)
    {
        static int delay = 0;
        if (!activated)
        {
            drawArrow = true;
        }
        if (!activated && input.keyDown[KEY_A] && canInput)
        {
            activated = true;
            drawArrow = false;
            delay = 21;
            clear();
        }
        if (activated && delay <= 0)
        {
            if (index < strlen(currText->text) && game.frame.getFrame() % 3 == 0)
            {
                update_text(0);
            }
            if (index >= strlen(currText->text))
            {
                transition();
                return;
            }
        }
        delay--;
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
    else
    {
        sys.error(util::va("unimplemented type: %i\n",(int)currText->type));
    }
}

bool Textbox::show(std::string idString)
{

    for (std::vector<Textset>::iterator it2 = game.world.currentMap->texts.begin(); it2 != game.world.currentMap->texts.end(); ++it2)
    {
        if (SDL_strcmp(idString.c_str(), it2->name.c_str()) == 0)
        {
            game.textbox.currText = it2->start;
            game.textbox.index = 0;
            game.textbox.cleared = false;
            input.keycatchers = KEYCATCHERS_TEXTBOX;
            return true;
        }
    }
    return false;
    
}

void Textbox::update_text(int num)
{
    if (index == 0)
    {
        //todo: call a function that replaces <PLAYER> etc with proper strings, reference: charmap.asm
        //actually maybe call it somewhere else... put it in filteredText or sth.
        //maybe at start of update? check if filtered text is null, then put text to filtered text, and
        //clear filtered text at each transition
    }
    int times = 1;
    if (input.keyDown[KEY_A]) //text speedup
        times = 3;
    for(int i = 0; i < times;i++)
    { 
        if(index < strlen(currText->text))
        { 
            SDL_snprintf(line[num], sizeof(line[num]), "%s%c", line[num], currText->text[index]);
            index++;
        }
    }
    updateRenderer(num);
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
        if (lineText[num].texture != nullptr) 
        {
            SDL_DestroyTexture(lineText[num].texture); //prevent memory leak
        }
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
    lineText[1].texture = nullptr; //potential memory leaks here, should prolly be SDL_DestroyTexture
    //if (lineText[0].texture != nullptr)
        //SDL_DestroyTexture(lineText[0].texture);
    //if (lineText[1].texture != nullptr)
        //SDL_DestroyTexture(lineText[1].texture);
    memset(line[0], 0, sizeof(line[0]));
    memset(line[1], 0, sizeof(line[1]));
    cleared = true;
}