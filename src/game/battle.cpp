#include "../sys/system.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>



Battle::Battle()
{
    ash_position.x = GAME_WIDTH - 8;
    ash_position.y = 40;
}

void Battle::begin_trainer(std::string trainerName, Party* opp_party)
{
    start();
    this->trainerName = trainerName;
    this->opp_party = opp_party;
    trainerBattle = true;
    on_begin();
}

void Battle::begin_wild(std::string pokemonName, int level)
{
    start();
    trainerBattle = false;
    Party* party = new Party();
    party->addPokemon(new Pokemon(res.getPokemonData(pokemonName), level));
    this->opp_party = party;
    enemyMonNick = pokemonName;
    on_begin();
}

void Battle::start()
{
    game.textbox.autoTextbox = true; //TODO: restore this on battle end
    game.textbox.autoClose = true; //TODO: restore this on battle end

    player_party = game.player.inv.getParty(); //switch this if you want to create a custom party

	starting = true;
    inBattle = false;
	battleIndex = 0;
    brightness = 3;
    game.textbox.clear();
    scriptIndex = 0;
	input.keycatchers = KEYCATCHERS_TEXTBOX;
    drawFrameBottom = true;
    drawPlayerPokeballs = true;
    drawEnemyInfo = false;
    drawPlayerInfo = false;
    drawSubmenu = BattleSubmenu::NONE;
    drawPlayerMon = 0;
    currEnemyMonIndex = 0;
    
    cursorGeneralPosition.x = 0;
    cursorGeneralPosition.y = 0;
    cursorFightPosition = 0;

}

void Battle::on_begin()
{
    if (player_party->firstMonId() < 0 || opp_party->firstMonId() < 0)
        sys.error("Trying to create a battle with an empty or dead party on either side");

    battleMonNick = player_party->firstMonNick();
    currPlayerMonIndex = player_party->firstMonId();

    create_fight_text();

}

static int cantor(int a, int b)
{
    return ((a + b) * (a + b + 1)) / 2 + b;
}

