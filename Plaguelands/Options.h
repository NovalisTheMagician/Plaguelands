#pragma once

#include <map>
#include <string>
#include <fstream>

class Options
{
public:
	Options(int, char*[], std::string);
	~Options();

	std::string GetString(std::string, std::string);
	int GetInt(std::string, int);
	float GetFloat(std::string, float);

	void SetString(std::string, std::string);
	void SetInt(std::string, int);
	void SetFloat(std::string, float);

private:
	void ParseOptionsFile(std::ifstream&);
	void ParseCommandLine(int, char*[]);

private:
	std::map<std::string, std::string> opts;

};
