#include "../sys/system.h"

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
}

void Battle::begin_wild(std::string pokemonName, int level)
{
    start();
    trainerBattle = false;
    Party* party = new Party();
    party->addPokemon(new Pokemon(res.getPokemonData(pokemonName), level));
    this->opp_party = party;
}

void Battle::start()
{
	starting = true;
    inBattle = false;
	battleIndex = 0;
    brightness = 3;
	input.keycatchers = KEYCATCHERS_TEXTBOX;
}

void Battle::on_begin()
{
}

void Battle::update()
{

	if (!inBattle)
	{
		if (starting)
		{
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
			inBattle = true;
			on_begin();
		}
	}
	else
	{
        battleIndex++;
        if (scrollIndex < 72)
            scrollIndex++;

		//todo
	}
	
}

void Battle::render()
{
	if (!inBattle)
		return;

	SDL_SetRenderDrawColor(sys.getRenderer(), 255, 255, 255, 255);
	SDL_Rect screen = { 0,0,GAME_WIDTH,GAME_HEIGHT };
	SDL_RenderFillRect(sys.getRenderer(), &screen);

    if (!trainerBattle)
    {
        opp_party->pokemonList.at(0)->data->front->render(scrollIndex * 2-40, 16);
    }
    res.getTexture("redb")->render(ash_position.x-scrollIndex*2, ash_position.y);
    
    if (battleIndex >= 100)
    {
        render_player_pokeballs();
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
    auto tex = res.getTexture("balls");
    int x_offset = 88;
    int status[6] = { 0 };
    game.player.inv.statusReport(status);
    tex->render_ex(x_offset, 80, status[0], 0, 8, 8);
    tex->render_ex(x_offset+8, 80, status[1], 0, 8, 8);
    tex->render_ex(x_offset+16, 80, status[2], 0, 8, 8);
    tex->render_ex(x_offset+24, 80, status[3], 0, 8, 8);
    tex->render_ex(x_offset+32, 80, status[4], 0, 8, 8);
    tex->render_ex(x_offset+40, 80, status[5], 0, 8, 8);
}