void Battle::update()
{
    static int counter = 0;
	if (!inBattle)
	{
		if (starting)
		{
            counter = 0;
			battleIndex++;
            if (battleIndex <= 76)
                first_animation();
            else if (battleIndex <= 105) //29 frames for second
                second_animation();
		}
		if (battleIndex == 176)
		{
			starting = false;
			battleIndex = 0;
            scrollIndex = 0;
            enemyScrollIndex = 0;
			inBattle = true;
			on_begin();
		}
	}
	else
	{
        battleIndex++;
        if (scrollIndex < 72)
        {
            scrollIndex++;
            enemyScrollIndex++;
        }
            

        if (battleIndex == 103)
        {
            delayScript = 10;
            if(!trainerBattle)
                game.textbox.show("WildMonAppearedText");
        }
        else if (battleIndex > 103 && game.canRunScript)
        {
            if (delayScript == 0)
            {
                switch (scriptIndex)
                {
                    case 0:
                    {
                        drawPlayerPokeballs = false;

                        create_enemy_pokemon_text_texture();
                        update_enemy_hp();

                        create_player_pokemon_text_texture();
                        update_player_hp();

                        drawEnemyInfo = true;
                        scriptIndex = 1;
                        break;
                    }
                    case 1:
                    {
                        drawFrameBottom = false;
                        game.textbox.clear();
                        scriptIndex = 2;
                        delayScript = 38;
                        break;
                    }
                    case 2: //scroll player out
                    {
                        if (battleIndex % 3 == 0)
                        {
                            if(counter % 2 == 1)
                                scrollIndex += 8;
                            else
                                scrollIndex += 4;
                            counter++;
                        }
                        if (counter == 6)
                        {
                            scriptIndex = 3;
                            delayScript = 5;
                            counter = 0;
                        }
                        break;
                    }
                    case 3: //show Go text
                    {
                        int hp = enemyHp;
                        int max_hp = opp_party->pokemonList.at(currEnemyMonIndex)->maxHp();
                        double percantage = (double)enemyHp / (double)max_hp;
                        if (percantage >= 0.7)
                            game.textbox.show("GoText");
                        else if (percantage >= 0.4)
                            game.textbox.show("DoItText");
                        else if (percantage >= 0.1)
                            game.textbox.show("GetmText");
                        else
                            game.textbox.show("EnemysWeakText");

                        
                        
                        scriptIndex = 4;
                        break;
                    }
                    case 4: //show GO Text part 2
                    {
                        game.textbox.show("PlayerMon1Text",false);
                        scriptIndex = 5;
                        delayScript = 2;
                        break;
                    }
                    case 5: //draw player frame
                    {
                        drawFrameBottom = true;
                        drawPlayerInfo = true;
                        scriptIndex = 6;
                        delayScript = 40;
                        break;
                    }
                    case 6: //play player pokemon appear animation
                    {
                        if (counter == 0)
                        {
                            counter++;
                            pokemonAppear.play = true;
                            pokemonAppear.counter = &counter;
                            pokemonAppear.x_offset = 0;
                            pokemonAppear.y_offset = 0;
                        }
                        else
                        {
                            counter++;
                            if (pokemonAppear.play == false)
                            {
                                pokemonAppear.reset();
                                delayScript = 4;
                                scriptIndex = 7;
                                counter = 0;
                            }
                        }
                        break;
                    }
                    case 7:
                    {
                        //reveal 3x3, wait 3, reveal 5x5, wait 6, reveal full
                        if (drawPlayerMon == 0)
                        {
                            delayScript = 3;
                            drawPlayerMon = 1;
                        }
                        else if (drawPlayerMon == 1)
                        {
                            delayScript = 6;
                            drawPlayerMon = 2;
                        }
                        else if (drawPlayerMon == 2)
                        {
                            drawPlayerMon = 3;
                            scriptIndex = 8;
                            delayScript = 52;
                        }
                        
                        break;
                    }
                    case 8:
                    {
                        game.textbox.clear();
                        delayScript = 7;
                        scriptIndex = (int)NamedBattleScripts::GENERAL_SUBMENU;
                        break;
                    }
                    case (int)NamedBattleScripts::GENERAL_SUBMENU: //Battle submenu shows here
                    {
                        drawSubmenu = BattleSubmenu::GENERAL;

                        if (input.keyDown[KEY_A])
                        {
                            const int offset = cantor(cursorGeneralPosition.x, cursorGeneralPosition.y);
                            input.clear();
                            scriptIndex = (int)NamedBattleScripts::FIGHT_SUBMENU + offset;
                            update_fight_move_description();
                            game.battle.canInput = true;

                        }
                        else if (input.keyDown[ARROW_LEFT])
                        {
                            input.clear();
                            if(cursorGeneralPosition.x > 0)
                                cursorGeneralPosition.x -= 1;
                        }
                        else if (input.keyDown[ARROW_RIGHT])
                        {
                            input.clear();
                            if(cursorGeneralPosition.x == 0)
                                cursorGeneralPosition.x += 1;
                        }
                        else if (input.keyDown[ARROW_DOWN])
                        {
                            input.clear();
                            if(cursorGeneralPosition.y == 0)
                                cursorGeneralPosition.y += 1;
                        }
                        else if (input.keyDown[ARROW_UP])
                        {
                            input.clear();
                            if(cursorGeneralPosition.y == 1)
                                cursorGeneralPosition.y -= 1;
                        }

                        break;
                    }
                    case (int)NamedBattleScripts::FIGHT_SUBMENU: //Battle submenu shows here
                    {
                        drawSubmenu = BattleSubmenu::FIGHT;

                        if (game.battle.canInput)
                        {
                            if (input.keyDown[KEY_A])
                            {
                                input.clear();
                                update_fight_move_description();
                            }
                            else if (input.keyDown[KEY_B])
                            {
                                input.clear();
                                scriptIndex = (int)NamedBattleScripts::GENERAL_SUBMENU;
                            }
                            else if (input.keyDown[ARROW_DOWN])
                            {
                                input.clear();
                                cursorFightPosition++;
                                cursorFightPosition = cursorFightPosition % num_moves;
                                update_fight_move_description();
                            }
                            else if (input.keyDown[ARROW_UP])
                            {
                                input.clear();
                                cursorFightPosition--;
                                if (cursorFightPosition < 0)
                                    cursorFightPosition = num_moves-1;
                                update_fight_move_description();
                            }
                        }

                        

                        break;
                    }
                    default:
                    {
                        sys.error(util::va("Undefined battle script: %i", scriptIndex));
                        break;
                    }
                }
            }
            if (delayScript > 0)
                delayScript--;
        }
		//todo
	}
	
}

