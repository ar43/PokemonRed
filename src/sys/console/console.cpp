#include "../system.h"

void Console::init()
{
	memset(buffer, 0, sizeof(buffer));
	cursor.blinkTime = 500;
	//res.loadText("c_arrow", ">", 24, 0, 6);
	//consoleInfo.loadFromRenderedTextBlended("The Legend of Zelda SDL console", game.colors[COLOR_CONSOLE], tex.fonts.con);
	//res.loadText("c_consoleinfo", "OGL_Test console", 24, 1920 - 230, 400);
	queueUpdate = false;
	lineCount = 0;
	scrollIndex = 0;
	
}

void Console::open()
{
	memset(buffer, 0, sizeof(buffer));
	cursor.lastBlink = game.frame.getTime();
	cursor.show = true;
	SDL_StartTextInput();
	//scrollIndex = 0; //maybe ??
}

void Console::close()
{
	memset(buffer, 0, sizeof(buffer));
	SDL_StopTextInput();
}

void Console::renderText()
{
	/*
	if (input.keycatchers == KEYCATCHERS_CONSOLE)
	{
		if (queueUpdate && buffer[0])
		{
			res.loadText("c_buffertext", buffer, 24, 15, 6);
			queueUpdate = false;
		}
		rend.drawText(res.getText("c_arrow"), res.getFont("main"));
		rend.drawText(res.getText("c_consoleinfo"), res.getFont("main"));
		

		for (std::vector<ConsoleLine>::size_type i = 0; i < NUM_CONSOLE_LINES; i++)
		{
			if (i + scrollIndex < lines.size())
			{
				//res.loadText("c_line", lines.at(i + scrollIndex)->text, 20, 0, (i + 2) * 20);
				lines.at(i+scrollIndex)->draw_text.pos.X(0);
				lines.at(i + scrollIndex)->draw_text.pos.Y((i + 2) * 20);
				rend.drawText(&lines.at(i + scrollIndex)->draw_text, res.getFont("main"));
			}
			else
			{
				break;
			}
		}

		if (buffer[0])
			rend.drawText(res.getText("c_buffertext"), res.getFont("main"));
	}
	*/
}

void Console::render()
{
	/*
	if (input.keycatchers == KEYCATCHERS_CONSOLE)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, sys.screen.width, sys.screen.height, 0.0, -1.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
		//glPushMatrix();        ----Not sure if I need this
		glLoadIdentity();
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		

		rend.drawRect(0, 1080-420, 1920, 420, 0,0,0); //the console
		rend.drawRect(0, 1080 - 420, 1920, 25, 48, 48, 48);
		rend.drawRect(0, 1080 - 26, 1920, 2, 0xc0, 0xc0, 0xc0);
		cursor.render();
		//R_DrawRect(0, 1080 - 400, 1920, 32, 48.0f,48.0f,48.0f); //upper gray part
		//R_DrawRect(0, SCREEN_HEIGHT - 21, SCREEN_WIDTH, 1, COLOR_WHITE); //line above input

		

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);
	}
	*/
}

void Cursor::render()
{
	/*
	if (blink.tick())
	{
		show = !show;
	}

	if(show)
	{
		if (!sys.console.buffer[0])
		{
			rend.drawRect(15, 1080-3, 7, 1, 0xc0, 0xc0, 0xc0);
		}
		else
		{
			//FTBBox box = res.getFont("main")->BBox(sys.console.buffer,-1);
			res.getFont("main")->FaceSize(24);
			rend.drawRect(15 + res.getFont("main")->Advance(sys.console.buffer, -1), 1080 - 3, 7, 1, 0xc0, 0xc0, 0xc0);
		}
	}
	*/
}

ConsoleLine::ConsoleLine(char *pText)
{
	SDL_snprintf(this->text, MAX_CONSOLE_TEXT, "%s", pText);
	//SDL_strlcpy(draw_text.text, text, 128);
	//draw_text.pos.Z(0);
	//draw_text.size = 20;
	sys.console.lineCount++;
}

ConsoleLine::ConsoleLine(char *pText, bool input)
{
	//Q_strncpyz(this->text, pText, sizeof(this->text));
	if(input)
		SDL_snprintf(this->text, MAX_CONSOLE_TEXT, "> %s", pText);
	else
		SDL_snprintf(this->text, MAX_CONSOLE_TEXT, "%s", pText);

	//SDL_strlcpy(draw_text.text, text, 128);
	//draw_text.pos.Z(0);
	//draw_text.size = 20;
	sys.console.lineCount++;

}

void Console::addLine(char *text)
{
	util::cleanStr(text);
	std::vector<std::unique_ptr<ConsoleLine>>::iterator it;
	it = lines.begin();
	lines.insert(it, std::make_unique<ConsoleLine>(text));
}

void Console::addLine(char *text, bool input)
{
	std::vector<std::unique_ptr<ConsoleLine>>::iterator it;
	it = lines.begin();
	if(input)
		lines.insert(it, std::make_unique<ConsoleLine>(text,true));
	else
		lines.insert(it, std::make_unique<ConsoleLine>(text));
}

void QDECL Console::print(const char *fmt, ...) 
{
	va_list		argptr;
	char		msg[MAX_CONSOLE_TEXT];

	va_start(argptr, fmt);
	vsprintf(msg, fmt, argptr);
	va_end(argptr);

	printf(msg);
	printf("\n");

	addLine(msg);
}

void Console::handleInput(SDL_Event* e)
{
	if (e->type == SDL_TEXTINPUT)
	{
		bool canInput = true;

		if (buffer[0])
		{
			if (strlen(buffer) > 150)
				canInput = false;
		}

		if (canInput)
		{
			SDL_strlcat(buffer, e->text.text, sizeof(buffer));
			queueUpdate = true;
			cursor.show = true;
		}
	}
	else if (e->type == SDL_KEYDOWN)
	{
		if (e->key.keysym.sym == SDLK_BACKSPACE && buffer[0])
		{
			buffer[strlen(buffer) - 1] = 0;
			queueUpdate = true;
		}
		else if (e->key.keysym.sym == SDLK_RETURN && buffer[0])
		{
			char *historybuffer = new char[MAX_CONSOLE_TEXT]();
			SDL_strlcpy(historybuffer, buffer, sizeof(buffer));
			history.push_back(historybuffer);
			historypointer = history.size() - 1;
			addLine(buffer, true);
			cmds.handle(buffer);
			memset(buffer, 0, sizeof(buffer));
			scrollIndex = 0;
		}
		else if (e->key.keysym.sym == SDLK_UP && history.size() > 0)
		{
			
			SDL_strlcpy(buffer, history.at(historypointer), MAX_CONSOLE_TEXT);

			if (historypointer > 0)
				historypointer--;
			//Sys_Print(va("%i", historypointer));
			queueUpdate = true;
		}
		else if (e->key.keysym.sym == SDLK_DOWN && historypointer < history.size() - 1)
		{
			
			historypointer++;
			//Sys_Print(va("%i", historypointer));
			SDL_strlcpy(buffer, history.at(historypointer), MAX_CONSOLE_TEXT);
			queueUpdate = true;
		}
	}
	else if (e->type == SDL_MOUSEWHEEL)
	{
		if (e->wheel.y > 0) // scroll up
		{
			if(scrollIndex < lines.size())
				scrollIndex++;
		}
		else if (e->wheel.y < 0) // scroll down
		{
			if (scrollIndex > 0)
				scrollIndex--;
		}
	}

}