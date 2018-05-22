#include "stdafx.h"
#include "PiCalculator.h"

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

void DispatchOptionAndExecute(const std::string& option)
{
	auto found = ActionsMap.find(option);
	if (found != ActionsMap.end())
	{
		auto& action = found->second;
		action();
	}
	else
	{
		PiCalculator calculator;
		const auto beginTime = std::chrono::steady_clock::now();
		const float pi = calculator.Calculate(std::stoi(option));
		const auto endTime = std::chrono::steady_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime);
		std::cout << "Calculated PI: " << pi << "\n"
			"Time taken: " << duration.count() << " ms\n";
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
		DispatchOptionAndExecute(argv[1]);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "FATAL ERROR: " << ex.what() << "\n";
		return 1;
	}
	return 0;
}