void Battle::render()
{
	if (!inBattle)
		return;

    if (!trainerBattle) //draw wild pokemon scrollin in
    {
        opp_party->pokemonList.at(0)->data->front->render(enemyScrollIndex * 2-40, 16);
    }

    res.getTexture("redb")->render(ash_position.x-scrollIndex*2, ash_position.y); //draw RED scrolling in
    
    if (battleIndex >= 100)
    {
        render_player_pokeballs();
    }
    if (battleIndex >= 102)
    {
        render_frame_bottom();
    }
    if (drawEnemyInfo)
    {
        render_enemy_info();
    }
    if (drawPlayerInfo)
    {
        render_player_info();
    }

    if (drawSubmenu == BattleSubmenu::GENERAL)
    {
        render_general_submenu();
    }
    else if (drawSubmenu == BattleSubmenu::FIGHT)
    {
        render_fight_submenu();
    }


    if (pokemonAppear.play)
    {
        playanim_pokemonappear();
    }
    
}

void Battle::pre_render()
{
    if (!inBattle)
        return;
    SDL_SetRenderDrawColor(sys.getRenderer(), 255, 255, 255, 255);
    SDL_Rect screen = { 0,0,GAME_WIDTH,GAME_HEIGHT };
    SDL_RenderFillRect(sys.getRenderer(), &screen);

    if (drawPlayerMon)
    {
        render_player_pokemon();
    }
}

void Battle::first_animation()
{
    static bool ascend = true;
    if (starting && battleIndex > 5)
    {
        if (battleIndex < 70 || brightness != BRIGHTNESS_NORMAL)
        {
            if (battleIndex == 6)
            {
                brightness = BRIGHTNESS_DARK1;
                ascend = true;
            }
            else if (battleIndex % 2 == 0)
            {
                if (ascend)
                {
                    brightness++;
                }
                else
                {
                    brightness--;
                }

                if (brightness < 0)
                {
                    brightness = 1;
                    ascend = true;
                }
                else if (brightness >= NUM_BRIGHTNESS)
                {
                    brightness = BRIGHTNESS_DARK2;
                    ascend = false;
                }
                //printf("i: %i b:%i\n", battleIndex, brightness);
            }
        }
    }
}

void Battle::second_animation()
{
    //todo
}

void Battle::render_player_pokeballs()
{
    if (!drawPlayerPokeballs)
        return;
    auto tex = res.getTexture("balls");
    int x_offset = 88;
    int status[6] = { 0 };
    player_party->statusReport(status);
    tex->render_ex(x_offset, 80, status[0], 0, 8, 8);
    tex->render_ex(x_offset+8, 80, status[1], 0, 8, 8);
    tex->render_ex(x_offset+16, 80, status[2], 0, 8, 8);
    tex->render_ex(x_offset+24, 80, status[3], 0, 8, 8);
    tex->render_ex(x_offset+32, 80, status[4], 0, 8, 8);
    tex->render_ex(x_offset+40, 80, status[5], 0, 8, 8);
}

void Battle::render_frame_bottom()
{
    if (!drawFrameBottom)
        return;
    auto tex1 = res.getTexture("battle_hud_1");
    auto tex2 = res.getTexture("battle_hud_2");
    auto tex3 = res.getTexture("battle_hud_3");
    int x_offset = 88;
    int y_offset = 88;

    tex1->render_ex(x_offset-8*2, y_offset, 16, 0, 8, 8);
    tex3->render_ex(x_offset-8, y_offset, 0, 0, 8, 8);
    tex3->render_ex(x_offset, y_offset, 0, 0, 8, 8);
    tex3->render_ex(x_offset+8, y_offset, 0, 0, 8, 8);
    tex3->render_ex(x_offset+8*2, y_offset, 0, 0, 8, 8);
    tex3->render_ex(x_offset+8*3, y_offset, 0, 0, 8, 8);
    tex3->render_ex(x_offset+8*4, y_offset, 0, 0, 8, 8);
    tex3->render_ex(x_offset+8*5, y_offset, 0, 0, 8, 8);
    tex3->render_ex(x_offset+8*6, y_offset, 0, 0, 8, 8);
    tex3->render_ex(x_offset+8*7, y_offset, 8, 0, 8, 8);
    tex2->render_ex(x_offset+8*7, y_offset-8, 0, 0, 8, 8);

}

