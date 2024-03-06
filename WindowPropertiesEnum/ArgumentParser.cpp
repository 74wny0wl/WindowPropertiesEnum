#include "ArgumentParser.h"

ArgumentParser::ArgumentParser(int argc, char* argv[])
{
	args = std::vector<std::string_view>(argv + 1, argv + argc);
}

std::string_view ArgumentParser::getArg(const std::string_view& arg) const
{
	for (auto it = args.begin(), end = args.end(); it != end; ++it) {
		if (*it == arg)
			if (it + 1 != end)
				return *(it + 1);
	}

	return "";
}

bool ArgumentParser::hasArg(const std::string_view& arg) const
{
	for (auto it = args.begin(), end = args.end(); it != end; ++it) {
		if (*it == arg)
			return true;
	}

	return false;
}

bool ArgumentParser::validateOptions() const
{
	return hasArg("-w");
}
