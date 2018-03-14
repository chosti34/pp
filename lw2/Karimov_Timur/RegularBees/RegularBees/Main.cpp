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

DWORD WINAPI BeeThreadProcedure(LPVOID lpParameter)
{
	auto* bee = reinterpret_cast<Bee*>(lpParameter);
	bee->GatherAndStoreHoney();
	return 0;
}

DWORD WINAPI BearThreadProcedure(LPVOID lpParameter)
{
	auto* bear = reinterpret_cast<Bear*>(lpParameter);
	bear->EatHoney();
	return 0;
}

void ExecuteApplication(std::vector<std::string> && args)
{
	unsigned beesCount = std::stoul(args[1]);
	unsigned potCapacity = std::stoul(args[2]);

	HANDLE hWakeBearEvent = CreateEvent(
		NULL, // нет нужды в атрибутах безопасности
		TRUE, // будем устанавливать состояние non-signalled используя ResetEvent
		FALSE, // начальное состояние - non-signalled
		NULL // нет нужды в именовании события
	);

	HANDLE hBeesPotAccessSemaphore = CreateSemaphore(
		NULL, // нет нужды в атрибутах семафора
		DWORD(1u), // начальное значение счётчика семафора, если не ноль, то семафор в состоянии signalled
		DWORD(1u), // максимальное значение счётчика семафора, должно быть больше либо равно начальному
		NULL // нет нужды в имени семафора
	);

	// 1 горшок
	Pot pot(potCapacity);

	// 1 медведь
	Bear bear(pot, &hWakeBearEvent, &hBeesPotAccessSemaphore);

	// какое-то кол-во пчёл
	std::vector<std::unique_ptr<Bee>> bees;
	bees.reserve(beesCount);

	unsigned i = 0;
	while (i++ < beesCount)
	{
		bees.push_back(std::make_unique<Bee>(i, pot, &hWakeBearEvent, &hBeesPotAccessSemaphore));
	}

	std::vector<HANDLE> threads;
	threads.reserve(bees.size() + 1u);

	for (auto& bee : bees)
	{
		threads.push_back(CreateThread(NULL, 0u, BeeThreadProcedure, bee.get(), 0u, NULL));
	}
	threads.push_back(CreateThread(NULL, 0u, BearThreadProcedure, &bear, 0u, NULL));

	WaitForMultipleObjects(DWORD(threads.size()), threads.data(), TRUE, 5000u);

	for (auto& hThread : threads)
	{
		CloseHandle(hThread);
	}
	CloseHandle(hWakeBearEvent);
	CloseHandle(hBeesPotAccessSemaphore);
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