void Battle::render_enemy_info()
{
    auto tex1 = res.getTexture("battle_hud_1");
    auto tex2 = res.getTexture("battle_hud_2");
    auto tex3 = res.getTexture("battle_hud_3");
    auto tex4 = res.getTexture("font_battle_extra");

    enemyPokemonText.render(8, 0); //name
    enemyPokemonLvl.render(32+8, 8); //level

    tex1->render_ex(32, 8, 8, 0, 8, 8); //:L

    //border
    tex2->render_ex(8, 16, 0, 0, 8, 8);
    tex2->render_ex(8, 16+8, 8, 0, 8, 8);
    tex3->render_ex(8+8, 16+8, 0, 0, 8, 8);
    tex3->render_ex(8+8*2, 16+8, 0, 0, 8, 8);
    tex3->render_ex(8+8*3, 16+8, 0, 0, 8, 8);
    tex3->render_ex(8+8*4, 16+8, 0, 0, 8, 8);
    tex3->render_ex(8+8*5, 16+8, 0, 0, 8, 8);
    tex3->render_ex(8+8*6, 16+8, 0, 0, 8, 8);
    tex3->render_ex(8+8*7, 16+8, 0, 0, 8, 8);
    tex3->render_ex(8+8*8, 16+8, 0, 0, 8, 8);
    tex3->render_ex(8+8*9, 16+8, 16, 0, 8, 8);

    //HP
    tex4->render_ex(16, 16, 0, 8, 8, 8);
    tex4->render_ex(16+8, 16, 0, 0, 8, 8);
    tex4->render_ex(10*8, 16, 8*10, 0, 8, 8);
    render_hp(enemyHp,opp_party->pokemonList.at(currEnemyMonIndex)->maxHp(),4*8,16);
}

static int get_health_texture(int pixels)
{
    return (pixels + 1) * 8;
}

void Battle::render_hp(int hp, int max_hp, int x_start, int y)
{
    auto tex = res.getTexture("font_battle_extra");

    int max_pixels = 48;
    int pixels_to_show = 0;

    if (hp == 0)
    {
        pixels_to_show = 0;
    }
    else if (hp == max_hp)
    {
        pixels_to_show = 48;
    }
    else
    {
        double percantage = (double)hp / (double)max_hp;
        pixels_to_show = (int)floor(percantage * 48);
        if (pixels_to_show == 0)
            pixels_to_show = 1;

        if (pixels_to_show < 0 || pixels_to_show >= 48)
            sys.error("Bad pixels_to_show in Battle::render_enemy_hp()");
        
    }

    int number_of_full_bars = pixels_to_show / 8;
    int i = 0;

    for (i = 0; i < number_of_full_bars; i++)
    {
        tex->render_ex(x_start + 8 * i, y, get_health_texture(8), 0, 8, 8);
    }

    if (number_of_full_bars < 6)
    {
        if (pixels_to_show % 8 != 0)
        {
            tex->render_ex(x_start + 8 * i, y, get_health_texture(pixels_to_show % 8), 0, 8, 8);
            i++;
        }
        for (i; i < 6; i++)
        {
            tex->render_ex(x_start + 8 * i, y, get_health_texture(0), 0, 8, 8);
        }
    }

}

void Battle::render_player_info()
{
    auto tex1 = res.getTexture("battle_hud_1");
    auto tex2 = res.getTexture("battle_hud_2");
    auto tex3 = res.getTexture("battle_hud_3");
    auto tex4 = res.getTexture("font_battle_extra");

    playerPokemonText.render(10*8, 7*8); //name
    playerPokemonLvl.render(15*8, 8*8); //level

    tex1->render_ex(14*8, 8*8, 8, 0, 8, 8); //:L

    //border
    tex1->render_ex(18*8, 9*8, 0, 0, 8, 8);

    //HP
    tex4->render_ex(10*8, 9*8, 0, 8, 8, 8);
    tex4->render_ex(11*8, 9*8, 0, 0, 8, 8);
    render_hp(playerHp,player_party->pokemonList.at(currPlayerMonIndex)->maxHp(),12*8,9*8);
    playerPokemonHp.render(11 * 8+1, 10 * 8);
}

