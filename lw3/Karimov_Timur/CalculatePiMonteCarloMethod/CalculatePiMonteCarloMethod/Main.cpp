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

std::chrono::milliseconds ExecuteAndMeasureTimeTaken(std::function<void()>&& fn)
{
	auto beginTime = std::chrono::steady_clock::now();
	fn();
	auto endTime = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime);
}

void CalculatePi(float& pi, unsigned iterations)
{
	uint64_t inside = 0;

	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_real_distribution<float> distribution(-1.f, 1.f);

	for (unsigned i = 0; i < iterations; ++i)
	{
		const float x = distribution(engine);
		const float y = distribution(engine);
		if (std::pow(x, 2) + std::pow(y, 2) <= 1.f)
		{
			++inside;
		}
	}

	pi = 4.f * float(inside) / float(iterations);
}

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
		float pi = 0.f;
		const auto timeTaken = ExecuteAndMeasureTimeTaken(
			std::bind(&CalculatePi, std::ref(pi), std::stoi(option)));
		std::cout << "Calculated PI: " << pi << "\n";
		std::cout << "Time taken: " << timeTaken.count() << " ms\n";
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
