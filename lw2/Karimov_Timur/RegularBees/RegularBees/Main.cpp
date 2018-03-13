#include "stdafx.h"
#include "Bee.h"
#include "Bear.h"
#include "Pot.h"

/*
Задача о Винни-Пухе или правильные пчелы (Вариант 2)
В одном лесу живут M пчел и один медведь, которые используют один горшок меда
вместимостью N глотков. Сначала горшок пустой. Пока горшок не наполнится,
медведь спит. Как только горшок заполняется, медведь просыпается и съедает весь мед,
после чего снова засыпает. Каждая пчела многократно собирает по одному глотку меда
и кладет его в горшок. Пчела, которая приносит последнюю порцию меда, будит медведя.
Условную синхронизацию потоков выполнить с помощью событий и семафоров.
*/

struct ThreadSharedData
{
	HANDLE wakeBear; // event
	HANDLE noBeesPuttingHoney; // semaphore
};

DWORD WINAPI BeeThreadProc(LPVOID lpParameter)
{
	auto* bee = reinterpret_cast<Bee*>(lpParameter);
	bee->GatherAndStoreHoney();
	return 0;
}

DWORD WINAPI BearThreadProc(LPVOID lpParameter)
{
	auto* bear = reinterpret_cast<Bear*>(lpParameter);
	bear->EatHoney();
	return 0;
}

void ExecuteApplication(std::vector<std::string> && args)
{
	unsigned beesCount = std::stoul(args[1]);
	unsigned potCapacity = std::stoul(args[2]);

	ThreadSharedData threadSharedData;
	threadSharedData.wakeBear = CreateEvent(NULL, FALSE, FALSE, NULL);
	threadSharedData.noBeesPuttingHoney = CreateSemaphore(NULL, beesCount, beesCount, NULL);

	// 1 горшок
	Pot pot(potCapacity);

	// 1 медведь
	Bear bear(pot, &threadSharedData.wakeBear);

	// какое-то кол-во пчёл
	std::vector<std::unique_ptr<Bee>> bees;
	bees.reserve(beesCount);
	for (unsigned i = 0; i < beesCount; ++i)
	{
		bees.push_back(std::make_unique<Bee>(pot, &threadSharedData.wakeBear));
	}

	std::vector<HANDLE> threads;
	threads.reserve(bees.size() + 1u);

	for (auto& bee : bees)
	{
		threads.push_back(CreateThread(NULL, 0u, BeeThreadProc, bee.get(), 0u, NULL));
	}
	threads.push_back(CreateThread(NULL, 0u, BearThreadProc, &bear, 0u, NULL));

	WaitForMultipleObjects(DWORD(threads.size()), threads.data(), TRUE, INFINITE);

	for (auto& hThread : threads)
	{
		CloseHandle(hThread);
	}
	CloseHandle(threadSharedData.wakeBear);
	CloseHandle(threadSharedData.noBeesPuttingHoney);
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::fprintf(stderr, "Invalid arguments count!\nUsage RegularBees.exe <bees count> <pot capacity>\n");
		return 1;
	}

	try
	{
		ExecuteApplication(std::vector<std::string>(argv, argv + argc));
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