void Battle::render_player_pokemon()
{
    if(drawPlayerMon == 3)
        player_party->pokemonList.at(currPlayerMonIndex)->data->back->render(1 * 8, 5 * 8);
    else if(drawPlayerMon == 2)
        player_party->pokemonList.at(currPlayerMonIndex)->data->back->render_tilemap(2 * 8, 7 * 8,false);
    else if(drawPlayerMon == 1)
        player_party->pokemonList.at(currPlayerMonIndex)->data->back->render_tilemap(3 * 8, 9 * 8,true);
}

void Battle::render_general_submenu()
{
    auto tex1 = res.getTexture("tb1");
    auto tex5 = res.getTexture("tb5");
    auto tex4 = res.getTexture("tb4");

    tex1->render(8 * 8, 12 * 8);
    
    for (int i = 0; i < 6; i++)
        tex4->render(8*8, GAME_HEIGHT - TEXTBOX_HEIGHT + 8 + i * 8);

    tex5->render(8 * 8, 17 * 8);

    res.getTexture("pkmn")->render(16 * 8, 14 * 8);
    res.getTexture("battle_fight")->render(10 * 8, 14 * 8);
    res.getTexture("battle_item")->render(10 * 8 + 1, 16 * 8);
    res.getTexture("battle_run")->render(16 * 8, 16 * 8);

    const int cursor_x = 9*8 + (6 * cursorGeneralPosition.x)*8;
    const int cursor_y = 14*8 + (2 * cursorGeneralPosition.y)*8;
    res.getTexture("cursor_full")->render(cursor_x, cursor_y);
}

void Battle::render_fight_submenu()
{
    auto tex1 = res.getTexture("tb1");
    auto tex2 = res.getTexture("tb2");
    auto tex5 = res.getTexture("tb5");
    auto tex4 = res.getTexture("tb4");
    auto tex3 = res.getTexture("tb3");
    auto tex6 = res.getTexture("tb6");

    SDL_SetRenderDrawColor( sys.getRenderer(), 255, 255, 255, 255 );
    SDL_Rect white = { 8,8 * 9,8 * 9,3 * 8 };
    SDL_RenderFillRect(sys.getRenderer(), &white);

    tex5->render(0, 12 * 8);

    for (int i = 0; i < 5; i++)
        tex4->render(4*8, GAME_HEIGHT - TEXTBOX_HEIGHT + 8 + i * 8);

    for (int i = 0; i < 3; i++)
        tex4->render(0, 9*8 + i * 8);
    for (int i = 0; i < 3; i++)
        tex4->render(10*8, 9*8 + i * 8);

    tex5->render(4 * 8, 17 * 8);

    for (int i = 0; i < 9; i++)
        tex2->render(8+i*8, 8*8);

    tex6->render(10 * 8, 12 * 8);
    tex1->render(0, 8 * 8);
    tex3->render(10*8, 8 * 8);
    

    for (int i = 0; i < 4; i++)
    {
        if (tex_move[i].flag)
        {
            tex_move[i].render(6 * 8+1, 13 * 8 + i*8);
        }
        else
        {
            tex_move[i].render(6 * 8, 13 * 8 + i*8);
        }     
    }

    int cursorPos = cursorFightPosition;
    res.getTexture("cursor_full")->render(5*8, 13*8+cursorPos*8);

    res.getTexture("battle_type")->render(1 * 8, 9 * 8);
    if(typeText.texture != nullptr)
        typeText.render(2 * 8, 10 * 8);
    if(current_ppText.texture != nullptr)
        current_ppText.render(5 * 8, 11 * 8);
}

void Battle::update_enemy_hp()
{
    enemyHp = opp_party->pokemonList.at(currEnemyMonIndex)->hp;
}

