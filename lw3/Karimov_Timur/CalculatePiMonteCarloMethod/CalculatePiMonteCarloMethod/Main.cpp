#include "stdafx.h"

namespace
{
void PrintUsageInstructions(std::ostream& output)
{
	output << "Usage: CalculatePiMonteCarloMethod.exe <options>\n"
		"<options>:\n"
		"  * <iterations count> - calculate pi with given iterations count\n"
		"  * --help - print usage instructions\n";
}

const std::unordered_map<std::string, std::function<void()>> ActionsMap = {
	{ "--help", std::bind(&PrintUsageInstructions, std::ref(std::cout)) }
};

void DispatchAndRun(const std::string& command)
{
	auto found = ActionsMap.find(command);
	if (found != ActionsMap.end())
	{
		auto& action = found->second;
		action();
	}
	else
	{
		const float pi = 0.f;
		std::cout << "Calculated PI: " << pi << "\n";
	}
}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Invalid arguments count!\n";
		PrintUsageInstructions(std::cerr);
		return 1;
	}

	try
	{
		DispatchAndRun(argv[1]);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "FATAL ERROR: " << ex.what() << "\n";
		return 1;
	}
	return 0;
}
