#include <iostream>
#include "Hailstorm/Hailstorm.h"
static void CallBack(std::string str, HailStorm::Severity sev)
{
	std::cout << str << std::endl;
}

int main()
{
	HailStorm::ThreadPool::Initialize(CallBack);
	
	int a[1000];
	int b[1000];
	int* h = new int[100000000];

	auto aa = HailStorm::ThreadPool::Work([&]
		{
			std::cout << "Start the task in task. ID: " << std::this_thread::get_id() << "\n";
			auto work1 = HailStorm::ThreadPool::Work([&]
				{
					for (size_t i = 0; i < 100000000; ++i)
					{
						h[i] = i * i;
					}
					std::cout << std::this_thread::get_id() << " is Done!\n";

				});
			auto work2 = HailStorm::ThreadPool::Work([&]
				{
					for (size_t i = 0; i < 100000000; ++i)
					{
						h[i] = i * i;
					}
					std::cout << std::this_thread::get_id() << " is Done!\n";

				});
			auto work3 = HailStorm::ThreadPool::Work([&]
				{
					for (size_t i = 0; i < 100000000; ++i)
					{
						h[i] = i * i;
					}
					std::cout << std::this_thread::get_id() << " is Done!\n";

				});
			work1.wait();
			work2.wait();
			work3.wait();
			std::cout << std::this_thread::get_id() << " is Done!\n";


		});

	auto frt = HailStorm::ThreadPool::Work([&]
		{
			for (size_t i = 0; i < 1000; ++i)
			{
				a[i] = i;
			}
			return true;
			std::cout << std::this_thread::get_id() << " is Done!\n";

		});
	auto frt2 = HailStorm::ThreadPool::Work([&]
		{
			for (size_t i = 0; i < 1000; ++i)
			{
				b[i] = 100 - i;
			}
			std::cout << std::this_thread::get_id() << " is Done!\n";
		});
	bool isTrue = frt.get();
	std::cout << isTrue << "\n";
	frt2.wait();
	int c[100];
	auto complete = HailStorm::ThreadPool::Work([&]
		{
			for (size_t i = 0; i < 100; ++i)
			{
				c[i] = a[i] * b[i];
			}
			std::cout << std::this_thread::get_id() << " is Done!\n";

		});
	aa.wait();
	std::cout << "aa loop done\n";
	complete.wait();
	std::cout << "final loop done\n";
	

	HailStorm::ThreadPool::Shutdown();
}