void Battle::update_player_hp()
{
    int max_hp = player_party->pokemonList.at(currPlayerMonIndex)->maxHp();
    playerHp = player_party->pokemonList.at(currPlayerMonIndex)->hp;

    std::ostringstream str;
    str << std::setw(3) << std::setfill(' ') << playerHp;

    std::ostringstream str2;
    str2 << std::setw(3) << std::setfill(' ') << max_hp;

    std::string full_hp = str.str() + "/" + str2.str();
    SDL_Surface* sur = TTF_RenderText_Solid(Constants::font, full_hp.c_str(), { 0,0,0,0xff });
    playerPokemonHp.w = sur->w;
    playerPokemonHp.h = sur->h;

    if (sur != NULL)
    {
        //Create texture from surface pixels
        if (playerPokemonHp.texture != nullptr) 
        {
            SDL_DestroyTexture(playerPokemonHp.texture); //prevent memory leak
        }
        playerPokemonHp.texture = SDL_CreateTextureFromSurface(sys.getRenderer(), sur);
        if (playerPokemonHp.texture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }

        //Get rid of old surface
        SDL_FreeSurface(sur);
    }
}

void Battle::create_enemy_pokemon_text_texture()
{
    res.updateText(&enemyPokemonLvl, std::to_string(opp_party->pokemonList.at(currEnemyMonIndex)->level));
    res.updateText(&enemyPokemonText, enemyMonNick);
}

void Battle::create_player_pokemon_text_texture()
{
    res.updateText(&playerPokemonLvl, std::to_string(player_party->pokemonList.at(currPlayerMonIndex)->level));
    res.updateText(&playerPokemonText, battleMonNick);
}

void Battle::create_fight_text()
{
    num_moves = 0;
    for (int i = 0; i < 4; i++)
    {
        std::string move_name = player_party->pokemonList.at(currPlayerMonIndex)->moves[i];
        if (!move_name.compare("NO_MOVE"))
        {
            move_name = "-";
            tex_move[i].flag = true;
        }
        else
        {
            tex_move[i].flag = false;
            num_moves++;
        }
            
        std::replace( move_name.begin(), move_name.end(), '_', ' ');
        res.updateText(&tex_move[i], move_name);
    }
}

void Battle::update_fight_move_description()
{
    if (cursorFightPosition >= num_moves || cursorFightPosition < 0)
        return sys.error("cursorFightPosition out of bounds in Battle::update_fight_move_description()");
    auto move = res.getMove(player_party->pokemonList.at(currPlayerMonIndex)->moves[cursorFightPosition]);
    std::string str_type = move->type;
    std::string max_pp = std::to_string(move->pp);
    std::string current_pp = std::to_string(player_party->pokemonList.at(currPlayerMonIndex)->pp[cursorFightPosition]) + "/" + max_pp;

    res.updateText(&typeText, str_type);
    res.updateText(&current_ppText, current_pp);
}

