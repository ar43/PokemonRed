#include "system.h"

Input::Input()
{
	keycatchers = KEYCATCHERS_NORMAL;
	block = 0;
	for (int i = 0; i < NUM_KEYS; i++)
	{
		keyDown[i] = false;
	}
}


void Input::clear()
{
	for (int i = 0; i < NUM_KEYS; i++)
	{
		keyDown[i] = false;
	}
	game.textbox.canInput = false;
	game.battle.canInput = false;
}

void Input::process(SDL_Event *e)
{
	while (SDL_PollEvent(e) != 0)
	{
		catchPriority(e);

		if (keycatchers == KEYCATCHERS_NORMAL)
			catchMain(e);
		else if (keycatchers == KEYCATCHERS_TEXTBOX)
			catchTextbox(e);
	}
}

void Input::catchPriority(SDL_Event *e)
{
	if (e->type == SDL_QUIT)
	{
		sys.requestQuit = true;
	}
	else if (e->type == SDL_KEYDOWN)
	{
		//printf("DEBUG: PRESSED: %i\n", (int)e->key.keysym.sym);

		switch (e->key.keysym.sym)
		{

		case SDLK_F1:
			printf("???\n");
			game.debug.drawPlayer = !game.debug.drawPlayer;
			break;

		case SDLK_F2:
			game.debug.drawSquare = !game.debug.drawSquare;
			break;

		case SDLK_F3:
			game.debug.drawColl = !game.debug.drawColl;
			break;

		case SDLK_F4:
			game.debug.noclip = !game.debug.noclip;
			break;

		case SDLK_F5:
			game.runDebugScript();
			game.battle.begin_wild("RATTATA",4);
			break;

		case SDLK_F11:
			game.runDebugScript();
			break;

		

		default:
			break;
		}

	}
}

void Input::catchMain(SDL_Event *e)
{
	
	if (e->type == SDL_KEYDOWN && block == 0)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_ESCAPE:
		{
			sys.requestQuit = true;
			break;
		}

		case SDLK_LSHIFT:
			game.debug.fastMode = true;
			break;

		case SDLK_UP:
			keyDown[ARROW_UP] = true;
			break;

		case SDLK_DOWN:
			keyDown[ARROW_DOWN] = true;
			break;

		case SDLK_LEFT:
			keyDown[ARROW_LEFT] = true;
			break;

		case SDLK_RIGHT:
			keyDown[ARROW_RIGHT] = true;
			break;

		case SDLK_y:
			keyDown[KEY_A] = true;
			break;
		

		default:
			break;
		}
	}
	else if (e->type == SDL_KEYUP)
	{
		switch (e->key.keysym.sym)
		{

		case SDLK_UP:
			keyDown[ARROW_UP] = false;
			break;
		case SDLK_DOWN:
			keyDown[ARROW_DOWN] = false;
			break;
		case SDLK_LEFT:
			keyDown[ARROW_LEFT] = false;
			break;
		case SDLK_RIGHT:
			keyDown[ARROW_RIGHT] = false;
			break;

		case SDLK_y:
			game.textbox.canInput = true;
			keyDown[KEY_A] = false;
			break;

		case SDLK_LSHIFT:
			game.debug.fastMode = false;
			break;

		default:
			break;
		}
	}
	
}

void Input::catchTextbox(SDL_Event* e)
{

	if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_ESCAPE:
		{
			sys.requestQuit = true;
			break;
		}
		case SDLK_y:
			keyDown[KEY_A] = true;
			break;

		case SDLK_x:
			keyDown[KEY_B] = true;
			break;

		case SDLK_UP:
			keyDown[ARROW_UP] = true;
			break;

		case SDLK_DOWN:
			keyDown[ARROW_DOWN] = true;
			break;

		case SDLK_LEFT:
			keyDown[ARROW_LEFT] = true;
			break;

		case SDLK_RIGHT:
			keyDown[ARROW_RIGHT] = true;
			break;

		default:
			break;
		}
	}
	else if (e->type == SDL_KEYUP)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_y:
			game.textbox.canInput = true;
			keyDown[KEY_A] = false;
			break;

		case SDLK_x:
			keyDown[KEY_B] = false;
			break;

		case SDLK_UP:
			game.battle.canInput = true;
			keyDown[ARROW_UP] = false;
			break;
		case SDLK_DOWN:
			game.battle.canInput = true;
			keyDown[ARROW_DOWN] = false;
			break;
		case SDLK_LEFT:
			game.battle.canInput = true;
			keyDown[ARROW_LEFT] = false;
			break;
		case SDLK_RIGHT:
			game.battle.canInput = true;
			keyDown[ARROW_RIGHT] = false;
			break;

		default:
			break;
		}
	}

}