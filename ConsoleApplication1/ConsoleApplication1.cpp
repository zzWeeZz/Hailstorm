#include <iostream>
#include "Hailstorm/Hailstorm.h"
static void CallBack(std::string str, HailStorm::Severity sev)
{
	std::cout << str << std::endl;
}

int main()
{
	HailStorm::ThreadPool::Initialize(CallBack);
	
	int a[100];
	int b[100];
	int* h = new int[100000000];

	auto aa = HailStorm::ThreadPool::Dispatch([&]
		{
			for (size_t i = 0; i < 100000000; ++i)
			{
				h[i] = i * i;
			}
		});

	auto frt = HailStorm::ThreadPool::Dispatch([&]
		{
			for (size_t i = 0; i < 100; ++i)
			{
				a[i] = i;
			}
		});
	auto frt2 = HailStorm::ThreadPool::Dispatch([&]
		{
			for (size_t i = 0; i < 100; ++i)
			{
				b[i] = 100 - i;
			}
		});
	frt.wait();
	frt2.wait();
	int c[100];
	auto complete = HailStorm::ThreadPool::Dispatch([&]
		{
			for (size_t i = 0; i < 100; ++i)
			{
				c[i] = a[i] * b[i];
			}
		});
	complete.wait();
	aa.wait();
	HailStorm::ThreadPool::Shutdown();
}
