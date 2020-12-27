#include "../sys/system.h"
#include <regex>

Textbox::Textbox()
{
    canInput = true;
    drawArrow = false;
    autoTextbox = false;
    delay = 2;
    autoClose = true;
    filteredText.clear();
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
    if (currText->type == TextType::TYPE_TEXT)
    {
        if (!cleared)
        {
            clear();
            //input.keyDown[KEY_A] = false;
        }
        if(index < filteredText.length() && game.frame.getFrame() % 3 == 0) //add a char
        { 
            update_text(0);
        }
        if (index >= filteredText.length()) //go next
        {
            transition();
            return;
        }
    }
    else if (currText->type == TextType::TYPE_LINE)
    {
        if (index < filteredText.length() && game.frame.getFrame() % 3 == 0)
        {
            update_text(1);
        }
        if (index >= filteredText.length())
        {
            transition();
            return;
        }
    }
    else if (currText->type == TextType::TYPE_CONT)
    {
        if (!activated)
        {
            drawArrow = true;
        }
        if (!activated && input.keyDown[KEY_A] && canInput || autoTextbox)
        {
            activated = true;
            scrollAnim = true;
            drawArrow = false;
            animIndex = 0;
        }
        if (activated && !scrollAnim)
        {
            if (index < filteredText.length() && game.frame.getFrame() % 3 == 0)
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
            if (index >= filteredText.length())
            {
                transition();
                return;
            }
        }
    }
    else if (currText->type == TextType::TYPE_PARA)
    {
        static int delay = 0;
        if (!activated)
        {
            drawArrow = true;
        }
        if (!activated && input.keyDown[KEY_A] && canInput || autoTextbox)
        {
            activated = true;
            drawArrow = false;
            delay = 21;
            clear();
        }
        if (activated && delay <= 0)
        {
            if (index < filteredText.length() && game.frame.getFrame() % 3 == 0)
            {
                update_text(0);
            }
            if (index >= filteredText.length())
            {
                transition();
                return;
            }
        }
        delay--;
    }
    else if (currText->type == TextType::TYPE_DONE || currText->type == TextType::TYPE_TEXT_END)
    {
        if (input.keyDown[KEY_A] && canInput || autoTextbox)
        {
            if (delay)
            {
                delay--;
                return;
            }
            game.canRunScript = true;
            if(autoClose)
            { 
                close();
            }
            return;
        }
    }
    else
    {
        sys.error(util::va("unimplemented type: %i\n",(int)currText->type));
    }
}

void Textbox::close()
{
    input.keycatchers = KEYCATCHERS_NORMAL;
    currText = nullptr;
    input.clear();
}

bool Textbox::show(std::string idString)
{

    idString = res.getTextRedefinition(idString);
    for (std::vector<Textset>::iterator it2 = game.world.currentMap->texts.begin(); it2 != game.world.currentMap->texts.end(); ++it2)
    {
        if (SDL_strcmp(idString.c_str(), it2->name.c_str()) == 0)
        {
            currText = it2->start;
            index = 0;
            cleared = false;
            input.keycatchers = KEYCATCHERS_TEXTBOX;
            filteredText = currText->text;
            game.canRunScript = false;
            return true;
        }
    }
    return false;
    
}

void Textbox::update_text(int num)
{
    if (index == 0)
    {
        filteredText = std::regex_replace(filteredText, std::regex("#"), "POKé");
        filteredText = std::regex_replace(filteredText, std::regex("<PLAYER>"), game.player.name);
        filteredText = std::regex_replace(filteredText, std::regex("<RIVAL>"), game.rivalName);
        filteredText = std::regex_replace(filteredText, std::regex("<PC>"), "PC");
        filteredText = std::regex_replace(filteredText, std::regex("<TM>"), "TM");
        filteredText = std::regex_replace(filteredText, std::regex("<TRAINER>"), "TRAINER");
        filteredText = std::regex_replace(filteredText, std::regex("<ROCKET>"), "ROCKET");
    }
    int times = 1;
    if (input.keyDown[KEY_A] && !autoTextbox) //text speedup
        times = 3;
    for(int i = 0; i < times;i++)
    { 

        size_t length = filteredText.length();
        if(index < length)
        { 
            if (filteredText.c_str()[index] == '@')
            {
                index = length;
                break;
            }
            SDL_snprintf(line[num], sizeof(line[num]), "%s%c", line[num], filteredText.c_str()[index]);
            index++;
        }
    }
    updateRenderer(num);
}

void Textbox::transition()
{
    currText = currText->next;
    filteredText = currText->text;
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