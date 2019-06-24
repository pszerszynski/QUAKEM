#include <iostream>

#include "Commands.hpp"
#include "Core.hpp"

using namespace Commands;

std::map<std::string, CMD_FUNC> Commands::COMMANDS;

void Commands::Init() {
	COMMANDS["echo"] = _echo;
	COMMANDS["clear"] = _clear;
	COMMANDS["quit"] = _quit;
	COMMANDS["help"] = _help;
	COMMANDS["set"] = _set;
	COMMANDS["tick"] = _tick;
	COMMANDS["playwav"] = _playwav;
	COMMANDS["playmus"] = _playmus;
	COMMANDS["stopmus"] = _stopmus;

	COMMANDS["listtex"] = _listtex;
	COMMANDS["listfnt"] = _listfnt;
	COMMANDS["listwav"] = _listwav;
	COMMANDS["listmus"] = _listmus;
}

CMD_FUNC Commands::GetCommand(const std::string& id) {
	auto cmd = COMMANDS.find(id);
	if (cmd == COMMANDS.end()) return nullptr;
	return cmd->second;
}

std::string Commands::Execute(const struct Command& com) {
	auto cmd = GetCommand(com.command);
	if (cmd == nullptr) return "Command \"" + com.command + "\" not found";
	auto result = cmd(com.args);
	return result;
}

void Commands::CallCommand(const std::string& str) {
	struct Command com;
	if (!Parser::ParseCommand(str, com)) {
		Log::Add(Parser::ErrorMsg);
	} else {
		std::string result = Commands::Execute(com); 
		Log::Add(result);
	}
}

// COMMANDS

namespace Commands {

std::string _echo(const std::vector<Argument>& args) {
	std::string str = "";
	for (auto arg : args) {
		str += arg.ToString();
	}
	return str;
}

std::string _clear(const std::vector<Argument>& args) {
	Log::History.clear();
	return "";
}

std::string _quit(const std::vector<Argument>& args) {
	Core.going = false;
	return "Quitting";
}

std::string _help(const std::vector<Argument>&) {
	std::string help_str = "\nAvailable commands:\n";
	for (auto c = COMMANDS.begin(); c != COMMANDS.end(); ++c) {
		help_str += c->first + "\n";
	}
	return help_str;
}

std::string _set(const std::vector<Argument>& args) {
	const std::string USE_MSG = "set cvar value - set a console variable to some value";
	if (args.size() < 2) return USE_MSG;
	if (args.at(0).type != ARG_CVAR) return USE_MSG;
	CVARS[args.at(0).str] = args.at(1);
	return "";
}

std::string _tick(const std::vector<Argument>& args) {
	return std::to_string(SDL_GetTicks());
}

std::string _playwav(const std::vector<Argument>& args) {
	const std::string USE_MSG = "playwav [chunkname]";

	if (args.size() < 1) return USE_MSG;
	std::string chunk_str = args.at(0).ToString();

	auto chunk = Media.GetChunk(chunk_str);
	if (chunk == nullptr) return "sfx chunk \"" + chunk_str + "\" not found";

	Mix_PlayChannel(-1, chunk, 0);

	return "";
}

std::string _playmus(const std::vector<Argument>& args) {
	const std::string USE_MSG = "playmus [name] {volume} {loops}";

	std::string mus_str;
	float volume = 1.0;
	int loops = 1;

	if (args.size() < 1) return USE_MSG;

	// volume arg
	if (args.size() >= 2) {
		if (args.at(1).type != ARG_NUMBER)
			return USE_MSG;
		else volume = args.at(1).ToFloat();
	}

	// loops args
	if (args.size() >= 3) {
		if (args.at(2).type != ARG_NUMBER)
			return USE_MSG;
		else loops = args.at(2).ToInt();
	}

	if (volume < 0.0) volume = 0.0;
	if (loops < 0) loops = 0;

	mus_str = args.at(0).ToString();
	Music.Play(mus_str, loops);
	Music.Volume(volume);
	return "";
}

template <typename T>
std::string __search__(const std::map<std::string, T>& v, std::string& find) {
	std::string str = "\n";
	bool filter = !find.empty();

	for (auto f : v) {
		std::string name = f.first;

		if (filter) {
			if (name.length() < find.length()) continue;

			for (int i = 0; i < name.length() - find.length(); ++i) {
				if (name.substr(i, find.length()) == find) {
					str += name + "\n";
					continue;
				}
			}

		} else {
			str += name + "\n";
		}

	}

	return str;
}

std::string _stopmus(const std::vector<Argument>&) {
	Music.Stop();
	return "";
}

std::string _listtex(const std::vector<Argument>& args) {
	std::string find = "";
	if (args.size() != 0)
		find = args.at(0).ToString();
	return __search__(Media.textures, find);
}

std::string _listfnt(const std::vector<Argument>& args) {
	std::string find = "";
	if (args.size() != 0)
		find = args.at(0).ToString();
	return __search__(Media.fonts, find);

}

std::string _listwav(const std::vector<Argument>& args) {
	std::string find = "";
	if (args.size() != 0)
		find = args.at(0).ToString();
	return __search__(Media.chunks, find);
}

std::string _listmus(const std::vector<Argument>& args) {
	std::string find = "";
	if (args.size() != 0)
		find = args.at(0).ToString();
	return __search__(Media.music, find);
}

}


