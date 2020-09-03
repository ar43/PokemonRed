#include "../system.h"

namespace Cmd
{
	void test()
	{
		sys.console.print("Number of args: %i", sys.console.cmds.getArgc());
	}

	void cmd_list()
	{
		sys.console.print("Command list:");
		for (std::vector<ConsoleCommand>::size_type i = 0; i < sys.console.cmds.cmdList.size(); i++)
		{
			sys.console.print("%s", sys.console.cmds.cmdList[i].name);
		}
	}

	/*
	void noclip()
	{
		game.cheats.noclip = !game.cheats.noclip;
		console.print("(CHEATS) Noclip: %i", game.cheats.noclip);
	}

	void devmode()
	{
		game.cheats.dev = !game.cheats.dev;
		console.print("(CHEATS) Devmode: %i", game.cheats.dev);
	}
	*/
}

void Cmds::init()
{
	add("test", Cmd::test);
	add("cmd_list", Cmd::cmd_list);
}

void Cmds::handle(char *text_in)
{
	tokenize(text_in);

	if (getArgc() == 0) //nothing
		return;

	for (std::vector<ConsoleCommand>::size_type i = 0; i < cmdList.size(); i++)
	{
		if (SDL_strcmp(getArgv(0), cmdList[i].name) == 0)
		{
			cmdList[i].function();
			return;
		}
	}

	sys.console.addLine(util::va("Unknown command: %s", getArgv(0)));

	for (std::vector<ConsoleCommand>::size_type i = 0; i < cmdList.size(); i++)
	{
		if (SDL_strncmp(cmdList[i].name, getArgv(0),SDL_strlen(getArgv(0))) == 0)
		{
			sys.console.addLine(util::va("%s", cmdList[i].name));
		}
	}

}

int Cmds::getArgc()
{
	return argc;
}

const char *Cmds::getArgv(int arg)
{
	if (arg >= argc)
		return "";

	return argv[arg];
}

void Cmds::tokenize(char *text_in) //stolen from Q3 engine
{
	const char *text;
	char *textOut;

	// Clear previous args
	argc = 0;

	if (!text_in)
		return;

	text = text_in;
	textOut = cmd_tokenized;

	while (1)
	{
		if (argc == MAX_STRING_TOKENS)
			return; // This is usually something malicious

		while (1)
		{
			// Skip whitespace
			while (*text && *text <= ' ')
				text++;

			if (!*text)
				return; // All tokens parsed

			// Skip // comments
			if (text[0] == '/' && text[1] == '/')
				return; // All tokens parsed

			// Skip /* */ comments
			if (text[0] == '/' && text[1] == '*')
			{
				while (*text && (text[0] != '*' || text[1] != '/'))
					text++;

				if (!*text)
					return; // All tokens parsed

				text += 2;
			}
			else
				break; // We are ready to parse a token
		}

		// Handle quoted strings
		if (*text == '"')
		{
			argv[argc] = textOut;
			argc++;
			text++;

			while (*text && *text != '"')
				*textOut++ = *text++;

			*textOut++ = 0;

			if (!*text)
				return; // All tokens parsed

			text++;
			continue;
		}

		// Regular token
		argv[argc] = textOut;
		argc++;

		// Skip until whitespace, quote, or command
		while (*(const unsigned char*)text > ' ')
		{
			if (text[0] == '"')
				break;

			if (text[0] == '/' && text[1] == '/')
				break;

			// Skip /* */ comments
			if (text[0] == '/' && text[1] == '*')
				break;

			*textOut++ = *text++;
		}

		*textOut++ = 0;

		if (!*text)
			return; // All tokens parsed
	}
}

ConsoleCommand::ConsoleCommand(const char* pName, xcommand_t pFunction)
{
	this->name = pName;
	this->function = pFunction;
}

bool comparisonFunc(ConsoleCommand c1, ConsoleCommand c2)
{
	return _stricmp(c1.name, c2.name) < 0;
}

void Cmds::add(const char* pName, xcommand_t pFunction)
{

	for (std::vector<ConsoleCommand>::size_type i = 0; i < cmdList.size(); i++)
	{
		if (_stricmp(pName, cmdList[i].name) == 0)
		{
			sys.console.addLine(util::va("Error: Trying to add already defined command %s", pName));
			return;
		}
	}

	cmdList.push_back(ConsoleCommand(pName, pFunction));
	std::sort(cmdList.begin(), cmdList.end(), comparisonFunc);
}