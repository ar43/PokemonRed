#pragma once

#include <algorithm>

#define MAX_STRING_TOKENS 1024
#define BIG_INFO_STRING 8192

typedef void(*xcommand_t) (void);

struct ConsoleCommand
{
	ConsoleCommand(const char* pName, xcommand_t function);
	const char *name;
	xcommand_t function;
};

class Cmds
{
public:
	void init();
	void handle(char *text_in);
	void add(const char* pName, xcommand_t pFunction);
	int getArgc();
	const char *getArgv(int arg);
	std::vector<ConsoleCommand> cmdList;
	int debugint;
	

private:
	char *argv[MAX_STRING_TOKENS];
	char cmd_tokenized[BIG_INFO_STRING + MAX_STRING_TOKENS];
	int argc;
	void tokenize(char *text_in);
	

};