void Battle::playanim_pokemonappear()
{
    int counter = *pokemonAppear.counter;
    int x_offset = pokemonAppear.x_offset-8;
    int y_offset = pokemonAppear.y_offset-16;
    int base_num = 49;
    SDL_RendererFlip both = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    auto tex = res.getTexture("attack_anim_1");

    if (counter > 25)
    {
        pokemonAppear.play = false;
    }
    else if (counter > 20)
    {
        const int table[12][4] = {
            {64,80,85,SDL_FLIP_HORIZONTAL},
            {56,80,86,SDL_FLIP_HORIZONTAL},
            {64,88,101,SDL_FLIP_HORIZONTAL},
            {32,80,86,0},
            {24,80,85,0},
            {24,88,101,0},
            {64,112,101,both},
            {64,120,85,both},
            {56,120,86,both},
            {24,112,101,SDL_FLIP_VERTICAL},
            {32,120,86,SDL_FLIP_VERTICAL},
            {24,120,85,SDL_FLIP_VERTICAL},
        };
        for (int i = 0; i < 12; i++)
        {
            tex->render_special(table[i][0]+x_offset, table[i][1]+y_offset, table[i][2]-base_num, (SDL_RendererFlip)table[i][3]);
        }
    }
    else if (counter > 15)
    {
        const int table[12][4] = {
            {60,84,85,SDL_FLIP_HORIZONTAL},
            {52,84,86,SDL_FLIP_HORIZONTAL},
            {60,92,101,SDL_FLIP_HORIZONTAL},
            {36,84,86,0},
            {28,84,85,0},
            {28,92,101,0},
            {60,108,101,both},
            {60,116,85,both},
            {52,116,86,both},
            {28,108,101,SDL_FLIP_VERTICAL},
            {36,116,86,SDL_FLIP_VERTICAL},
            {28,116,85,SDL_FLIP_VERTICAL},
        };
        for (int i = 0; i < 12; i++)
        {
            tex->render_special(table[i][0]+x_offset, table[i][1]+y_offset, table[i][2]-base_num, (SDL_RendererFlip)table[i][3]);
        }
    }
    else if (counter > 10)
    {
        const int table[16][4] = {
            {60,84,81,SDL_FLIP_HORIZONTAL},
            {52,84,82,SDL_FLIP_HORIZONTAL},
            {60,92,97,SDL_FLIP_HORIZONTAL},
            {52,92,98,SDL_FLIP_HORIZONTAL},
            {36,84,82,0},
            {28,84,81,0},
            {36,92,98,0},
            {28,92,97,0},
            {60,108,97,both},
            {52,108,98,both},
            {60,116,81,both},
            {52,116,82,both},
            {36,108,98,SDL_FLIP_VERTICAL},
            {28,108,97,SDL_FLIP_VERTICAL},
            {36,116,82,SDL_FLIP_VERTICAL},
            {28,116,81,SDL_FLIP_VERTICAL},
        };
        for (int i = 0; i < 16; i++)
        {
            tex->render_special(table[i][0]+x_offset, table[i][1]+y_offset, table[i][2]-base_num, (SDL_RendererFlip)table[i][3]);
        }
    }
    else if (counter > 5)
    {
        const int table[16][4] = {
            {56,88,81,SDL_FLIP_HORIZONTAL},
            {48,88,82,SDL_FLIP_HORIZONTAL},
            {56,96,97,SDL_FLIP_HORIZONTAL},
            {48,96,98,SDL_FLIP_HORIZONTAL},
            {40,88,82,0},
            {32,88,81,0},
            {40,96,98,0},
            {32,96,97,0},
            {56,104,97,both},
            {48,104,98,both},
            {56,112,81,both},
            {48,112,82,both},
            {40,104,98,SDL_FLIP_VERTICAL},
            {32,104,97,SDL_FLIP_VERTICAL},
            {40,112,82,SDL_FLIP_VERTICAL},
            {32,112,81,SDL_FLIP_VERTICAL},
        };
        for (int i = 0; i < 16; i++)
        {
            tex->render_special(table[i][0]+x_offset, table[i][1]+y_offset, table[i][2]-base_num, (SDL_RendererFlip)table[i][3]);
        }
    }
    else //animation starts here
    {
        tex->render_special(48+x_offset, 88+y_offset, 84-base_num, SDL_FLIP_HORIZONTAL);
        tex->render_special(56+x_offset, 96+y_offset, 99-base_num, SDL_FLIP_HORIZONTAL);
        tex->render_special(48+x_offset, 96+y_offset, 100-base_num, SDL_FLIP_HORIZONTAL);
        tex->render_special(40+x_offset, 88+y_offset, 84-base_num);
        tex->render_special(40+x_offset, 96+y_offset, 100-base_num);
        tex->render_special(32+x_offset, 96+y_offset, 99-base_num);
        tex->render_special(56+x_offset, 104+y_offset, 99-base_num, both);
        tex->render_special(48+x_offset, 104+y_offset, 100-base_num, both);
        tex->render_special(48+x_offset, 112+y_offset, 84-base_num, both);
        tex->render_special(40+x_offset, 104+y_offset, 100-base_num, SDL_FLIP_VERTICAL);
        tex->render_special(32+x_offset, 104+y_offset, 99-base_num, SDL_FLIP_VERTICAL);
        tex->render_special(40+x_offset, 112+y_offset, 84-base_num, SDL_FLIP_VERTICAL);
    }
    
}

void BattleAnimation::reset()
{
    play = false;
    counter = nullptr;
    x_offset = 0;
    y_offset = 0;
}
