#pragma once

#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>

class ArgumentParser
{
private:
	std::vector<std::string_view> args;

public:
	ArgumentParser(int argc, char* argv[]);
	std::string_view getArg(const std::string_view& arg) const;
	bool hasArg(const std::string_view& arg) const;
	bool validateOptions() const;
};

