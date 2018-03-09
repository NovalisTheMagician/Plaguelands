#include <iostream>
#include <sstream>
#include "options.h"

Options::Options(int argc, char *argv[], std::string optionsFile)
{
	std::ifstream optionsStream(optionsFile);
	if (optionsStream.is_open())
		ParseOptionsFile(optionsStream);

	if ((argc - 1) % 2 != 0)
		argc -= 1;

	ParseCommandLine(argc, argv);
}

Options::~Options()
{

}

void Options::ParseOptionsFile(std::ifstream &file)
{
	//TODO 
}

void Options::ParseCommandLine(int argc, char *argv[])
{
	for (int i = 1; i < argc; i += 2)
	{
		std::string key(argv[i]);
		std::string val(argv[i]);

		opts.insert(std::pair<std::string, std::string>(key, val));
	}
}

std::string Options::GetString(std::string key, std::string def)
{
	auto val = opts.find(key);
	if (val != opts.end)
	{
		return val->second;
	}
	return def;
}

int Options::GetInt(std::string key, int def)
{
	auto val = opts.find(key);
	if (val != opts.end)
	{
		try
		{
			return std::stoi(val->second);
		}
		catch (...)
		{}
	}
	return def;
}

float Options::GetFloat(std::string key, float def)
{
	auto val = opts.find(key);
	if (val != opts.end)
	{
		try
		{
			return std::stof(val->second);
		}
		catch (...)
		{
		}
	}
	return def;
}

void Options::SetString(std::string key, std::string val)
{
	opts[key] = val;
}

void Options::SetInt(std::string key, int val)
{
	std::stringstream ss;
	ss << val;
	opts[key] = ss.str();
}

void Options::SetFloat(std::string key, float val)
{
	std::stringstream ss;
	ss << val;
	opts[key] = ss.str();
}
