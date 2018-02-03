#include "stdafx.h"

namespace
{

const unsigned ARGUMENTS_REQUIRED_COUNT = 2;
const std::string INVALID_ARGUMENTS_COUNT_MESSAGE =
	"Invalid arguments count!\n"
	"Usage: CalculatePiMonteCarloMethod.exe <iterations count>\n";

}

int main(int argc, char* argv[])
{
	if (argc != ARGUMENTS_REQUIRED_COUNT)
	{
		std::printf(INVALID_ARGUMENTS_COUNT_MESSAGE.c_str());
		return 1;
	}
	return 0;
}
