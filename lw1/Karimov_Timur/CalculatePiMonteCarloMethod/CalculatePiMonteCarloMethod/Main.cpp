#include "stdafx.h"
#include "App.h"
#include "Chronometer.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "Invalid arguments count!\n"
			"Usage: CalculatePiMonteCarloMethod.exe <iterations> <threads>" << std::endl;
		return 1;
	}

	try
	{
		App app;
		Chronometer chronometer;

		const float pi = app.Execute(std::stoi(argv[1]), std::stoi(argv[2]));
		std::cout << "Calculated PI: " << pi << std::endl;
		std::cout << "Time taken: " << chronometer.GrabDeltaTime().count() << " seconds" << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
