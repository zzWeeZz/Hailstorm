#include <iostream>
#include "Hailstorm/Hailstorm.h"
static void CallBack(std::string str, HailStorm::Severity sev)
{
	std::cout << str << std::endl;
}

int main()
{
	HailStorm::ThreadPool::Initialize(CallBack);
	while (true) {};
}
