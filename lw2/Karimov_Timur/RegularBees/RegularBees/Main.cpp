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

namespace
{
using Function = std::function<void()>;

class Thread : private boost::noncopyable
{
public:
	Thread(Function&& fn)
		: m_fn(fn)
		, m_handle()
	{
		m_handle = CreateThread(NULL, SIZE_T(0u), &Thread::Execute, &m_fn, DWORD(0), NULL);
		assert(m_handle != NULL);
	}

	~Thread()
	{
		BOOL closed = CloseHandle(m_handle);
		assert(closed);
		(void)closed;
	}

	void Join()
	{
		DWORD state = WaitForSingleObject(m_handle, INFINITE);
		assert(state == WAIT_OBJECT_0);
	}

private:
	static DWORD WINAPI Execute(LPVOID data)
	{
		auto fn = reinterpret_cast<Function*>(data);
		(*fn)();
		return 0;
	}

	Function m_fn;
	HANDLE m_handle;
};

class ThreadPool
{
public:
	ThreadPool(size_t possibleCapacity = 0u)
		: m_threads()
	{
		m_threads.reserve(possibleCapacity);
	}

	void Add(Function&& fn)
	{
		m_threads.push_back(std::make_unique<Thread>(std::move(fn)));
	}

	void Join()
	{
		for (auto& thread : m_threads)
		{
			thread->Join();
		}
	}

private:
	std::vector<std::unique_ptr<Thread>> m_threads;
};

void SimulateBeeGardenBehavior(unsigned beesCount, unsigned potCapacity)
{
	HANDLE wakeBearEvent = CreateEvent(
		NULL, // нет нужды в атрибутах безопасности
		TRUE, // будем устанавливать состояние non-signalled используя ResetEvent
		FALSE, // начальное состояние - non-signalled
		NULL // нет нужды в именовании события
	);

	HANDLE wakeBeesEvent = CreateEvent(
		NULL, // нет нужды в атрибутах безопасности
		TRUE, // будем устанавливать состояние non-signalled используя ResetEvent
		TRUE, // начальное состояние - signalled
		NULL // нет нужды в именовании события
	);

	HANDLE beesPotAccessSemaphore = CreateSemaphore(
		NULL, // нет нужды в атрибутах семафора
		DWORD(1u), // начальное значение счётчика семафора, если не ноль, то семафор в состоянии signalled
		DWORD(1u), // максимальное значение счётчика семафора, должно быть больше либо равно начальному
		NULL // нет нужды в имени семафора
	);

	Pot pot(potCapacity);
	Bear bear(pot, wakeBearEvent, wakeBeesEvent);

	std::vector<std::unique_ptr<Bee>> bees;
	bees.reserve(beesCount);

	unsigned i = 0u;
	while (i++ < beesCount)
	{
		bees.push_back(std::make_unique<Bee>(i, pot, wakeBearEvent, wakeBeesEvent, beesPotAccessSemaphore));
	}

	ThreadPool threads(bees.size() + 1u);
	for (auto& bee : bees)
	{
		threads.Add([&bee]() { bee->GatherAndStoreHoney(); });
	}
	threads.Add([&bear]() { bear.EatHoney(); });
	threads.Join();
}

void ExecuteApplication(std::vector<std::string> && args)
{
	const unsigned beesCount = std::stoul(args[1]);
	const unsigned potCapacity = std::stoul(args[2]);
	SimulateBeeGardenBehavior(beesCount, potCapacity);
}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::fprintf(stderr,
			"Invalid arguments count!\n"
			"Usage RegularBees.exe <bees count> <pot capacity>\n");
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
